#pragma once
#include "Renderer.h"
#include "GLFW/glfw3.h"
#include <functional>
#include "RenderTexture.h"
#include <vector>
#include "glm/glm.hpp"

namespace GFXEngine {
	namespace Core {
		class GFXGui
		{
		public:
			void init(GFXEngine::Graphics::Renderer& renderer, GLFWwindow* window);
			VkDescriptorSet createTextureDescriptorSet(GFXEngine::Graphics::Renderer& renderer, const GFXEngine::Graphics::RenderTexture& renderTexture);
			void newFrame();

			void beginUI(const char* title);
			bool createCollapsingHeader(const char* label);
			void createText(const char* text);
			void createButton(const char* label, const std::function<void()>& onClick);
			void createImage(VkDescriptorSet descriptorSet, const glm::vec2& size);
			void createFloatSlider(const char* label, float* value, float min, float max);
			void createCheckbox(const char* label, bool* value);
			void createNumberInput(const char* label, int* value);
			void createFloatInput(const char* label, float* value);
			void createTextInput(const char* label, char* buffer, size_t bufferSize);
			void createVector3Input(const char* label, glm::vec3* value);
			void createVector4Input(const char* label, glm::vec4* value);
			void endUI();
			void render(GFXEngine::Graphics::Renderer& renderer, uint32_t imageIndex);
			void dispose(GFXEngine::Graphics::Renderer& renderer);


		private:
			VkDescriptorPool m_descriptorPool;
		};
	}
}
