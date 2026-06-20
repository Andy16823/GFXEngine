#pragma once

#include <GLFW/glfw3.h>
#include "ServiceManager.h"
#include "SerializationContext.h"
#include "AssetManager.h"
#include "BehaviorRegistry.h"
#include "EntityFactory.h"
#include "InputManager.h"
#include "EventBus.h"

namespace GFXEngine {

	class RuntimeContext
	{
	public: 

		//************************************
		// Method:    get
		// FullName:  GFXEngine::RuntimeContext::get
		// Access:    public static 
		// Returns:   GFXEngine::RuntimeContext&
		// Qualifier:
		//************************************
		static RuntimeContext& get()
		{
			static RuntimeContext instance;
			return instance;
		}

	public:
		//************************************
		// Method:    setWindow
		// FullName:  GFXEngine::RuntimeContext::setWindow
		// Access:    public 
		// Returns:   void
		// Qualifier:
		// Parameter: GLFWwindow * window
		//************************************
		void setWindow(GLFWwindow* window) { m_window = window; }
		
		//************************************
		// Method:    setServiceManager
		// FullName:  GFXEngine::RuntimeContext::setServiceManager
		// Access:    public 
		// Returns:   void
		// Qualifier:
		// Parameter: ServiceManager * manager
		//************************************
		void setServiceManager(ServiceManager* manager) { m_serviceManager = manager; }
		
		//************************************
		// Method:    setAssetManager
		// FullName:  GFXEngine::RuntimeContext::setAssetManager
		// Access:    public 
		// Returns:   void
		// Qualifier:
		// Parameter: AssetManager * manager
		//************************************
		void setAssetManager(AssetManager* manager) { m_assetManager = manager; }
		
		//************************************
		// Method:    setBehaviorRegistry
		// FullName:  GFXEngine::RuntimeContext::setBehaviorRegistry
		// Access:    public 
		// Returns:   void
		// Qualifier:
		// Parameter: BehaviorRegistry * registry
		//************************************
		void setBehaviorRegistry(BehaviorRegistry* registry) { m_behaviorRegistry = registry; }
		
		//************************************
		// Method:    setEntityFactory
		// FullName:  GFXEngine::RuntimeContext::setEntityFactory
		// Access:    public 
		// Returns:   void
		// Qualifier:
		// Parameter: EntityFactory * factory
		//************************************
		void setEntityFactory(EntityFactory* factory) { m_entityFactory = factory; }
		
		//************************************
		// Method:    setInputManager
		// FullName:  GFXEngine::RuntimeContext::setInputManager
		// Access:    public 
		// Returns:   void
		// Qualifier:
		// Parameter: InputManager * manager
		//************************************
		void setInputManager(InputManager* manager) { m_inputManager = manager; }
		
		//************************************
		// Method:    setEventBus
		// FullName:  GFXEngine::RuntimeContext::setEventBus
		// Access:    public 
		// Returns:   void
		// Qualifier:
		// Parameter: EventBus * eventBus
		//************************************
		void setEventBus(EventBus* eventBus) { m_eventBus = eventBus; }

	public:
		//************************************
		// Method:    getWindow
		// FullName:  GFXEngine::RuntimeContext::getWindow
		// Access:    public 
		// Returns:   GLFWwindow*
		// Qualifier: const
		//************************************
		GLFWwindow* getWindow() const { return m_window; }
		
		//************************************
		// Method:    getServiceManager
		// FullName:  GFXEngine::RuntimeContext::getServiceManager
		// Access:    public 
		// Returns:   GFXEngine::ServiceManager*
		// Qualifier:
		//************************************
		ServiceManager* getServiceManager() { return m_serviceManager; }
		
		//************************************
		// Method:    getAssetManager
		// FullName:  GFXEngine::RuntimeContext::getAssetManager
		// Access:    public 
		// Returns:   GFXEngine::AssetManager*
		// Qualifier: const
		//************************************
		AssetManager* getAssetManager() const { return m_assetManager; }
		
		//************************************
		// Method:    getBehaviorRegistry
		// FullName:  GFXEngine::RuntimeContext::getBehaviorRegistry
		// Access:    public 
		// Returns:   GFXEngine::BehaviorRegistry*
		// Qualifier: const
		//************************************
		BehaviorRegistry* getBehaviorRegistry() const { return m_behaviorRegistry; }
		
		//************************************
		// Method:    getEntityFactory
		// FullName:  GFXEngine::RuntimeContext::getEntityFactory
		// Access:    public 
		// Returns:   GFXEngine::EntityFactory*
		// Qualifier: const
		//************************************
		EntityFactory* getEntityFactory() const { return m_entityFactory; }
		
		//************************************
		// Method:    getInputManager
		// FullName:  GFXEngine::RuntimeContext::getInputManager
		// Access:    public 
		// Returns:   GFXEngine::InputManager*
		// Qualifier: const
		//************************************
		InputManager* getInputManager() const { return m_inputManager; }
		
		//************************************
		// Method:    getEventBus
		// FullName:  GFXEngine::RuntimeContext::getEventBus
		// Access:    public 
		// Returns:   GFXEngine::EventBus*
		// Qualifier: const
		//************************************
		EventBus* getEventBus() const { return m_eventBus; }
		
	public:
		
		//************************************
		// Method:    createSerializationContext
		// FullName:  GFXEngine::RuntimeContext::createSerializationContext
		// Access:    public 
		// Returns:   GFXEngine::SerializationContext
		// Qualifier:
		//************************************
		SerializationContext createSerializationContext() {
			AssetManager* assetManager = m_assetManager;
			BehaviorRegistry* behaviorRegistry = m_behaviorRegistry;
			EntityFactory* entityFactory = m_entityFactory;
			return SerializationContext(*assetManager, *behaviorRegistry, *entityFactory);
		}

	private:
		//************************************
		// Method:    RuntimeContext
		// FullName:  GFXEngine::RuntimeContext::RuntimeContext
		// Access:    private 
		// Returns:   
		// Qualifier:
		//************************************
		RuntimeContext() = default;
		
		//************************************
		// Method:    ~RuntimeContext
		// FullName:  GFXEngine::RuntimeContext::~RuntimeContext
		// Access:    private 
		// Returns:   
		// Qualifier:
		//************************************
		~RuntimeContext() = default;

		//************************************
		// Method:    RuntimeContext
		// FullName:  GFXEngine::RuntimeContext::RuntimeContext
		// Access:    private 
		// Returns:   
		// Qualifier:
		// Parameter: const RuntimeContext &
		//************************************
		RuntimeContext(const RuntimeContext&) = delete;
		
		//************************************
		// Method:    operator=
		// FullName:  GFXEngine::RuntimeContext::operator=
		// Access:    private 
		// Returns:   GFXEngine::RuntimeContext&
		// Qualifier: = delete
		// Parameter: const RuntimeContext &
		//************************************
		RuntimeContext& operator=(const RuntimeContext&) = delete;
		
		//************************************
		// Method:    RuntimeContext
		// FullName:  GFXEngine::RuntimeContext::RuntimeContext
		// Access:    private 
		// Returns:   
		// Qualifier:
		// Parameter: RuntimeContext & &
		//************************************
		RuntimeContext(RuntimeContext&&) = delete;
		
		//************************************
		// Method:    operator=
		// FullName:  GFXEngine::RuntimeContext::operator=
		// Access:    private 
		// Returns:   GFXEngine::RuntimeContext&
		// Qualifier: = delete
		// Parameter: RuntimeContext & &
		//************************************
		RuntimeContext& operator=(RuntimeContext&&) = delete;

	private:
		GLFWwindow* m_window = nullptr;
		ServiceManager* m_serviceManager = nullptr;
		AssetManager* m_assetManager = nullptr;
		BehaviorRegistry* m_behaviorRegistry = nullptr;
		EntityFactory* m_entityFactory = nullptr;
		InputManager* m_inputManager = nullptr;
		EventBus* m_eventBus = nullptr;
	};
}
