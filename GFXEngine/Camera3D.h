#pragma once
#include "DataTypes.h"
#include "glm/glm.hpp"

namespace GFXEngine{
	namespace Graphics {
		class Camera3D
		{
		private:
			glm::vec3 m_position;
			glm::vec3 m_target;
			glm::vec3 m_up;
			float m_fov;
			float m_aspectRatio;
			float m_nearPlane;
			float m_farPlane;
		public:
			Camera3D(glm::vec3 position, float aspect, float near, float far);
			~Camera3D() = default;
			GFXEngine::EngineTypes::CameraBufferObject getCameraBufferObject() const;
		};
	}
}
