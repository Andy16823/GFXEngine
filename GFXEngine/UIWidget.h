#pragma once
#include "Renderer.h"
#include "UIContext.h"
#include "InputManager.h"
#include <string>
#include "Utils.h"

namespace GFXEngine {
	namespace Core {

		class UIWidget {
		private:
			bool m_isVisible = false;
			std::string m_name;
			std::string m_uuid;

		public:

			UIWidget() : m_uuid(Utils::generateUUID()) {}
			virtual ~UIWidget() = default;

			virtual void init(UIContext& context, GFXEngine::Graphics::Renderer& renderer) = 0;
			virtual void handleInput(GLFWwindow* window, int key, int mods, int action) = 0;
			virtual void handleMouseInput(GLFWwindow* window, int button, int mods, int action) = 0;
			virtual void handleMouseMove(GLFWwindow* window, double xpos, double ypos) = 0;
			virtual void update(UIContext& context, InputManager& input, float deltaTime) = 0;
			virtual void beforeRender(UIContext& context, GFXEngine::Graphics::Renderer& renderer, uint32_t imageIndex) = 0;
			virtual void render(UIContext& context, GFXEngine::Graphics::Renderer& renderer, uint32_t imageIndex) = 0;
			virtual void afterRender(UIContext& context, GFXEngine::Graphics::Renderer& renderer, uint32_t imageIndex) = 0;
			virtual void dispose(UIContext& context, GFXEngine::Graphics::Renderer& renderer) = 0;

			const std::string& getName() const { return m_name; };
			const std::string& getUUID() const { return m_uuid; };
			bool isVisible() const { return m_isVisible; }

			void setName(const std::string& name) { m_name = name; }
			void setVisible(bool visible) {	m_isVisible = visible; }
			void show() { m_isVisible = true; }
			void hide() { m_isVisible = false; }
			void toggle() {	m_isVisible = !m_isVisible; }
		};
	}
}