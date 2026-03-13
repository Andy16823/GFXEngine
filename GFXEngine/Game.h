#pragma once
#include "Renderer.h"
#include "Camera.h"
#include "LibGFX.h"

namespace GFXEngine {
	namespace Core {
		class Game
		{
		public:

			Game() = default;
			~Game() = default;

			void start(uint32_t width, uint32_t height, const std::string& title = "My Game", bool validationLayers = true);

			virtual void onInit(Graphics::Renderer& renderer) = 0;
			virtual void onUpdate(Graphics::Renderer& renderer, uint32_t imageIndex, float deltaTime) = 0;
			virtual void onRender(Graphics::Renderer& renderer, uint32_t imageIndex) = 0;
			virtual void onDestroy(Graphics::Renderer& renderer) = 0;
			virtual void onKeyDown(int key, int mods) = 0;
			virtual void onKeyUp(int key, int mods) = 0;

			glm::ivec2 getWindowSize() const { return m_windowSize; }
			GLFWwindow* getWindow() const { return m_window; }

		private:
			GLFWwindow* m_window = nullptr;
			std::unique_ptr<Graphics::Renderer> m_renderer;
			glm::ivec2 m_windowSize = { 800, 600 };
		};
	}
}
