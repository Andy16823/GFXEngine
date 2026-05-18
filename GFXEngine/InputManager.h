#pragma once
#include "GLFW/glfw3.h"
#include "Glm/glm.hpp"

namespace GFXEngine {
	class InputManager
	{
	private:
		GLFWwindow* m_window;

	public:
		InputManager(GLFWwindow* window) : m_window(window) {}
		~InputManager() = default;

		bool isKeyPressed(int key) const;
		bool isKeyReleased(int key) const;
		bool isMouseButtonPressed(int button) const;
		bool isMouseButtonReleased(int button) const;
		glm::vec2 getCursorPosition() const;
	};
}