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

uint32_t GFXEngine::InputManager::registerMouseButtonCallback(const MouseButtonCallback& callback)
{
	uint32_t callbackId = generateCallbackId();
	m_mouseButtonCallbacks[callbackId] = callback;
	return callbackId;
}

uint32_t GFXEngine::InputManager::registerMouseMoveCallback(const MouseMoveCallback& callback)
{
	uint32_t callbackId = generateCallbackId();
	m_mouseMoveCallbacks[callbackId] = callback;
	return callbackId;
}

uint32_t GFXEngine::InputManager::registerScrollCallback(const ScrollCallback& callback)
{
	uint32_t callbackId = generateCallbackId();
	m_scrollCallbacks[callbackId] = callback;
	return callbackId;
}

void GFXEngine::InputManager::unregisterInputCallback(uint32_t callbackId)
{
	if (m_inputCallbacks.contains(callbackId)) {
		m_inputCallbacks.erase(callbackId);
	}
}

void GFXEngine::InputManager::unregisterMouseButtonCallback(uint32_t callbackId)
{
	if (m_mouseButtonCallbacks.contains(callbackId)) {
		m_mouseButtonCallbacks.erase(callbackId);
	}
}

void GFXEngine::InputManager::unregisterMouseMoveCallback(uint32_t callbackId)
{
	if (m_mouseMoveCallbacks.contains(callbackId)) {
		m_mouseMoveCallbacks.erase(callbackId);
	}
}

void GFXEngine::InputManager::unregisterScrollCallback(uint32_t callbackId)
{
	if (m_scrollCallbacks.contains(callbackId)) {
		m_scrollCallbacks.erase(callbackId);
	}
}

void GFXEngine::InputManager::handleInput(int key, int mods, int action)
{
	for (const auto& [callbackId, callback] : m_inputCallbacks) {
		callback(key, mods, action);
	}
}

void GFXEngine::InputManager::handleMouseButton(int button, int mods, int action)
{
	for (const auto& [callbackId, callback] : m_mouseButtonCallbacks) {
		callback(button, mods, action);
	}
}

void GFXEngine::InputManager::handleMouseMove(double xpos, double ypos)
{
	for (const auto& [callbackId, callback] : m_mouseMoveCallbacks) {
		callback(xpos, ypos);
	}
}

void GFXEngine::InputManager::handleScroll(double xoffset, double yoffset)
{
	for (const auto& [callbackId, callback] : m_scrollCallbacks) {
		callback(xoffset, yoffset);
	}
}

void GFXEngine::InputManager::clearCallbacks()
{
	m_inputCallbacks.clear();
	m_mouseButtonCallbacks.clear();
	m_mouseMoveCallbacks.clear();
	m_scrollCallbacks.clear();
}
