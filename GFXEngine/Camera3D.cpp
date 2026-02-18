#include "Camera3D.h"
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>

GFXEngine::Graphics::Camera3D::Camera3D(glm::vec3 position, float aspect, float near, float far)
{
	m_transform.position = position;
	m_transform.setRotationFromEuler(glm::vec3(0.0f, 0.0f, 0.0f));
	m_fov = glm::radians(45.0f);
	m_aspectRatio = aspect;
	m_nearPlane = near;
	m_farPlane = far;
}

GFXEngine::EngineTypes::CameraBufferObject GFXEngine::Graphics::Camera3D::getCameraBufferObject() const
{
	EngineTypes::CameraBufferObject bufferObject;
	bufferObject.view = getViewMatrix();
	bufferObject.proj = getProjectionMatrix();
	bufferObject.cameraPos = glm::vec4(m_transform.position, 1.0f);
	return bufferObject;
}

glm::mat4 GFXEngine::Graphics::Camera3D::getViewMatrix() const
{
	auto target = m_transform.position + m_transform.getForward();
	auto up = glm::vec3(0.0f, 1.0f, 0.0f);
	return glm::lookAt(m_transform.position, target, up);
}

glm::mat4 GFXEngine::Graphics::Camera3D::getProjectionMatrix() const
{
	glm::mat4 proj = glm::perspective(m_fov, m_aspectRatio, m_nearPlane, m_farPlane);
	proj[1][1] *= -1; // Invert Y for Vulkan
	return proj;
}
