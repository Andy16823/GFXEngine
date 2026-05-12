#pragma once
#include "AssetManager.h"
#include "BehaviorRegistry.h"

namespace GFXEngine {
	class SerializationContext
	{
	public:
		AssetManager* assetManager;
		BehaviorRegistry* behaviorRegistry;

		SerializationContext() = default;
		~SerializationContext() = default;
	};
}
