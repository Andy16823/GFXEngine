#pragma once
#include "glm/glm.hpp"
#include "Renderer.h"
#include <memory>

namespace GFXEngine {
	namespace Graphics {

		/// <summary>
		/// Abstract base class for cameras in the engine. Defines the interface for getting view and projection matrices, as well as managing descriptor sets for camera data.
		/// </summary>
		class Camera : public std::enable_shared_from_this<Camera>
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

			static void setActiveCamera(std::shared_ptr<Camera> camera) {
				s_activeCamera = camera;
			}

			static std::shared_ptr<Camera> getActiveCamera() {
				return s_activeCamera.lock();
			}

			void makeActive() {
				setActiveCamera(shared_from_this());
			}

		private:
			static std::weak_ptr<Camera> s_activeCamera; // Weak pointer to the currently active camera
		};
	}
}