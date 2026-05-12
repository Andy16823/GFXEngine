#pragma once

namespace GFXEngine {
	class AssetManager;
	class BehaviorRegistry;

	/// <summary>
	/// SerializationContext provides necessary resources and information for the serialization and deserialization processes within the GFXEngine. 
	/// </summary>
	struct SerializationContext
	{
		AssetManager& assets;
		BehaviorRegistry& behaviors;

		constexpr SerializationContext(AssetManager& assetMgr, BehaviorRegistry& behaviorReg) noexcept
			: assets(assetMgr), behaviors(behaviorReg) {}
	};
}