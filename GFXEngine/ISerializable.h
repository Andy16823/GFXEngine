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

	//************************************
	// Method:    operator|
	// FullName:  GFXEngine::operator|
	// Access:    public 
	// Returns:   GFXEngine::SerializationFlags
	// Qualifier:
	// Parameter: SerializationFlags a
	// Parameter: SerializationFlags b
	//************************************
	inline SerializationFlags operator|(SerializationFlags a, SerializationFlags b)
	{
		return static_cast<SerializationFlags>(static_cast<int>(a) | static_cast<int>(b));
	}

	//************************************
	// Method:    operator&
	// FullName:  GFXEngine::operator&
	// Access:    public 
	// Returns:   GFXEngine::SerializationFlags
	// Qualifier:
	// Parameter: SerializationFlags a
	// Parameter: SerializationFlags b
	//************************************
	inline SerializationFlags operator&(SerializationFlags a, SerializationFlags b)
	{
		return static_cast<SerializationFlags>(static_cast<int>(a) & static_cast<int>(b));
	}

	//************************************
	// Method:    operator|=
	// FullName:  GFXEngine::operator|=
	// Access:    public 
	// Returns:   GFXEngine::SerializationFlags&
	// Qualifier:
	// Parameter: SerializationFlags & a
	// Parameter: SerializationFlags b
	//************************************
	inline SerializationFlags& operator|=(SerializationFlags& a, SerializationFlags b)
	{
		a = a | b;
		return a;
	}

	//************************************
	// Method:    operator&=
	// FullName:  GFXEngine::operator&=
	// Access:    public 
	// Returns:   GFXEngine::SerializationFlags&
	// Qualifier:
	// Parameter: SerializationFlags & a
	// Parameter: SerializationFlags b
	//************************************
	inline SerializationFlags& operator&=(SerializationFlags& a, SerializationFlags b)
	{
		a = a & b;
		return a;
	}

	//************************************
	// Method:    hasFlag
	// FullName:  GFXEngine::hasFlag
	// Access:    public 
	// Returns:   bool
	// Qualifier:
	// Parameter: SerializationFlags flags
	// Parameter: SerializationFlags flag
	//************************************
	inline bool hasFlag(SerializationFlags flags, SerializationFlags flag)
	{
		return (flags & flag) == flag;
	}

	class ISerializable
	{
	public:
		//************************************
		// Method:    ~ISerializable
		// FullName:  GFXEngine::ISerializable::~ISerializable
		// Access:    virtual public 
		// Returns:   
		// Qualifier:
		//************************************
		virtual ~ISerializable() = default;
		
		//************************************
		// Method:    serialize
		// FullName:  GFXEngine::ISerializable::serialize
		// Access:    virtual public 
		// Returns:   nlohmann::json
		// Qualifier: const
		//************************************
		virtual nlohmann::json serialize() const = 0;
		
		//************************************
		// Method:    deserialize
		// FullName:  GFXEngine::ISerializable::deserialize
		// Access:    virtual public 
		// Returns:   void
		// Qualifier:
		// Parameter: const nlohmann::json & data
		// Parameter: SerializationContext & context
		// Parameter: SerializationFlags flags
		//************************************
		virtual void deserialize(const nlohmann::json& data, SerializationContext& context, SerializationFlags flags = SerializationFlags::None) = 0;
		
		//************************************
		// Method:    resolveReferences
		// FullName:  GFXEngine::ISerializable::resolveReferences
		// Access:    virtual public 
		// Returns:   void
		// Qualifier:
		// Parameter: SerializationContext & context
		//************************************
		virtual void resolveReferences(SerializationContext& context) {};
	};
}