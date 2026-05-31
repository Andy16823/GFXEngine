#pragma once
#include <unordered_map>
#include <string>

namespace GFXEngine {

	namespace Core {
		class Entity;
	}

	class AssetManager;
	class BehaviorRegistry;
	class EntityFactory;

	using EntityRegistry = std::unordered_map<std::string, GFXEngine::Core::Entity*>;

	/// <summary>
	/// SerializationContext provides necessary resources and information for the serialization and deserialization processes within the GFXEngine. 
	/// </summary>
	struct SerializationContext
	{
		AssetManager& assets;
		BehaviorRegistry& behaviors;
		EntityFactory& entityFactory;
		EntityRegistry entityRegistry;


		SerializationContext(AssetManager& assetMgr, BehaviorRegistry& behaviorReg, EntityFactory& entityFactory) noexcept
			: assets(assetMgr), behaviors(behaviorReg), entityFactory(entityFactory) {}

		void registerEntity(const std::string& uuid, Core::Entity* entity) 
		{
			entityRegistry[uuid] = entity;
		}

		Core::Entity* getEntity(const std::string& uuid) const
		{
			auto it = entityRegistry.find(uuid);
			if (it != entityRegistry.end()) {
				return it->second;
			}
			return nullptr;
		}
	};
}