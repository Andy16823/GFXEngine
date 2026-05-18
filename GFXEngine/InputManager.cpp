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
