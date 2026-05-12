#pragma once

namespace GFXEngine {
	class AssetManager;
	class BehaviorRegistry;

	class SerializationContext
	{
	public:
		AssetManager* assetManager;
		BehaviorRegistry* behaviorRegistry;

		SerializationContext(AssetManager* assetMgr, BehaviorRegistry* behaviorReg)
			: assetManager(assetMgr), behaviorRegistry(behaviorReg) {}
		~SerializationContext() = default;
	};
}
