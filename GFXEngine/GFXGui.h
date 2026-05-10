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
			enum class WindowFlags : int
			{
				None = 0,
				NoTitleBar = 1 << 0,
				NoResize = 1 << 1,
				NoMove = 1 << 2,
				NoScrollbar = 1 << 3,
				NoScrollWithMouse = 1 << 4,
				NoCollapse = 1 << 5,
				AlwaysAutoResize = 1 << 6,
				NoBackground = 1 << 7,
				NoSavedSettings = 1 << 8,
				NoMouseInputs = 1 << 9,
				MenuBar = 1 << 10,
				HorizontalScrollbar = 1 << 11,
				NoFocusOnAppearing = 1 << 12,
				NoBringToFrontOnFocus = 1 << 13,
				AlwaysVerticalScrollbar = 1 << 14,
				AlwaysHorizontalScrollbar = 1 << 15,
				NoNavInputs = 1 << 16,
				NoNavFocus = 1 << 17,
				UnsavedDocument = 1 << 18,
				NoDocking = 1 << 19,
				NoNav = 1 << 20,
				NoDecoration = 1 << 21,
				NoInputs = 1 << 22
			};

			enum class DockingNodeSlot {
				Left = 0,
				Right = 1,
				Up = 2,
				Down = 3
			};

		public:
			// Base functions
			void init(GFXEngine::Graphics::Renderer& renderer, GLFWwindow* window);
			void newFrame();
			void beginUI(const char* title, bool docking = false, WindowFlags flags = WindowFlags::None);
			void endUI();
			void render(GFXEngine::Graphics::Renderer& renderer, uint32_t imageIndex);
			void dispose(GFXEngine::Graphics::Renderer& renderer);

			// UI element creation functions
			bool createCollapsingHeader(const char* label);
			bool createTreeNode(const char* label);
			bool createSelectable(const char* label, bool selected = false);
			void createTreePop();
			void createSameLine();
			void createText(const char* text);
			void createButton(const char* label, const std::function<void()>& onClick);
			void createImage(VkDescriptorSet descriptorSet, const glm::vec2& size);
			void createFloatSlider(const char* label, float* value, float min, float max);
			void createCheckbox(const char* label, bool* value);
			void createNumberInput(const char* label, int* value);
			void createFloatInput(const char* label, float* value);
			void createTextInput(const char* label, char* buffer, size_t bufferSize);
			void createTextAreaInput(const char* label, char* buffer, size_t bufferSize);
			void createVectorInput(const char* label, glm::vec2* value);
			void createVectorInput(const char* label, glm::vec3* value);
			void createVectorInput(const char* label, glm::vec4* value);
			void createQuatInput(const char* label, glm::quat* value);
			void createColorInput(const char* label, glm::vec4* color);
			void createColorInput(const char* label, glm::vec3* color);
			void createDockingSpace(const char* id);		
			void createDockingSpace(uint32_t id);
			void dockbuilderRemoveNode(uint32_t nodeID);
			void dockbuilderAddNode(uint32_t nodeID);
			void dockbuilderSetNodeSize(uint32_t nodeID, const glm::vec2& size);
			uint32_t dockbuilderSplitNode(uint32_t nodeID, DockingNodeSlot splitDir, float splitRatio, uint32_t* outIDAtDir = nullptr, uint32_t* outIDAtOppositeDir = nullptr);
			void dockbuilderDockWindow(const char* windowLabel, uint32_t nodeID);
			void dockbuilderFinish(uint32_t nodeID);

			bool transformGizmo(const glm::mat4& view, const glm::mat4& projection, glm::mat4& transform, const glm::vec4& rect);
			bool gizmoIsOver();
			bool gizmoIsUsing();

			// Utility functions
			VkDescriptorSet createTextureDescriptorSet(GFXEngine::Graphics::Renderer& renderer, const GFXEngine::Graphics::RenderTexture& renderTexture);
			void freeTextureDescriptorSet(GFXEngine::Graphics::Renderer& renderer, VkDescriptorSet descriptorSet);

			// Setters
			void setWindowPosition(const glm::vec2& position);
			void setWindowSize(const glm::vec2& size);

			// Getters
			glm::vec2 getClientAreaSize() const;
			glm::vec2 getWindowPosition() const;
			glm::vec2 getCursorScreenPos() const;
			glm::vec2 getCursorPos() const;
			glm::vec2 getMousePos() const;
			uint32_t getID(const char* label) const;
		private:
			VkDescriptorPool m_descriptorPool;
		};

		// Operator overloads AUSSERHALB der Klasse
		inline GFXGui::WindowFlags operator|(GFXGui::WindowFlags a, GFXGui::WindowFlags b)
		{
			return static_cast<GFXGui::WindowFlags>(static_cast<int>(a) | static_cast<int>(b));
		}

		inline GFXGui::WindowFlags operator&(GFXGui::WindowFlags a, GFXGui::WindowFlags b)
		{
			return static_cast<GFXGui::WindowFlags>(static_cast<int>(a) & static_cast<int>(b));
		}
	}

}
