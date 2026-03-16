#include "Raycast.h"

void GFXEngine::Physics::Raycast::raycast(const glm::vec2& screenPos, const Graphics::Camera& camera, const glm::vec4& viewport, float groundHeight, RaycastHit& hitInfo)
{
	glm::vec3 nearPoint = camera.unprojectPosition(glm::vec3(screenPos, 0.0f), viewport);
	glm::vec3 farPoint = camera.unprojectPosition(glm::vec3(screenPos, 1.0f), viewport);
	glm::vec3 rayDirection = glm::normalize(farPoint - nearPoint);

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