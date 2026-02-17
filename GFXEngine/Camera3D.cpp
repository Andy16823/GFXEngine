#include "Camera3D.h"
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>

GFXEngine::Graphics::Camera3D::Camera3D(glm::vec3 position, float aspect, float near, float far)
{
	m_position = position;
	m_target = glm::vec3(0.0f, 0.0f, 0.0f);
	m_up = glm::vec3(0.0f, 1.0f, 0.0f);
	m_fov = glm::radians(45.0f);
	m_aspectRatio = aspect;
	m_nearPlane = near;
	m_farPlane = far;
}

GFXEngine::EngineTypes::CameraBufferObject GFXEngine::Graphics::Camera3D::getCameraBufferObject() const
{
	EngineTypes::CameraBufferObject bufferObject;
	bufferObject.view = glm::lookAt(m_position, m_target, m_up);
	bufferObject.proj = glm::perspective(m_fov, m_aspectRatio, m_nearPlane, m_farPlane);
	bufferObject.cameraPos = m_position;
	return bufferObject;
}
