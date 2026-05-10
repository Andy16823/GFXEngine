#pragma once
#include "Renderer.h"
#include "GLFW/glfw3.h"
#include <functional>
#include "RenderTexture.h"
#include <vector>
#include "glm/glm.hpp"
#include "imgui_internal.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_vulkan.h"

namespace GFXEngine {
	namespace Core {

		class GFXGui
		{
		public:
			enum class GuizmoOperation {
				Translate,
				Rotate,
				Scale
			};

		public:
			// Base functions
			void init(GFXEngine::Graphics::Renderer& renderer, GLFWwindow* window);
			void newFrame();
			void beginnFullscreen(const char* title, ImGuiWindowFlags flags = ImGuiWindowFlags_None);
			void render(GFXEngine::Graphics::Renderer& renderer, uint32_t imageIndex);
			void dispose(GFXEngine::Graphics::Renderer& renderer);

			// UI element creation functions
			void createButton(const char* label, const std::function<void()>& onClick);
			void createImage(VkDescriptorSet descriptorSet, const glm::vec2& size);

			bool transformGizmo(const glm::mat4& view, const glm::mat4& projection, glm::mat4& transform, const glm::vec4& rect, GuizmoOperation operation = GuizmoOperation::Translate);
			bool gizmoIsOver();
			bool gizmoIsUsing();

			// Utility functions
			VkDescriptorSet createTextureDescriptorSet(GFXEngine::Graphics::Renderer& renderer, const GFXEngine::Graphics::RenderTexture& renderTexture);
			void freeTextureDescriptorSet(GFXEngine::Graphics::Renderer& renderer, VkDescriptorSet descriptorSet);
		private:
			VkDescriptorPool m_descriptorPool;
		};
	}

}
