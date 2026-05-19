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

namespace GFXEngine {
	namespace Core {
		class Game
		{
		public:
			Game() = default;
			virtual ~Game() = default;

			std::unique_ptr<ServiceManager> serviceManager = std::make_unique<ServiceManager>();
			std::unique_ptr<AssetManager> assetManager = std::make_unique<AssetManager>();
			std::unique_ptr<BehaviorRegistry> behaviorRegistry = std::make_unique<BehaviorRegistry>();
			std::unique_ptr<EntityFactory> entityFactory = std::make_unique<EntityFactory>();
			std::unique_ptr<InputManager> inputManager = std::make_unique<InputManager>();

			// Non-virtual function to start the game loop
			void start(uint32_t width, uint32_t height, const std::string& shadersDirectory, const std::string& title = "My Game", bool fullscreen = false, bool validationLayers = true);

			// Main functions to be implemented by the user
			virtual void onInit(Graphics::Renderer& renderer) = 0;
			virtual void onStart(Graphics::Renderer& renderer) = 0;
			virtual void onUpdate(Graphics::Renderer& renderer, uint32_t imageIndex, float deltaTime) = 0;
			virtual void beforeRender(Graphics::Renderer& renderer, uint32_t imageIndex) = 0;
			virtual void onRender(Graphics::Renderer& renderer, uint32_t imageIndex) = 0;
			virtual void afterRender(Graphics::Renderer& renderer, uint32_t imageIndex) = 0;
			virtual void onDestroy(Graphics::Renderer& renderer) = 0;
			virtual void onInput(int key, int mods, int action) = 0;
			virtual void onMouseInput(int button, int mods, int action) = 0;
			virtual void onMouseMove(double xpos, double ypos) = 0;
			virtual void onScroll(double xoffset, double yoffset) = 0;
			virtual void onSwapchainRecreate(Graphics::Renderer& renderer) = 0;
			virtual void afterSwapchainRecreate(Graphics::Renderer& renderer, VkViewport viewport, VkRect2D scissor) = 0;

			// Optional overrides for asset loading and behavior registration
			virtual void loadAssets(AssetManager& assetManager) {}
			virtual void registerBehaviors(BehaviorRegistry& behaviorRegistry) {}
			
			// Getters
			glm::ivec2 getWindowSize() const { return m_windowSize; }
			glm::vec2 getCursorPos() const;
			GLFWwindow* getWindow() const { return m_window; }
			float getDeltaTime() const { return m_deltaTime; }
			float getTime() const { return m_lastFrameTime; }
			float getFPS() const { return (m_deltaTime > 0.0f) ? (1.0f / m_deltaTime) : 0.0f; }
			float getTargetFPS() const { return m_targetFPS; }
			SerializationContext createSerializationContext() {	return SerializationContext(*assetManager, *behaviorRegistry, *entityFactory); }
			bool isResizable() const { return m_resizable; }

			// Setters
			void setTargetFPS(float fps) { m_targetFPS = fps; }
			void setResizable(bool resizable) { m_resizable = resizable; }

		private:
			GLFWwindow* m_window = nullptr;
			std::unique_ptr<Graphics::Renderer> m_renderer;
			glm::ivec2 m_windowSize = { 800, 600 };
			float m_targetFPS = 120.0f;
			float m_lastFrameTime = 0.0f;
			float m_deltaTime = 0.0f;
			bool m_resizable = false;
		};
	}
}
