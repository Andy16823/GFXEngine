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

		enum class GuizmoOperation {
			Translate,
			Rotate,
			Scale
		};

		class UIContext
		{
		private:
			VkDescriptorPool m_descriptorPool;

		public:
			//************************************
			// Method:    init
			// FullName:  GFXEngine::Core::UIContext::init
			// Access:    public 
			// Returns:   void
			// Qualifier:
			// Parameter: GFXEngine::Graphics::Renderer & renderer
			// Parameter: GLFWwindow * window
			//************************************
			void init(GFXEngine::Graphics::Renderer& renderer, GLFWwindow* window);
			
			//************************************
			// Method:    newFrame
			// FullName:  GFXEngine::Core::UIContext::newFrame
			// Access:    public 
			// Returns:   void
			// Qualifier:
			//************************************
			void newFrame();
			
			//************************************
			// Method:    render
			// FullName:  GFXEngine::Core::UIContext::render
			// Access:    public 
			// Returns:   void
			// Qualifier:
			// Parameter: GFXEngine::Graphics::Renderer & renderer
			// Parameter: uint32_t imageIndex
			//************************************
			void render(GFXEngine::Graphics::Renderer& renderer, uint32_t imageIndex);
			
			//************************************
			// Method:    dispose
			// FullName:  GFXEngine::Core::UIContext::dispose
			// Access:    public 
			// Returns:   void
			// Qualifier:
			// Parameter: GFXEngine::Graphics::Renderer & renderer
			//************************************
			void dispose(GFXEngine::Graphics::Renderer& renderer);

		public:
			//************************************
			// Method:    createTextureDescriptorSet
			// FullName:  GFXEngine::Core::UIContext::createTextureDescriptorSet
			// Access:    public 
			// Returns:   VkDescriptorSet
			// Qualifier:
			// Parameter: GFXEngine::Graphics::Renderer & renderer
			// Parameter: const GFXEngine::Graphics::RenderTexture & renderTexture
			//************************************
			VkDescriptorSet createTextureDescriptorSet(GFXEngine::Graphics::Renderer& renderer, const GFXEngine::Graphics::RenderTexture& renderTexture);
			
			//************************************
			// Method:    freeTextureDescriptorSet
			// FullName:  GFXEngine::Core::UIContext::freeTextureDescriptorSet
			// Access:    public 
			// Returns:   void
			// Qualifier:
			// Parameter: GFXEngine::Graphics::Renderer & renderer
			// Parameter: VkDescriptorSet descriptorSet
			//************************************
			void freeTextureDescriptorSet(GFXEngine::Graphics::Renderer& renderer, VkDescriptorSet descriptorSet);

		public:
			//************************************
			// Method:    beginnFullscreen
			// FullName:  GFXEngine::Core::UIContext::beginnFullscreen
			// Access:    public static 
			// Returns:   void
			// Qualifier:
			// Parameter: const char * title
			// Parameter: ImGuiWindowFlags flags
			//************************************
			static void beginnFullscreen(const char* title, ImGuiWindowFlags flags = ImGuiWindowFlags_None);
			
			//************************************
			// Method:    createButton
			// FullName:  GFXEngine::Core::UIContext::createButton
			// Access:    public static 
			// Returns:   void
			// Qualifier:
			// Parameter: const char * label
			// Parameter: const std::function<void
			// Parameter: > & onClick
			//************************************
			static void createButton(const char* label, const std::function<void()>& onClick);
			
			//************************************
			// Method:    createImage
			// FullName:  GFXEngine::Core::UIContext::createImage
			// Access:    public static 
			// Returns:   void
			// Qualifier:
			// Parameter: VkDescriptorSet descriptorSet
			// Parameter: const glm::vec2 & size
			//************************************
			static void createImage(VkDescriptorSet descriptorSet, const glm::vec2& size);
			
			//************************************
			// Method:    createLabelID
			// FullName:  GFXEngine::Core::UIContext::createLabelID
			// Access:    public static 
			// Returns:   std::string
			// Qualifier:
			// Parameter: const std::string & base
			// Parameter: const std::string & id
			//************************************
			static std::string createLabelID(const std::string& base, const std::string& id);
			
			//************************************
			// Method:    createLabelID
			// FullName:  GFXEngine::Core::UIContext::createLabelID
			// Access:    public static 
			// Returns:   std::string
			// Qualifier:
			// Parameter: const std::string & base
			// Parameter: uint32_t id
			//************************************
			static std::string createLabelID(const std::string& base, uint32_t id);
			
		public:
			//************************************
			// Method:    transformGizmo
			// FullName:  GFXEngine::Core::UIContext::transformGizmo
			// Access:    public static 
			// Returns:   bool
			// Qualifier:
			// Parameter: const glm::mat4 & view
			// Parameter: const glm::mat4 & projection
			// Parameter: glm::mat4 & transform
			// Parameter: const glm::vec4 & rect
			// Parameter: GuizmoOperation operation
			//************************************
			static bool transformGizmo(const glm::mat4& view, const glm::mat4& projection, glm::mat4& transform, const glm::vec4& rect, GuizmoOperation operation = GuizmoOperation::Translate);
			
			//************************************
			// Method:    gizmoIsOver
			// FullName:  GFXEngine::Core::UIContext::gizmoIsOver
			// Access:    public static 
			// Returns:   bool
			// Qualifier:
			//************************************
			static bool gizmoIsOver();
			
			//************************************
			// Method:    gizmoIsUsing
			// FullName:  GFXEngine::Core::UIContext::gizmoIsUsing
			// Access:    public static 
			// Returns:   bool
			// Qualifier:
			//************************************
			static bool gizmoIsUsing();

		public:
			//************************************
			// Method:    toVec2
			// FullName:  GFXEngine::Core::UIContext::toVec2
			// Access:    public static 
			// Returns:   glm::vec2
			// Qualifier:
			// Parameter: const ImVec2 & v
			//************************************
			static glm::vec2 toVec2(const ImVec2& v) { return glm::vec2(v.x, v.y); }
			
			//************************************
			// Method:    toVec4
			// FullName:  GFXEngine::Core::UIContext::toVec4
			// Access:    public static 
			// Returns:   glm::vec4
			// Qualifier:
			// Parameter: const ImVec4 & v
			//************************************
			static glm::vec4 toVec4(const ImVec4& v) { return glm::vec4(v.x, v.y, v.z, v.w); }
			
			//************************************
			// Method:    toImVec2
			// FullName:  GFXEngine::Core::UIContext::toImVec2
			// Access:    public static 
			// Returns:   ImVec2
			// Qualifier:
			// Parameter: const glm::vec2 & v
			//************************************
			static ImVec2 toImVec2(const glm::vec2& v) { return ImVec2(v.x, v.y); }
			
			//************************************
			// Method:    toImVec4
			// FullName:  GFXEngine::Core::UIContext::toImVec4
			// Access:    public static 
			// Returns:   ImVec4
			// Qualifier:
			// Parameter: const glm::vec4 & v
			//************************************
			static ImVec4 toImVec4(const glm::vec4& v) { return ImVec4(v.x, v.y, v.z, v.w); }
		};
	}

}
