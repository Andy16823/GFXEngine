#include "Raycast.h"

GFXEngine::Physics::Ray GFXEngine::Physics::Raycast::screenPointToRay(const glm::vec2& screenPos, const Graphics::Camera& camera, const glm::vec4& viewport)
{
	glm::vec3 nearPoint = camera.unprojectPosition(glm::vec3(screenPos, 0.0f), viewport);
	glm::vec3 farPoint = camera.unprojectPosition(glm::vec3(screenPos, 1.0f), viewport);
	glm::vec3 rayDirection = glm::normalize(farPoint - nearPoint);
	return Ray{ nearPoint, rayDirection };
}

void GFXEngine::Physics::Raycast::raycast(const glm::vec2& screenPos, const Graphics::Camera& camera, const glm::vec4& viewport, float groundHeight, RaycastHit& hitInfo)
{
	Ray ray = screenPointToRay(screenPos, camera, viewport);
	glm::vec3 nearPoint = ray.origin;
	glm::vec3 rayDirection = ray.direction;

	// Check if the ray is parallel to the ground plane
	if (std::abs(rayDirection.y) < 0.0001f) { 
		hitInfo.hit = false;
		return; 
	}

	// Calculate the distance along the ray to the intersection with the ground plane
	float t = (groundHeight - nearPoint.y) / rayDirection.y;

	// If t is positive, the intersection point is in front of the ray origin
	if (t > 0.0f) {
		hitInfo.hit = true;
		hitInfo.point = nearPoint + rayDirection * t;
		hitInfo.normal = glm::vec3(0.0f, 1.0f, 0.0f);
		hitInfo.distance = t;
		return;
	}

	hitInfo.hit = false; 
}

bool GFXEngine::Physics::Raycast::rayIntersectsAABB(const Ray& ray, const Math::AABB& aabb, float& tMin, float& tMax)
{
	tMin = 0.0f;
	tMax = std::numeric_limits<float>::max();

	for (int i = 0; i < 3; i++) {
		float invD = 1.0f / ray.direction[i];
		float t0 = (aabb.min[i] - ray.origin[i]) * invD;
		float t1 = (aabb.max[i] - ray.origin[i]) * invD;

		if (invD < 0.0f) {
			std::swap(t0, t1);
		}

		tMin = std::max(tMin, t0);
		tMax = std::min(tMax, t1);

		if (tMax <= tMin) {
			return false;
		}
	}
	return true;
}
