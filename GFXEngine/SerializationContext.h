#pragma once

namespace GFXEngine {
	class AssetManager;
	class BehaviorRegistry;
	class EntityFactory;

	/// <summary>
	/// SerializationContext provides necessary resources and information for the serialization and deserialization processes within the GFXEngine. 
	/// </summary>
	struct SerializationContext
	{
		AssetManager& assets;
		BehaviorRegistry& behaviors;
		EntityFactory& entityFactory;

		constexpr SerializationContext(AssetManager& assetMgr, BehaviorRegistry& behaviorReg, EntityFactory& entityFactory) noexcept
			: assets(assetMgr), behaviors(behaviorReg), entityFactory(entityFactory) {}
	};
}