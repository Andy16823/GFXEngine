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

	private:
		GLFWwindow* m_window;
		std::unordered_map<uint32_t, InputCallback> m_inputCallbacks;
		uint32_t m_nextCallbackId = 0;

		uint32_t generateCallbackId() {
			return m_nextCallbackId++;
		}
	public:
		InputManager(GLFWwindow* window) : m_window(window) {}
		~InputManager() = default;

		bool isKeyPressed(int key) const;
		bool isKeyReleased(int key) const;
		bool isMouseButtonPressed(int button) const;
		bool isMouseButtonReleased(int button) const;
		glm::vec2 getCursorPosition() const;

		uint32_t registerInputCallback(const InputCallback& callback);
		void unregisterInputCallback(uint32_t callbackId);
		void handleInput(int key, int mods, int action);
	};
}