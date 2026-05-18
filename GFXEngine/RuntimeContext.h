#pragma once
#include "ServiceManager.h"
#include "SerializationContext.h"

const std::string ASSET_MANAGER_SERVICE_ID = "AssetManager";
const std::string BEHAVIOR_REGISTRY_SERVICE_ID = "BehaviorRegistry";
const std::string ENTITY_FACTORY_SERVICE_ID = "EntityFactory";
const std::string INPUT_MANAGER_SERVICE_ID = "InputManager";

namespace GFXEngine {
	class RuntimeContext
	{
	public: 
		static RuntimeContext& getInstance()
		{
			static RuntimeContext instance;
			return instance;
		}

		template<typename T>
		void addService(const std::string& serviceId, T* service) {
			m_serviceManager.addService<T>(serviceId, service);
		}

		template<typename T>
		T* getService(const std::string& serviceId) {
			return m_serviceManager.getService<T>(serviceId);
		}

		void removeService(const std::string& serviceId) {
			m_serviceManager.removeService(serviceId);
		}

		SerializationContext createSerializationContext() {
			AssetManager* assetManager = getService<AssetManager>(ASSET_MANAGER_SERVICE_ID);
			BehaviorRegistry* behaviorRegistry = getService<BehaviorRegistry>(BEHAVIOR_REGISTRY_SERVICE_ID);
			EntityFactory* entityFactory = getService<EntityFactory>(ENTITY_FACTORY_SERVICE_ID);
			return SerializationContext(*assetManager, *behaviorRegistry, *entityFactory);
		}

	private:
		RuntimeContext() = default;
		~RuntimeContext() = default;

		RuntimeContext(const RuntimeContext&) = delete;
		RuntimeContext& operator=(const RuntimeContext&) = delete;
		RuntimeContext(RuntimeContext&&) = delete;
		RuntimeContext& operator=(RuntimeContext&&) = delete;

		Core::ServiceManager m_serviceManager;
	};
}
