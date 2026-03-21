#pragma once
#include "Renderer.h"
#include "GLFW/glfw3.h"
#include <functional>
#include "RenderTexture.h"
#include "imgui.h"
#include <vector>
#include "glm/glm.hpp"

namespace GFXEngine {
	namespace Core {
		class GFXGui
		{
		public:
			void init(GFXEngine::Graphics::Renderer& renderer, GLFWwindow* window);
			ImTextureID createTexture(GFXEngine::Graphics::Renderer& renderer, const GFXEngine::Graphics::RenderTexture& renderTexture);
			VkDescriptorSet createTextureDescriptorSet(GFXEngine::Graphics::Renderer& renderer, const GFXEngine::Graphics::RenderTexture& renderTexture);
			void newFrame();

			void beginUI(const char* title);
			void createText(const char* text);
			void createButton(const char* label, const std::function<void()>& onClick);
			void createImage(ImTextureID textureId, const glm::vec2& size);
			void createImage(VkDescriptorSet descriptorSet, const glm::vec2& size);
			void endUI();
			void render(GFXEngine::Graphics::Renderer& renderer, uint32_t imageIndex);
			void dispose(GFXEngine::Graphics::Renderer& renderer);


		private:
			VkDescriptorPool m_descriptorPool;
		};
	}
}
