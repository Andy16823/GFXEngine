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
	// TODO: Implement this later when model view projection matrices are properly set up in the shader. For now, just return an empty buffer object.
	glm::mat4 proj = glm::perspective(m_fov, m_aspectRatio, m_nearPlane, m_farPlane);
	proj[1][1] *= -1; // Invert Y coordinate for Vulkan
	EngineTypes::CameraBufferObject bufferObject;
	bufferObject.view = glm::lookAt(m_position, m_target, m_up);
	bufferObject.proj = proj;
	bufferObject.cameraPos = m_position;
	return bufferObject;

	//EngineTypes::CameraBufferObject bufferObject{};
	//bufferObject.view = glm::mat4(1.0f);
	//bufferObject.proj = glm::mat4(1.0f);
	//bufferObject.cameraPos = m_position;
	//return bufferObject;
}
