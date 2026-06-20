#pragma once
#include "ServiceManager.h"
#include "Renderer.h"
#include "Camera.h"
#include "LibGFX.h"
#include "DataTypes.h"
#include "AssetManager.h"
#include "BehaviorRegistry.h"
#include "EntityFactory.h"
#include "InputManager.h"
#include "EventBus.h"
#include "BackgroundTask.h"

namespace GFXEngine {
	namespace Core {
		class Game
		{
		private:
			GLFWwindow* m_window = nullptr;
			std::unique_ptr<Graphics::Renderer> m_renderer;
			BackgroundTaskManager m_backgroundTaskManager;
			glm::ivec2 m_windowSize = { 800, 600 };
			float m_targetFPS = 120.0f;
			float m_lastFrameTime = 0.0f;
			float m_deltaTime = 0.0f;
			bool m_resizable = false;

		public:
			std::unique_ptr<ServiceManager> serviceManager = std::make_unique<ServiceManager>();
			std::unique_ptr<AssetManager> assetManager = std::make_unique<AssetManager>();
			std::unique_ptr<BehaviorRegistry> behaviorRegistry = std::make_unique<BehaviorRegistry>();
			std::unique_ptr<EntityFactory> entityFactory = std::make_unique<EntityFactory>();
			std::unique_ptr<InputManager> inputManager = std::make_unique<InputManager>();
			std::unique_ptr<EventBus> eventBus = std::make_unique<EventBus>();

		public:
			//************************************
			// Method:    Game
			// FullName:  GFXEngine::Core::Game::Game
			// Access:    public 
			// Returns:   
			// Qualifier:
			//************************************
			Game() = default;
			
			//************************************
			// Method:    ~Game
			// FullName:  GFXEngine::Core::Game::~Game
			// Access:    virtual public 
			// Returns:   
			// Qualifier:
			//************************************
			virtual ~Game() = default;

			//************************************
			// Method:    start
			// FullName:  GFXEngine::Core::Game::start
			// Access:    public 
			// Returns:   void
			// Qualifier:
			// Parameter: uint32_t width
			// Parameter: uint32_t height
			// Parameter: const std::string & shadersDirectory
			// Parameter: const std::string & title
			// Parameter: bool fullscreen
			// Parameter: bool validationLayers
			//************************************
			void start(uint32_t width, uint32_t height, const std::string& shadersDirectory, const std::string& title = "My Game", bool fullscreen = false, bool validationLayers = true);

			//************************************
			// Method:    onInit
			// FullName:  GFXEngine::Core::Game::onInit
			// Access:    virtual public 
			// Returns:   void
			// Qualifier:
			// Parameter: Graphics::Renderer & renderer
			//************************************
			virtual void onInit(Graphics::Renderer& renderer) = 0;
			
			//************************************
			// Method:    onInit
			// FullName:  GFXEngine::Core::Game::onInit
			// Access:    virtual public 
			// Returns:   void
			// Qualifier:
			// Parameter: Graphics::Renderer & renderer
			//************************************
			virtual void onStart(Graphics::Renderer& renderer) = 0;
			
			//************************************
			// Method:    onUpdate
			// FullName:  GFXEngine::Core::Game::onUpdate
			// Access:    virtual public 
			// Returns:   void
			// Qualifier:
			// Parameter: Graphics::Renderer & renderer
			// Parameter: uint32_t imageIndex
			// Parameter: float deltaTime
			//************************************
			virtual void onUpdate(Graphics::Renderer& renderer, uint32_t imageIndex, float deltaTime) = 0;
			
			//************************************
			// Method:    beforeRender
			// FullName:  GFXEngine::Core::Game::beforeRender
			// Access:    virtual public 
			// Returns:   void
			// Qualifier:
			// Parameter: Graphics::Renderer & renderer
			// Parameter: uint32_t imageIndex
			//************************************
			virtual void beforeRender(Graphics::Renderer& renderer, uint32_t imageIndex) = 0;
			
			//************************************
			// Method:    onRender
			// FullName:  GFXEngine::Core::Game::onRender
			// Access:    virtual public 
			// Returns:   void
			// Qualifier:
			// Parameter: Graphics::Renderer & renderer
			// Parameter: uint32_t imageIndex
			//************************************
			virtual void onRender(Graphics::Renderer& renderer, uint32_t imageIndex) = 0;
			
			//************************************
			// Method:    afterRender
			// FullName:  GFXEngine::Core::Game::afterRender
			// Access:    virtual public 
			// Returns:   void
			// Qualifier:
			// Parameter: Graphics::Renderer & renderer
			// Parameter: uint32_t imageIndex
			//************************************
			virtual void afterRender(Graphics::Renderer& renderer, uint32_t imageIndex) = 0;
			
			//************************************
			// Method:    onDestroy
			// FullName:  GFXEngine::Core::Game::onDestroy
			// Access:    virtual public 
			// Returns:   void
			// Qualifier:
			// Parameter: Graphics::Renderer & renderer
			//************************************
			virtual void onDestroy(Graphics::Renderer& renderer) = 0;
			
			//************************************
			// Method:    onInput
			// FullName:  GFXEngine::Core::Game::onInput
			// Access:    virtual public 
			// Returns:   void
			// Qualifier:
			// Parameter: int key
			// Parameter: int mods
			// Parameter: int action
			//************************************
			virtual void onInput(int key, int mods, int action) = 0;
			
			//************************************
			// Method:    onMouseInput
			// FullName:  GFXEngine::Core::Game::onMouseInput
			// Access:    virtual public 
			// Returns:   void
			// Qualifier:
			// Parameter: int button
			// Parameter: int mods
			// Parameter: int action
			//************************************
			virtual void onMouseInput(int button, int mods, int action) = 0;
			
			//************************************
			// Method:    onMouseMove
			// FullName:  GFXEngine::Core::Game::onMouseMove
			// Access:    virtual public 
			// Returns:   void
			// Qualifier:
			// Parameter: double xpos
			// Parameter: double ypos
			//************************************
			virtual void onMouseMove(double xpos, double ypos) = 0;
			
			//************************************
			// Method:    onScroll
			// FullName:  GFXEngine::Core::Game::onScroll
			// Access:    virtual public 
			// Returns:   void
			// Qualifier:
			// Parameter: double xoffset
			// Parameter: double yoffset
			//************************************
			virtual void onScroll(double xoffset, double yoffset) = 0;
			
			//************************************
			// Method:    onSwapchainRecreate
			// FullName:  GFXEngine::Core::Game::onSwapchainRecreate
			// Access:    virtual public 
			// Returns:   void
			// Qualifier:
			// Parameter: Graphics::Renderer & renderer
			//************************************
			virtual void onSwapchainRecreate(Graphics::Renderer& renderer) = 0;
			
			//************************************
			// Method:    afterSwapchainRecreate
			// FullName:  GFXEngine::Core::Game::afterSwapchainRecreate
			// Access:    virtual public 
			// Returns:   void
			// Qualifier:
			// Parameter: Graphics::Renderer & renderer
			// Parameter: VkViewport viewport
			// Parameter: VkRect2D scissor
			//************************************
			virtual void afterSwapchainRecreate(Graphics::Renderer& renderer, VkViewport viewport, VkRect2D scissor) = 0;

			//************************************
			// Method:    loadAssets
			// FullName:  GFXEngine::Core::Game::loadAssets
			// Access:    virtual public 
			// Returns:   void
			// Qualifier:
			// Parameter: AssetManager & assetManager
			//************************************
			virtual void loadAssets(AssetManager& assetManager) {}
			
			//************************************
			// Method:    registerBehaviors
			// FullName:  GFXEngine::Core::Game::registerBehaviors
			// Access:    virtual public 
			// Returns:   void
			// Qualifier:
			// Parameter: BehaviorRegistry & behaviorRegistry
			//************************************
			virtual void registerBehaviors(BehaviorRegistry& behaviorRegistry) {}
			
			//************************************
			// Method:    getWindowSize
			// FullName:  GFXEngine::Core::Game::getWindowSize
			// Access:    public 
			// Returns:   glm::ivec2
			// Qualifier: const
			//************************************
			glm::ivec2 getWindowSize() const { return m_windowSize; }
			
			//************************************
			// Method:    getCursorPos
			// FullName:  GFXEngine::Core::Game::getCursorPos
			// Access:    public 
			// Returns:   glm::vec2
			// Qualifier: const
			//************************************
			glm::vec2 getCursorPos() const;
			
			//************************************
			// Method:    getWindow
			// FullName:  GFXEngine::Core::Game::getWindow
			// Access:    public 
			// Returns:   GLFWwindow*
			// Qualifier: const
			//************************************
			GLFWwindow* getWindow() const { return m_window; }
			
			//************************************
			// Method:    getDeltaTime
			// FullName:  GFXEngine::Core::Game::getDeltaTime
			// Access:    public 
			// Returns:   float
			// Qualifier: const
			//************************************
			float getDeltaTime() const { return m_deltaTime; }
			
			//************************************
			// Method:    getTime
			// FullName:  GFXEngine::Core::Game::getTime
			// Access:    public 
			// Returns:   float
			// Qualifier: const
			//************************************
			float getTime() const { return m_lastFrameTime; }
			
			//************************************
			// Method:    getFPS
			// FullName:  GFXEngine::Core::Game::getFPS
			// Access:    public 
			// Returns:   float
			// Qualifier: const
			//************************************
			float getFPS() const { return (m_deltaTime > 0.0f) ? (1.0f / m_deltaTime) : 0.0f; }
			
			//************************************
			// Method:    getTargetFPS
			// FullName:  GFXEngine::Core::Game::getTargetFPS
			// Access:    public 
			// Returns:   float
			// Qualifier: const
			//************************************
			float getTargetFPS() const { return m_targetFPS; }
			
			//************************************
			// Method:    createSerializationContext
			// FullName:  GFXEngine::Core::Game::createSerializationContext
			// Access:    public 
			// Returns:   GFXEngine::SerializationContext
			// Qualifier:
			//************************************
			SerializationContext createSerializationContext() {	return SerializationContext(*assetManager, *behaviorRegistry, *entityFactory); }
			
			//************************************
			// Method:    isResizable
			// FullName:  GFXEngine::Core::Game::isResizable
			// Access:    public 
			// Returns:   bool
			// Qualifier: const
			//************************************
			bool isResizable() const { return m_resizable; }

			//************************************
			// Method:    setTargetFPS
			// FullName:  GFXEngine::Core::Game::setTargetFPS
			// Access:    public 
			// Returns:   void
			// Qualifier:
			// Parameter: float fps
			//************************************
			void setTargetFPS(float fps) { m_targetFPS = fps; }
			
			//************************************
			// Method:    setResizable
			// FullName:  GFXEngine::Core::Game::setResizable
			// Access:    public 
			// Returns:   void
			// Qualifier:
			// Parameter: bool resizable
			//************************************
			void setResizable(bool resizable) { m_resizable = resizable; }

			//************************************
			// Method:    setResizable
			// FullName:  GFXEngine::Core::Game::setResizable
			// Access:    public 
			// Returns:   void
			// Qualifier:
			// Parameter: std::unique_ptr<BackgroundTask> task
			// Parameter: TaskCompletionCallback completionCallback
			//************************************
			void StartBackgroundTask(std::unique_ptr<BackgroundTask> task, TaskCompletionCallback completionCallback);
		};
	}
}
