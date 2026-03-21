#pragma once
#include "Renderer.h"
#include "GLFW/glfw3.h"

namespace GFXEngine {
	namespace Core {
		class GFXGui
		{
		public:
			void init(GFXEngine::Graphics::Renderer& renderer, GLFWwindow* window);
			void newFrame();
			void buildGui();
			void render(GFXEngine::Graphics::Renderer& renderer, uint32_t imageIndex);
			void dispose(GFXEngine::Graphics::Renderer& renderer);


		private:
			VkDescriptorPool m_descriptorPool;

		};
	}
}
