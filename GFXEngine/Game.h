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
#include "FrameContext.h"

namespace GFXEngine {
	namespace Core {
		class Game
		{
		private:
			GLFWwindow* m_window = nullptr;
			std::unique_ptr<Graphics::Renderer> m_renderer;
            std::unique_ptr<Graphics::FrameContext> m_frameContext;
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
			/// <summary>
			/// Creates a new instance of the Game class
			/// </summary>
			Game() = default;
			
			/// <summary>
			/// Default destructor for the Game class.
			/// </summary>
			virtual ~Game() = default;

			/// <summary>
			/// Starts the game by creating a window, 
			/// initializing the renderer, and entering the main game loop.
			/// </summary>
			/// <param name="width">The width of the game window.</param>
			/// <param name="height">The height of the game window.</param>
			/// <param name="shadersDirectory">The directory where shader files are located.</param>
			/// <param name="title">The title of the game window.</param>
			/// <param name="fullscreen">Whether the game should start in fullscreen mode.</param>
			/// <param name="validationLayers">Whether to enable validation layers for debugging.</param>
			void start(uint32_t width, uint32_t height, const std::string& shadersDirectory, const std::string& title = "My Game", bool fullscreen = false, bool validationLayers = true);

			/// <summary>
			/// Initialize lifecycle method called before the game starts
			/// allowing for custom initialization logic.
			/// </summary>
			/// <param name="renderer">The renderer instance.</param>
			virtual void onInit(Graphics::Renderer& renderer) = 0;
			
			/// <summary>
			/// OnStart lifecycle method called after the game has been initialized,
			/// but before the main game loop starts, allowing for custom setup logic.
			/// </summary>
			/// <param name="renderer"></param>
			virtual void onStart(Graphics::Renderer& renderer) = 0;
			
			/// <summary>
			/// Update lifecycle method called once per frame, 
			/// allowing for custom game logic and state updates.
			/// </summary>
			/// <param name="renderer">The renderer instance.</param>
			/// <param name="imageIndex">The index of the current image being rendered.</param>
			/// <param name="deltaTime">The time elapsed since the last frame.</param>
			virtual void onUpdate(Graphics::Renderer& renderer, uint32_t imageIndex, float deltaTime) = 0;
			
			/// <summary>
			/// BeforeRender lifecycle method called before rendering each frame,
			/// allowing for custom logic to be executed prior to rendering.
			/// </summary>
			/// <param name="renderer">The renderer instance.</param>
			/// <param name="imageIndex">The index of the current image being rendered.</param>
			virtual void beforeRender(Graphics::Renderer& renderer, uint32_t imageIndex) = 0;
			
			/// <summary>
			/// OnRender lifecycle method called during the rendering phase of each frame,
			/// allowing for custom rendering logic to be executed.
			/// </summary>
			/// <param name="renderer">The renderer instance.</param>
			/// <param name="frameContext">The frame context.</param>
			/// <param name="imageIndex">The index of the current image being rendered.</param>
			virtual void onRender(Graphics::Renderer& renderer, Graphics::FrameContext& frameContext, uint32_t imageIndex) = 0;
			
			/// <summary>
			/// AfterRender lifecycle method called after rendering each frame,
			/// allowing for custom logic to be executed after rendering.
			/// </summary>
			/// <param name="renderer">The renderer instance.</param>
			/// <param name="imageIndex">The index of the current image being rendered.</param>
			virtual void afterRender(Graphics::Renderer& renderer, uint32_t imageIndex) = 0;
			
			/// <summary>
			/// OnDestroy lifecycle method called when the game is being destroyed,
			/// allowing for custom cleanup logic to be executed.
			/// </summary>
			/// <param name="renderer">The renderer instance.</param>
			virtual void onDestroy(Graphics::Renderer& renderer) = 0;
			
            /// <summary>
			/// OnInput lifecycle method called when a key input event occurs,
			/// allowing for custom input handling logic to be executed.
            /// </summary>
            /// <param name="key">The key that was pressed or released.</param>
            /// <param name="scancode">The system-specific scancode of the key.</param>
            /// <param name="action">The action performed (press, release, repeat).</param>
            /// <param name="mods">Bit field describing which modifier keys were held down.</param>
            virtual void onInput(int key, int scancode, int action, int mods) = 0;
			
			/// <summary>
			/// OnMouseInput lifecycle method called when a mouse button input event occurs,
			/// allowing for custom mouse input handling logic to be executed.
			/// </summary>
			/// <param name="button">The mouse button that was pressed or released.</param>
			/// <param name="action">The action performed (press, release).</param>
			/// <param name="mods">Bit field describing which modifier keys were held down.</param>
			virtual void onMouseInput(int button, int action, int mods) = 0;
			
			/// <summary>
			/// OnMouseMove lifecycle method called when the mouse is moved,
			/// allowing for custom mouse movement handling logic to be executed.
			/// </summary>
			/// <param name="xpos">The new x-coordinate of the mouse cursor.</param>
			/// <param name="ypos">The new y-coordinate of the mouse cursor.</param>
			virtual void onMouseMove(double xpos, double ypos) = 0;
			
			/// <summary>
			/// OnScroll lifecycle method called when the mouse scroll wheel is used
			/// </summary>
			/// <param name="xoffset"></param>
			/// <param name="yoffset"></param>
			virtual void onScroll(double xoffset, double yoffset) = 0;
			
			/// <summary>
			/// OnSwapchainRecreate lifecycle method called when the swapchain is recreated.
			/// </summary>
			/// <param name="renderer"></param>
			virtual void onSwapchainRecreate(Graphics::Renderer& renderer) = 0;
			
			/// <summary>
			/// AfterSwapchainRecreate lifecycle method called after the swapchain has been recreated
			/// </summary>
			/// <param name="renderer"></param>
			/// <param name="viewport"></param>
			/// <param name="scissor"></param>
			virtual void afterSwapchainRecreate(Graphics::Renderer& renderer, VkViewport viewport, VkRect2D scissor) = 0;

			/// <summary>
			/// Load assets lifecycle method called to load game assets such as textures, models, and materials.
			/// </summary>
			/// <param name="assetManager"></param>
			virtual void loadAssets(AssetManager& assetManager) {}
			
			/// <summary>
			/// Register behaviors lifecycle method called to register game behaviors and 
			/// components with the behavior registry.
			/// </summary>
			/// <param name="behaviorRegistry"></param>
			virtual void registerBehaviors(BehaviorRegistry& behaviorRegistry) {}
			
			/// <summary>
			/// Gets the current size of the game window as a 2D vector (width, height).
			/// </summary>
			/// <returns></returns>
			glm::ivec2 getWindowSize() const { return m_windowSize; }
			
			/// <summary>
			/// Gets the current position of the cursor within the game window as a 2D vector (x, y).
			/// </summary>
			/// <returns></returns>
			glm::vec2 getCursorPos() const;
			
			/// <summary>
			/// Gets the GLFW window associated with the game, allowing for direct interaction with the windowing system.
			/// </summary>
			/// <returns></returns>
			GLFWwindow* getWindow() const { return m_window; }

			/// <summary>
			/// Gets the FrameContext used for managing per-frame resources and data.
			/// </summary>
			/// <returns></returns>
			Graphics::FrameContext& getFrameContext() { return *m_frameContext; }
			
			/// <summary>
			/// Gets the time elapsed since the last frame.
			/// </summary>
			/// <returns></returns>
			float getDeltaTime() const { return m_deltaTime; }
			
			/// <summary>
			/// Gets the time of the last frame, allowing for timing and frame rate calculations.
			/// </summary>
			/// <returns></returns>
			float getTime() const { return m_lastFrameTime; }
			
			/// <summary>
			/// Gets the current frames per second (FPS) based on the delta time.
			/// </summary>
			/// <returns></returns>
			float getFPS() const { return (m_deltaTime > 0.0f) ? (1.0f / m_deltaTime) : 0.0f; }
			
			/// <summary>
			/// Gets the target frames per second (FPS) set for the game.
			/// </summary>
			/// <returns></returns>
			float getTargetFPS() const { return m_targetFPS; }

			/// <summary>
			/// Gets the renderer instance used for rendering graphics in the game.
			/// </summary>
			/// <returns></returns>
			GFXEngine::Graphics::Renderer* getRenderer() const { return m_renderer.get(); }
			
			/// <summary>
			/// Creates a SerializationContext for managing serialization and deserialization of game assets, behaviors, and entities.
			/// </summary>
			/// <returns></returns>
			SerializationContext createSerializationContext() {	return SerializationContext(*assetManager, *behaviorRegistry, *entityFactory); }
			
			/// <summary>
			/// Checks if the game window is resizable.
			/// </summary>
			/// <returns></returns>
			bool isResizable() const { return m_resizable; }

			/// <summary>
			/// Sets the target frames per second (FPS) for the game.
			/// </summary>
			/// <param name="fps"></param>
			void setTargetFPS(float fps) { m_targetFPS = fps; }
			
			/// <summary>
			/// Sets whether the game window is resizable.
			/// </summary>
			/// <param name="resizable"></param>
			void setResizable(bool resizable) { m_resizable = resizable; }

			/// <summary>
			/// Starts a background task for asynchronous execution.
			/// </summary>
			/// <param name="task"></param>
			/// <param name="completionCallback"></param>
			void StartBackgroundTask(std::unique_ptr<BackgroundTask> task, TaskCompletionCallback completionCallback);

			/// <summary>
			/// Gets the current viewport of the game window as a 4D vector (x, y, width, height).
			/// </summary>
			/// <returns></returns>
			glm::vec4 getWindowViewport() const;
		};
	}
}
