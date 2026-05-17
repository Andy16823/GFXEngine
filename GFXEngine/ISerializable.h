#pragma once
#include <string>
#include <nlohmann/json.hpp>
#include "SerializationContext.h"

namespace GFXEngine {

	enum class SerializationFlags
	{
		None = 0,
		RegenerateUUID = 1 << 0, // When deserializing, generate new UUIDs instead of using the ones in the JSON
	};

	inline SerializationFlags operator|(SerializationFlags a, SerializationFlags b)
	{
		return static_cast<SerializationFlags>(static_cast<int>(a) | static_cast<int>(b));
	}

	inline SerializationFlags operator&(SerializationFlags a, SerializationFlags b)
	{
		return static_cast<SerializationFlags>(static_cast<int>(a) & static_cast<int>(b));
	}

	inline SerializationFlags& operator|=(SerializationFlags& a, SerializationFlags b)
	{
		a = a | b;
		return a;
	}

	inline SerializationFlags& operator&=(SerializationFlags& a, SerializationFlags b)
	{
		a = a & b;
		return a;
	}

	inline bool hasFlag(SerializationFlags flags, SerializationFlags flag)
	{
		return (flags & flag) == flag;
	}

	class ISerializable
	{
	public:
		virtual ~ISerializable() = default;
		virtual nlohmann::json serialize() const = 0;
		virtual void deserialize(const nlohmann::json& data, SerializationContext& context, SerializationFlags flags = SerializationFlags::None) = 0;
	};
}