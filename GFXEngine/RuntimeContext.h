#pragma once

#include <GLFW/glfw3.h>
#include "ServiceManager.h"
#include "SerializationContext.h"
#include "AssetManager.h"
#include "BehaviorRegistry.h"
#include "EntityFactory.h"
#include "InputManager.h"

namespace GFXEngine {

	class RuntimeContext
	{
	public: 

		static RuntimeContext& get()
		{
			static RuntimeContext instance;
			return instance;
		}

		void setWindow(GLFWwindow* window) { m_window = window; }
		void setServiceManager(ServiceManager* manager) { m_serviceManager = manager; }
		void setAssetManager(AssetManager* manager) { m_assetManager = manager; }
		void setBehaviorRegistry(BehaviorRegistry* registry) { m_behaviorRegistry = registry; }
		void setEntityFactory(EntityFactory* factory) { m_entityFactory = factory; }
		void setInputManager(InputManager* manager) { m_inputManager = manager; }

		GLFWwindow* getWindow() const { return m_window; }
		ServiceManager* getServiceManager() { return m_serviceManager; }
		AssetManager* getAssetManager() const { return m_assetManager; }
		BehaviorRegistry* getBehaviorRegistry() const { return m_behaviorRegistry; }
		EntityFactory* getEntityFactory() const { return m_entityFactory; }
		InputManager* getInputManager() const { return m_inputManager; }
		
		SerializationContext createSerializationContext() {
			AssetManager* assetManager = m_assetManager;
			BehaviorRegistry* behaviorRegistry = m_behaviorRegistry;
			EntityFactory* entityFactory = m_entityFactory;
			return SerializationContext(*assetManager, *behaviorRegistry, *entityFactory);
		}

	private:
		RuntimeContext() = default;
		~RuntimeContext() = default;

		RuntimeContext(const RuntimeContext&) = delete;
		RuntimeContext& operator=(const RuntimeContext&) = delete;
		RuntimeContext(RuntimeContext&&) = delete;
		RuntimeContext& operator=(RuntimeContext&&) = delete;

		GLFWwindow* m_window = nullptr;
		ServiceManager* m_serviceManager = nullptr;
		AssetManager* m_assetManager = nullptr;
		BehaviorRegistry* m_behaviorRegistry = nullptr;
		EntityFactory* m_entityFactory = nullptr;
		InputManager* m_inputManager = nullptr;
	};
}
