#ifndef STARDUSTXR_STARDUST_SCENEGRAPH_H
#define STARDUSTXR_STARDUST_SCENEGRAPH_H

#include "../scenegraph.hpp"
#include "node.hpp"

namespace StardustXR {

class StardustScenegraph : public Scenegraph {
public:
	StardustScenegraph() : Scenegraph() {}

	void sendSignal(std::string path, std::string method, flexbuffers::Reference data);
	std::vector<uint8_t> executeMethod(std::string path, std::string method, flexbuffers::Reference args);

	void createNode(std::string path, Node *node);
protected:
	Node root;
	void onPathStep(std::string path, void (*pathStepFunction)(std::string pathStep));
};

} // namespace StardustXR

#endif
