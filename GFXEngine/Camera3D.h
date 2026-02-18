#pragma once
#include "DataTypes.h"
#include "glm/glm.hpp"
#include "Transform.h"

namespace GFXEngine{
	namespace Graphics {

		class Camera3D
		{
		private:
			GFXEngine::Math::Transform m_transform;
			float m_fov;
			float m_aspectRatio;
			float m_nearPlane;
			float m_farPlane;
		public:
			Camera3D(glm::vec3 position, float aspect, float near, float far);
			~Camera3D() = default;
			GFXEngine::EngineTypes::CameraBufferObject getCameraBufferObject() const;
			glm::mat4 getViewMatrix() const;
			glm::mat4 getProjectionMatrix() const;
			glm::vec3 getPosition() const { return m_transform.position; }
		};
	}
}
