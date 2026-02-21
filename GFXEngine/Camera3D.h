#pragma once
#include "Camera.h"
#include "DataTypes.h"
#include "glm/glm.hpp"
#include "Transform.h"
#include <vector>
#include "LibGFX.h"
#include "Buffer.h"
#include "Renderer.h"

namespace GFXEngine{
	namespace Graphics {

		/// <summary>
		/// Camera3D is a concrete implementation of the Camera interface for a standard 3D perspective camera. 
		/// It manages its own transform, projection parameters, and Vulkan descriptor sets for passing camera data to shaders.
		/// </summary>
		class Camera3D : public Camera
		{
		private:
			GFXEngine::Math::Transform m_transform;
			float m_fov;
			float m_aspectRatio;
			float m_nearPlane;
			float m_farPlane;
			std::vector<LibGFX::Buffer> m_cameraBuffers;
			std::vector<VkDescriptorSet> m_descriptorSets;
		public:
			Camera3D(glm::vec3 position, float aspect, float near, float far);
			~Camera3D() = default;
			glm::mat4 getViewMatrix() const override;
			glm::mat4 getProjectionMatrix() const override;
			glm::vec3 getPosition() const override { return m_transform.position; }
			GFXEngine::Math::Transform& getTransform() { return m_transform; }
			GFXEngine::EngineTypes::CameraBufferObject getCameraBufferObject() const;

			void createDescriptorSets(Renderer& renderer, VkDescriptorSetLayout descriptorSetLayout) override;
			void updateCameraBuffers(Renderer& renderer, uint32_t imageIndex) override;
			void destroyDescriptorSets(Renderer& renderer) override;
			VkDescriptorSet getDescriptorSet(uint32_t imageIndex) const override { return m_descriptorSets[imageIndex]; }
		};
	}
}
