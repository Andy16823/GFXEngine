#include "InputManager.h"

bool GFXEngine::InputManager::isKeyPressed(int key) const
{
	return glfwGetKey(m_window, key) == GLFW_PRESS;
}

bool GFXEngine::InputManager::isKeyReleased(int key) const
{
	return glfwGetKey(m_window, key) == GLFW_RELEASE;
}

bool GFXEngine::InputManager::isMouseButtonPressed(int button) const
{
	return glfwGetMouseButton(m_window, button) == GLFW_PRESS;
}

bool GFXEngine::InputManager::isMouseButtonReleased(int button) const
{
	return glfwGetMouseButton(m_window, button) == GLFW_RELEASE;	
}

glm::vec2 GFXEngine::InputManager::getCursorPosition() const
{
	double x, y;
	glfwGetCursorPos(m_window, &x, &y);
	return glm::vec2(static_cast<float>(x), static_cast<float>(y));
}

uint32_t GFXEngine::InputManager::registerInputCallback(const InputCallback& callback)
{
	uint32_t callbackId = generateCallbackId();
	m_inputCallbacks[callbackId] = callback;
	return callbackId;
}

void GFXEngine::InputManager::unregisterInputCallback(uint32_t callbackId)
{
	if (m_inputCallbacks.contains(callbackId)) {
		m_inputCallbacks.erase(callbackId);
	}
}

void GFXEngine::InputManager::handleInput(int key, int mods, int action)
{
	for (const auto& [callbackId, callback] : m_inputCallbacks) {
		callback(key, mods, action);
	}
}
