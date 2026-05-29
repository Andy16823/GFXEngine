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

bool GFXEngine::Physics::Raycast::rayIntersectsMesh(const Ray& ray, const Math::Transform& transform, const Graphics::Mesh& mesh, RaycastHit& hitInfo)
{
	glm::mat4 finalMatrix = transform.getModelMatrix(); // TODO: Add mesh matrix
	float closestT = std::numeric_limits<float>::max();
	hitInfo.hit = false;

	auto indices = mesh.getIndices();
	auto positionsView = mesh.getVertexComponent(GFXEngine::EngineTypes::VertexComponent::Position);
	if (positionsView.isEmpty()) {
		throw std::runtime_error("Mesh does not contain position vertex component");
	}
	auto positions = positionsView.as<glm::vec3>();

	for (size_t i = 0; i < indices.size(); i += 3) {
		auto v0 = glm::vec3(finalMatrix * glm::vec4(positions[indices[i]], 1.0f));
		auto v1 = glm::vec3(finalMatrix * glm::vec4(positions[indices[i + 1]], 1.0f));
		auto v2 = glm::vec3(finalMatrix * glm::vec4(positions[indices[i + 2]], 1.0f));

		float t;
		glm::vec3 normal;
		if (rayIntersectsTriangle(ray, v0, v1, v2, t, normal)) {
			if (t < closestT) {
				closestT = t;
				hitInfo.point = ray.origin + ray.direction * t;
				hitInfo.normal = normal;
				hitInfo.hit = true;
				hitInfo.distance = t;
			}
		}
	}
	return hitInfo.hit;
}

bool GFXEngine::Physics::Raycast::rayIntersectsTriangle(const Ray& ray, const glm::vec3& v0, const glm::vec3& v1, const glm::vec3& v2, float& t, glm::vec3& normal)
{
	t = 0;
	normal = glm::vec3(0.0f);

	const float EPSILON = 0.0000001f;
	glm::vec3 edge1 = v1 - v0;
	glm::vec3 edge2 = v2 - v0;
	glm::vec3 h = glm::cross(ray.direction, edge2);
	float a = glm::dot(edge1, h);

	if (a > -EPSILON && a < EPSILON) {
		return false;
	}

	float f = 1.0f / a;
	glm::vec3 s = ray.origin - v0;
	float u = f * glm::dot(s, h);

	if (u < 0.0f || u > 1.0f) {
		return false;
	}

	glm::vec3 q = glm::cross(s, edge1);
	float v = f * glm::dot(ray.direction, q);

	if (v < 0.0f || u + v > 1.0f) {
		return false;
	}

	t = f * glm::dot(edge2, q);
	if (t > EPSILON) {
		normal = glm::normalize(glm::cross(edge1, edge2));
		return true;
	}
	return false;
}
