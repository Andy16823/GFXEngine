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

	struct SerializationContext
	{
		AssetManager& assets;
		BehaviorRegistry& behaviors;
		EntityFactory& entityFactory;
		EntityRegistry entityRegistry;

		
		//************************************
		// Method:    SerializationContext
		// FullName:  GFXEngine::SerializationContext::SerializationContext
		// Access:    public 
		// Returns:   
		// Qualifier: noexcept : assets(assetMgr), behaviors(behaviorReg), entityFactory(entityFactory)
		// Parameter: AssetManager & assetMgr
		// Parameter: BehaviorRegistry & behaviorReg
		// Parameter: EntityFactory & entityFactory
		//************************************
		SerializationContext(AssetManager& assetMgr, BehaviorRegistry& behaviorReg, EntityFactory& entityFactory) noexcept
			: assets(assetMgr), behaviors(behaviorReg), entityFactory(entityFactory) {}

		//************************************
		// Method:    registerEntity
		// FullName:  GFXEngine::SerializationContext::registerEntity
		// Access:    public 
		// Returns:   void
		// Qualifier:
		// Parameter: const std::string & uuid
		// Parameter: Core::Entity * entity
		//************************************
		void registerEntity(const std::string& uuid, Core::Entity* entity) 
		{
			entityRegistry[uuid] = entity;
		}

		//************************************
		// Method:    getEntity
		// FullName:  GFXEngine::SerializationContext::getEntity
		// Access:    public 
		// Returns:   GFXEngine::Core::Entity*
		// Qualifier: const
		// Parameter: const std::string & uuid
		//************************************
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