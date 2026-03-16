#pragma once
#include "glm/glm.hpp"
#include "Renderer.h"
#include "glm/gtc/matrix_transform.hpp"

namespace GFXEngine {
	namespace Graphics {

		/// <summary>
		/// Abstract base class for cameras in the engine. Defines the interface for getting view and projection matrices, as well as managing descriptor sets for camera data.
		/// </summary>
		class Camera
		{
		public:
			virtual ~Camera() = default;
			virtual glm::mat4 getViewMatrix() const = 0;
			virtual glm::mat4 getProjectionMatrix() const = 0;
			virtual glm::vec3 getPosition() const = 0;

			virtual void createDescriptorSets(Renderer& renderer, VkDescriptorSetLayout descriptorSetLayout) = 0;
			virtual void updateCameraBuffers(Renderer& renderer, uint32_t imageIndex) = 0;
			virtual void destroyDescriptorSets(Renderer& renderer) = 0;
			virtual VkDescriptorSet getDescriptorSet(uint32_t imageIndex) const = 0;

			glm::vec3 unprojectPosition(const glm::vec3& screenPosition, const glm::vec4 viewport) const {
				auto view = getViewMatrix();
				auto projection = getProjectionMatrix();
				return glm::unProject(screenPosition, view, projection, viewport);
			}

			glm::vec3 projectPosition(const glm::vec3& worldPosition, const glm::vec4& viewport) const {
				auto view = getViewMatrix();
				auto projection = getProjectionMatrix();
				return glm::project(worldPosition, view, projection, viewport);
			}
		};
	}
}