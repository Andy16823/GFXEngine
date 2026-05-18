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

		/// <summary>
		/// Gizmo operation types for the transform gizmo.
		/// </summary>
		enum class GuizmoOperation {
			Translate,
			Rotate,
			Scale
		};

		/// <summary>
		/// UIContext class that manages the ImGui context and provides functions for creating UI elements and handling the transform gizmo.
		/// </summary>
		class UIContext
		{
		public:
			// Lifecycle functions
			void init(GFXEngine::Graphics::Renderer& renderer, GLFWwindow* window);
			void newFrame();
			void render(GFXEngine::Graphics::Renderer& renderer, uint32_t imageIndex);
			void dispose(GFXEngine::Graphics::Renderer& renderer);

			// Functions for managing texture descriptor sets
			VkDescriptorSet createTextureDescriptorSet(GFXEngine::Graphics::Renderer& renderer, const GFXEngine::Graphics::RenderTexture& renderTexture);
			void freeTextureDescriptorSet(GFXEngine::Graphics::Renderer& renderer, VkDescriptorSet descriptorSet);

			// Static helper functions for creating UI elements
			static void beginnFullscreen(const char* title, ImGuiWindowFlags flags = ImGuiWindowFlags_None);
			static void createButton(const char* label, const std::function<void()>& onClick);
			static void createImage(VkDescriptorSet descriptorSet, const glm::vec2& size);
			static std::string createLabelID(const std::string& base, const std::string& id);
			static std::string createLabelID(const std::string& base, uint32_t id);
			
			// Guizmo functions
			static bool transformGizmo(const glm::mat4& view, const glm::mat4& projection, glm::mat4& transform, const glm::vec4& rect, GuizmoOperation operation = GuizmoOperation::Translate);
			static bool gizmoIsOver();
			static bool gizmoIsUsing();

			// Static conversions
			static glm::vec2 toVec2(const ImVec2& v) { return glm::vec2(v.x, v.y); }
			static glm::vec4 toVec4(const ImVec4& v) { return glm::vec4(v.x, v.y, v.z, v.w); }
			static ImVec2 toImVec2(const glm::vec2& v) { return ImVec2(v.x, v.y); }
			static ImVec4 toImVec4(const glm::vec4& v) { return ImVec4(v.x, v.y, v.z, v.w); }

		private:
			VkDescriptorPool m_descriptorPool;
		};
	}

}
