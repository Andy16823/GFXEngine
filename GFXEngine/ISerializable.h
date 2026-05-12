#pragma once
#include <string>
#include <nlohmann/json.hpp>
#include "SerializationContext.h"

namespace GFXEngine {
	class ISerializable
	{
	public:
		virtual ~ISerializable() = default;
		virtual nlohmann::json serialize() const = 0;
		virtual void deserialize(const nlohmann::json& data, SerializationContext& context) = 0;
	};
}