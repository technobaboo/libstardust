#include "messenger.hpp"
#include <flatbuffers/flatbuffers.h>
#include <mutex>
#include <signal.h>
#include <unistd.h>

namespace StardustXR {

Messenger::Messenger(int readFD, int writeFD, Scenegraph *scenegraph) {
	this->messageReadFD = readFD;
	this->messageWriteFD = writeFD;
	this->scenegraph = scenegraph;

	// setup signal handler
	struct sigaction sigact = {SIG_IGN};
	sigaction(SIGPIPE, &sigact, nullptr);
}

Messenger::~Messenger() {}

void Messenger::startHandler() {
	this->handlerThread = std::thread(&StardustXR::Messenger::messageHandler, this);
	this->handlerThread.detach();
}

uint Messenger::generateMessageID() {
	const std::lock_guard<std::mutex> lock(pendingCallbacksMutex);

	uint id = 0;
	while(pendingCallbacks.count(id)) //Increment up until a free spot is found for the message ID
		id++;
	return id;
}

void Messenger::executeRemoteMethod(const char *object, const char *method, std::vector<uint8_t> &data, Callback callback) {
	if(checkPipeBroken()) return;

	uint id = generateMessageID();
	{
		const std::lock_guard<std::mutex> lock(pendingCallbacksMutex);
		pendingCallbacks[id] = callback;
	}
	sendCall(2, id, object, method, data);
}

void Messenger::sendCall(uint8_t type, uint id, const char *object, const char *method, std::vector<uint8_t> &data) {
	if(checkPipeBroken()) return;

	const std::lock_guard<std::mutex> sendLock(sendMutex);

	auto objectPath = fbb.CreateString(object);
	auto methodName = fbb.CreateString(method);
	auto dataBuffer = fbb.CreateVector<uint8_t>(data);

	MessageBuilder messageBuilder(fbb);
	messageBuilder.add_type(type);
	messageBuilder.add_id(id);
	messageBuilder.add_object(objectPath);
	messageBuilder.add_method(methodName);
	messageBuilder.add_data(dataBuffer);
	auto message = messageBuilder.Finish();

	fbb.Finish(message);
	sendMessage(fbb.GetBufferPointer(), fbb.GetSize());
	fbb.Clear();
}

void Messenger::sendMessage(uint8_t *buffer, uint32_t size) {
	ssize_t rc;
	rc = write(messageWriteFD, &size, 4);
	if (rc == -1 && errno == EPIPE) {
		pipeBroke = true;
		checkPipeBroken();
		return;
	}

	write(messageWriteFD, buffer, size);
}

void Messenger::messageHandler() {
	while (!pipeBroke) {
		uint32_t messageLength;
		switch (read(messageReadFD, &messageLength, 4)) {
			case 0: {
				printf("Pipe broke!\n");
				pipeBroke = true;
				return;
			} break;
			case -1: {
				printf("Pipe error\n");
				continue;
			}
		}

		void *messageBinary = malloc(messageLength);
		read(messageReadFD, messageBinary, messageLength);

		const Message *message = GetMessage(messageBinary);
		handleMessage(message);

		free(messageBinary);
	}

	onPipeBreak();
}

void Messenger::handleMessage(const Message *message) {
	switch (message->type()) {
	case 0: {
		// Error, so spit the error out to stderr
		fputs(message->error()->c_str(), stderr);
	} break;
	case 1: {
		// Signal, so execute the local scenegraph method
		scenegraph->sendSignal(message->object()->str(), message->method()->str(), message->data_flexbuffer_root());
	} break;
	case 2: {

		// Method was called, so execute the local scenegraph method and send back the result
		std::vector<uint8_t> returnValue = scenegraph->executeMethod(message->object()->str(), message->method()->str(), message->data_flexbuffer_root());
		sendCall(3, message->id(), message->object()->c_str(), message->method()->c_str(), returnValue);
	} break;
	case 3: {
		Callback callback = nullptr;
		{
			const std::lock_guard<std::mutex> lock(pendingCallbacksMutex);
			if(pendingCallbacks.count(message->id())) {
				callback = pendingCallbacks[message->id()];
				pendingCallbacks.erase(message->id());
			} else {
				// I have no idea how this would happen but I don't want anything breaking on the slim chance it does...
				printf("The method callback \"%s\" on object with path \"%s\" and id %i is not pending\n", message->method()->c_str(), message->object()->c_str(), message->id());
				return;
			}
		}

		//Method return, so execute the callback method if it exists and remove it from the pending map
		callback(message->data_flexbuffer_root());
	}
	}
}

} // namespace StardustXR