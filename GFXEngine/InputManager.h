#pragma once
#include "GLFW/glfw3.h"
#include "Glm/glm.hpp"
#include <functional>
#include <unordered_map>

namespace GFXEngine {
	class InputManager
	{
	private:
		using InputCallback = std::function<void(int key, int mods, int action)>;
		using MouseButtonCallback = std::function<void(int button, int mods, int action)>;
		using MouseMoveCallback = std::function<void(double xpos, double ypos)>;
		using ScrollCallback = std::function<void(double xoffset, double yoffset)>;

	private:
		GLFWwindow* m_window;
		std::unordered_map<uint32_t, InputCallback> m_inputCallbacks;
		std::unordered_map<uint32_t, MouseButtonCallback> m_mouseButtonCallbacks;
		std::unordered_map<uint32_t, MouseMoveCallback> m_mouseMoveCallbacks;
		std::unordered_map<uint32_t, ScrollCallback> m_scrollCallbacks;
		uint32_t m_nextCallbackId = 0;

		uint32_t generateCallbackId() {	return m_nextCallbackId++; }
	public:
		InputManager(GLFWwindow* window) : m_window(window) {}
		~InputManager() = default;

		bool isKeyPressed(int key) const;
		bool isKeyReleased(int key) const;
		bool isMouseButtonPressed(int button) const;
		bool isMouseButtonReleased(int button) const;
		glm::vec2 getCursorPosition() const;

		uint32_t registerInputCallback(const InputCallback& callback);
		uint32_t registerMouseButtonCallback(const MouseButtonCallback& callback);
		uint32_t registerMouseMoveCallback(const MouseMoveCallback& callback);
		uint32_t registerScrollCallback(const ScrollCallback& callback);

		void unregisterInputCallback(uint32_t callbackId);
		void unregisterMouseButtonCallback(uint32_t callbackId);
		void unregisterMouseMoveCallback(uint32_t callbackId);
		void unregisterScrollCallback(uint32_t callbackId);

		void handleInput(int key, int mods, int action);
		void handleMouseButton(int button, int mods, int action);
		void handleMouseMove(double xpos, double ypos);
		void handleScroll(double xoffset, double yoffset);

		void clearCallbacks();
	};
}