#pragma once
#include "Renderer.h"
#include "GLFW/glfw3.h"
#include <functional>
#include "RenderTexture.h"
#include <vector>
#include "glm/glm.hpp"

namespace GFXEngine {
	namespace Core {

		/// <summary>
		/// Wrapper class for ImGui integration with Vulkan and GLFW. 
		/// Provides functions to initialize ImGui, create UI elements, 
		/// and render the UI within the Vulkan rendering loop.
		/// </summary>
		class GFXGui
		{
		public:
			// Base functions
			void init(GFXEngine::Graphics::Renderer& renderer, GLFWwindow* window);
			void newFrame();
			void beginUI(const char* title);
			void endUI();
			void render(GFXEngine::Graphics::Renderer& renderer, uint32_t imageIndex);
			void dispose(GFXEngine::Graphics::Renderer& renderer);

			// UI element creation functions
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
			void createColorInput(const char* label, glm::vec4* color);
			void createColorInput(const char* label, glm::vec3* color);

			// Utility functions
			VkDescriptorSet createTextureDescriptorSet(GFXEngine::Graphics::Renderer& renderer, const GFXEngine::Graphics::RenderTexture& renderTexture);
			glm::vec2 getClientAreaSize() const;
			glm::vec2 getWindowPosition() const;
		private:
			VkDescriptorPool m_descriptorPool;
		};
	}
}
