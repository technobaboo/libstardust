#pragma once

#include "../acceptor.hpp"
#include "../item.hpp"
#include "../types/environment.hpp"

#include <functional>

namespace StardustXRFusion {

class EnvironmentItemAcceptor : public ItemAcceptor {
public:
	explicit EnvironmentItemAcceptor(Spatial *parent, Field &field, Vec3 origin, Quat rotation);

	std::function<void(EnvironmentItem &panel, EnvironmentItem::Data data)> itemCapturedMethod = [](EnvironmentItem &, EnvironmentItem::Data) {};
	std::function<void(EnvironmentItem &panel)> itemReleasedMethod = [](EnvironmentItem &) {};

private:
	std::vector<uint8_t> acceptorCallback(flexbuffers::Reference data, bool);
};

}
