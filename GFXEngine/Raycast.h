#pragma once
#include "Camera.h"
#include "AABB.h"
#include "Mesh.h"
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
			//************************************
			// Method:    screenPointToRay
			// FullName:  GFXEngine::Physics::Raycast::screenPointToRay
			// Access:    public static 
			// Returns:   GFXEngine::Physics::Ray
			// Qualifier:
			// Parameter: const glm::vec2 & screenPos
			// Parameter: const Graphics::Camera & camera
			// Parameter: const glm::vec4 & viewport
			//************************************
			static Ray screenPointToRay(const glm::vec2& screenPos, const Graphics::Camera& camera, const glm::vec4& viewport);
			
			//************************************
			// Method:    raycast
			// FullName:  GFXEngine::Physics::Raycast::raycast
			// Access:    public static 
			// Returns:   void
			// Qualifier:
			// Parameter: const glm::vec2 & screenPos
			// Parameter: const Graphics::Camera & camera
			// Parameter: const glm::vec4 & viewport
			// Parameter: float groundHeight
			// Parameter: RaycastHit & hitInfo
			//************************************
			static void raycast(const glm::vec2& screenPos, const Graphics::Camera& camera, const glm::vec4& viewport, float groundHeight, RaycastHit& hitInfo);
			
			//************************************
			// Method:    rayIntersectsAABB
			// FullName:  GFXEngine::Physics::Raycast::rayIntersectsAABB
			// Access:    public static 
			// Returns:   bool
			// Qualifier:
			// Parameter: const Ray & ray
			// Parameter: const Math::AABB & aabb
			// Parameter: float & tMin
			// Parameter: float & tMax
			//************************************
			static bool rayIntersectsAABB(const Ray& ray, const Math::AABB& aabb, float& tMin, float& tMax);
			
			//************************************
			// Method:    rayIntersectsMesh
			// FullName:  GFXEngine::Physics::Raycast::rayIntersectsMesh
			// Access:    public static 
			// Returns:   bool
			// Qualifier:
			// Parameter: const Ray & ray
			// Parameter: const Math::Transform & transform
			// Parameter: const Graphics::Mesh & mesh
			// Parameter: RaycastHit & hitInfo
			//************************************
			static bool rayIntersectsMesh(const Ray& ray, const Math::Transform& transform, const Graphics::Mesh& mesh, RaycastHit& hitInfo);
			
			//************************************
			// Method:    rayIntersectsTriangle
			// FullName:  GFXEngine::Physics::Raycast::rayIntersectsTriangle
			// Access:    public static 
			// Returns:   bool
			// Qualifier:
			// Parameter: const Ray & ray
			// Parameter: const glm::vec3 & v0
			// Parameter: const glm::vec3 & v1
			// Parameter: const glm::vec3 & v2
			// Parameter: float & t
			// Parameter: glm::vec3 & normal
			//************************************
			static bool rayIntersectsTriangle(const Ray& ray, const glm::vec3& v0, const glm::vec3& v1, const glm::vec3& v2, float& t, glm::vec3& normal);
		};
	}
}
