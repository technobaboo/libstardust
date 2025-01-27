#include "../../fusion_internal.hpp"
#include "../../flex.hpp"

#include "cylinderfield.hpp"



namespace StardustXRFusion {

CylinderField::CylinderField(Spatial *parent, Vec3 origin, Quat rotation, float length, float radius) {
	nodeName = GenerateID();
	nodePath = "/field";
	messenger->sendSignal(
		"/field",
		"createCylinderField",
		FLEX_ARGS(
			FLEX_STRING(nodeName)
			FLEX_STRING(parent ? parent->getNodePath() : std::string(""))
			FLEX_VEC3(origin)
			FLEX_QUAT(rotation)
			FLEX_FLOAT(length)
			FLEX_FLOAT(radius)
		)
	);
}

} // namespace StardustXRFusion
