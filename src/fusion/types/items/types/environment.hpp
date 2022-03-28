#pragma once

#include "../item.hpp"
#include <functional>
#include <string>
#include <vector>

namespace flexbuffers {
	class Reference;
}

namespace StardustXRFusion {

class EnvironmentItem : public Item {
public:
	EnvironmentItem(Spatial *space, const std::string path, SKMath::vec3 origin, SKMath::quat orientation);
	EnvironmentItem(Spatial *space, std::string nodePath, std::string nodeName);

	struct Data {
		const std::string path;
	};

	static void registerUIHandlers(std::function<void(EnvironmentItem &, Data)> create, std::function<void(EnvironmentItem &)> destroy);

	static std::string createAcceptorMethodString;
	static Data parseData(flexbuffers::Reference data);

private:
	static std::vector<uint8_t> uiCallback(flexbuffers::Reference data, bool);
	static std::function<void(EnvironmentItem &, Data)> uiCreateFunction;
	static std::function<void(EnvironmentItem &)>       uiDestroyFunction;
};

}