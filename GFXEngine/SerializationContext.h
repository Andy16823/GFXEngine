#pragma once

namespace GFXEngine {
	class AssetManager;
	class BehaviorRegistry;

	class SerializationContext
	{
	public:
		AssetManager* assetManager;
		BehaviorRegistry* behaviorRegistry;

		SerializationContext() = default;
		~SerializationContext() = default;
	};
}
