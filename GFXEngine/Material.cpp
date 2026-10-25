#include "Material.h"

using namespace GFXEngine;
using namespace GFXEngine::Graphics;

nlohmann::json Material::serialize() const {
	nlohmann::json data;
	data["type"] = typeid(*this).name();
	return data;
}

void Material::deserialize(const nlohmann::json& data, GFXEngine::SerializationContext& context, GFXEngine::SerializationFlags flags) {
	
}