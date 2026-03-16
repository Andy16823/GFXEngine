#pragma once
#include "Renderer.h"
#include "Camera.h"
#include "LibGFX.h"
#include "DataTypes.h"

namespace GFXEngine {
	namespace Core {
		class Game
		{
		public:

			Game() = default;
			~Game() = default;

			void start(uint32_t width, uint32_t height, const std::string& title = "My Game", bool validationLayers = true);

			virtual void onInit(Graphics::Renderer& renderer) = 0;
			virtual void onStart(Graphics::Renderer& renderer) = 0;
			virtual void onUpdate(Graphics::Renderer& renderer, uint32_t imageIndex, float deltaTime) = 0;
			virtual void onRender(Graphics::Renderer& renderer, uint32_t imageIndex) = 0;
			virtual void onDestroy(Graphics::Renderer& renderer) = 0;
			virtual void onInput(int key, int mods, int action) = 0;
			

			glm::ivec2 getWindowSize() const { return m_windowSize; }
			glm::vec2 getCursorPos() const;
			GLFWwindow* getWindow() const { return m_window; }
			float getDeltaTime() const { return m_deltaTime; }
			float getTime() const { return m_lastFrameTime; }
			float getFPS() const { return (m_deltaTime > 0.0f) ? (1.0f / m_deltaTime) : 0.0f; }
			float getTargetFPS() const { return m_targetFPS; }

			void setTargetFPS(float fps) { m_targetFPS = fps; }

		private:
			GLFWwindow* m_window = nullptr;
			std::unique_ptr<Graphics::Renderer> m_renderer;
			glm::ivec2 m_windowSize = { 800, 600 };
			float m_targetFPS = 120.0f;
			float m_lastFrameTime = 0.0f;
			float m_deltaTime = 0.0f;
		};
	}
}
