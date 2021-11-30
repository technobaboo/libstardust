#include "panel.hpp"
#include "../../scenegraph.hpp"
#include "fusion_internal.hpp"
#include <cstddef>
#include <flatbuffers/flexbuffers.h>
#include <string>
#include <vector>

namespace StardustXRFusion {

std::function<void(bool, PanelItem &, uint32_t, uint32_t, uint32_t)> PanelItem::uiCallbackFunction = [](bool, PanelItem &, uint32_t, uint32_t, uint32_t) {};

PanelItem::PanelItem(Spatial *space, std::string nodePath, std::string nodeName) :
	Item(space, nodePath, nodeName) {
}
void PanelItem::registerUIHandler(std::function<void(bool, PanelItem &, uint32_t, uint32_t, uint32_t)> callback) {
	uiCallbackFunction = callback;
	scenegraph->methods["panelUI"] = &PanelItem::uiCallback;

	messenger->sendSignal(
		"/item",
		"registerPanelItemUI",
		FLEX_ARGS(
			FLEX_STRING(std::string(""))
			FLEX_STRING(std::string("panelUI"))
		)
	);
}

void PanelItem::applySurfaceMaterial(Model &model, uint32_t submeshIndex) {
	messenger->sendSignal(
		getNodePath().c_str(),
		"applySurfaceMaterial",
		FLEX_ARGS(
			FLEX_STRING(model.getNodePath())
			fbb.UInt(submeshIndex);
		)
	);
}

std::vector<uint8_t> PanelItem::uiCallback(flexbuffers::Reference data, bool) {
	flexbuffers::Vector flexVec = data.AsVector();
	bool created = flexVec[0].AsBool();
	std::string nodeName = flexVec[1].AsString().str();
	flexbuffers::Vector dataVec = flexVec[2].AsVector();

	PanelItem item(nullptr, "/item/panel", nodeName);
	uiCallbackFunction(created, item, dataVec[0].AsUInt32(), dataVec[1].AsUInt32(), dataVec[2].AsUInt32());
	return std::vector<uint8_t>();
}

}
