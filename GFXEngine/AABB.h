#pragma once
#include "glm/glm.hpp"

namespace GFXEngine {
	namespace Math {
		struct AABB {
			glm::vec3 min;
			glm::vec3 max;

			//************************************
			// Method:    AABB
			// FullName:  GFXEngine::Math::AABB::AABB
			// Access:    public 
			// Returns:   
			// Qualifier: : min(glm::vec3(std::numeric_limits<float>::max())), max(std::numeric_limits<float>::lowest())
			//************************************
			AABB() : min(glm::vec3(std::numeric_limits<float>::max())), max(std::numeric_limits<float>::lowest()) {}
			
			//************************************
			// Method:    AABB
			// FullName:  GFXEngine::Math::AABB::AABB
			// Access:    public 
			// Returns:   
			// Qualifier: : min(min), max(max)
			// Parameter: const glm::vec3 & min
			// Parameter: const glm::vec3 & max
			//************************************
			AABB(const glm::vec3& min, const glm::vec3& max) : min(min), max(max) {}
			
			//************************************
			// Method:    ~AABB
			// FullName:  GFXEngine::Math::AABB::~AABB
			// Access:    public 
			// Returns:   
			// Qualifier:
			//************************************
			~AABB() = default;

			//************************************
			// Method:    intersects
			// FullName:  GFXEngine::Math::AABB::intersects
			// Access:    public 
			// Returns:   bool
			// Qualifier: const
			// Parameter: const AABB & other
			//************************************
			bool intersects(const AABB& other) const {
				return (min.x <= other.max.x && max.x >= other.min.x) &&
					   (min.y <= other.max.y && max.y >= other.min.y) &&
					   (min.z <= other.max.z && max.z >= other.min.z);
			}

			//************************************
			// Method:    contains
			// FullName:  GFXEngine::Math::AABB::contains
			// Access:    public 
			// Returns:   bool
			// Qualifier: const
			// Parameter: const glm::vec3 & point
			//************************************
			bool contains(const glm::vec3& point) const {
				return (point.x >= min.x && point.x <= max.x) &&
					   (point.y >= min.y && point.y <= max.y) &&
					   (point.z >= min.z && point.z <= max.z);
			}

			//************************************
			// Method:    unionWith
			// FullName:  GFXEngine::Math::AABB::unionWith
			// Access:    public 
			// Returns:   GFXEngine::Math::AABB
			// Qualifier: const
			// Parameter: const AABB & other
			//************************************
			AABB unionWith(const AABB& other) const {
				glm::vec3 newMin = glm::min(min, other.min);
				glm::vec3 newMax = glm::max(max, other.max);
				return AABB(newMin, newMax);
			}
			
			//************************************
			// Method:    applyTransform
			// FullName:  GFXEngine::Math::AABB::applyTransform
			// Access:    public 
			// Returns:   GFXEngine::Math::AABB
			// Qualifier: const
			// Parameter: const glm::mat4 & transform
			//************************************
			AABB applyTransform(const glm::mat4& transform) const {
				glm::vec3 corners[8] = {
					glm::vec3(min.x, min.y, min.z),
					glm::vec3(max.x, min.y, min.z),
					glm::vec3(min.x, max.y, min.z),
					glm::vec3(max.x, max.y, min.z),
					glm::vec3(min.x, min.y, max.z),
					glm::vec3(max.x, min.y, max.z),
					glm::vec3(min.x, max.y, max.z),
					glm::vec3(max.x, max.y, max.z)
				};
				AABB transformedAABB;
				for (const auto& corner : corners) {
					glm::vec4 transformedCorner = transform * glm::vec4(corner, 1.0f);
					transformedAABB = transformedAABB.unionWith(AABB(glm::vec3(transformedCorner), glm::vec3(transformedCorner)));
				}
				return transformedAABB;
			}
		};
	}
}