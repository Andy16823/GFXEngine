#pragma once
#include "Camera.h"
#include "AABB.h"
#include "Mesh3D.h"
#include "Transform.h"

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
			static Ray screenPointToRay(const glm::vec2& screenPos, const Graphics::Camera& camera, const glm::vec4& viewport);
			static void raycast(const glm::vec2& screenPos, const Graphics::Camera& camera, const glm::vec4& viewport, float groundHeight, RaycastHit& hitInfo);
			static bool rayIntersectsAABB(const Ray& ray, const Math::AABB& aabb, float& tMin, float& tMax);
			static bool rayIntersectsMesh(const Ray& ray, const Math::Transform& transform, const Graphics::Mesh3D& mesh, RaycastHit& hitInfo);
			static bool rayIntersectsTriangle(const Ray& ray, const glm::vec3& v0, const glm::vec3& v1, const glm::vec3& v2, float& t, glm::vec3& normal);
		};
	}
}
