#pragma once
#include "Camera.h"

namespace GFXEngine {
	namespace Physics {

		struct Ray {
			glm::vec3 origin;
			glm::vec3 direction;
		};

		struct RaycastHit {
			bool hit;
			glm::vec3 point;
			glm::vec3 normal;
			float distance;
		};

		class Raycast {

		public:
			static void raycast(const glm::vec2& screenPos, const Graphics::Camera& camera, const glm::vec4& viewport, float groundHeight, RaycastHit& hitInfo);

		};
	}
}
