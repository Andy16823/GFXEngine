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

			//************************************
			// Method:    Camera3D
			// FullName:  GFXEngine::Graphics::Camera3D::Camera3D
			// Access:    public 
			// Returns:   
			// Qualifier:
			// Parameter: glm::vec3 position
			// Parameter: float aspect
			// Parameter: float near
			// Parameter: float far
			//************************************
			Camera3D(glm::vec3 position, float aspect, float near, float far);
			
			//************************************
			// Method:    ~Camera3D
			// FullName:  GFXEngine::Graphics::Camera3D::~Camera3D
			// Access:    public 
			// Returns:   
			// Qualifier:
			//************************************
			~Camera3D() = default;
			
			//************************************
			// Method:    getViewMatrix
			// FullName:  GFXEngine::Graphics::Camera3D::getViewMatrix
			// Access:    public 
			// Returns:   glm::mat4
			// Qualifier: const 
			//************************************
			glm::mat4 getViewMatrix() const override;
			
			//************************************
			// Method:    getProjectionMatrix
			// FullName:  GFXEngine::Graphics::Camera3D::getProjectionMatrix
			// Access:    public 
			// Returns:   glm::mat4
			// Qualifier: const 
			//************************************
			glm::mat4 getProjectionMatrix() const override;
			
			//************************************
			// Method:    getPosition
			// FullName:  GFXEngine::Graphics::Camera3D::getPosition
			// Access:    public 
			// Returns:   glm::vec3
			// Qualifier: const 
			//************************************
			glm::vec3 getPosition() const override { return m_transform.position; }
			
			//************************************
			// Method:    getTransform
			// FullName:  GFXEngine::Graphics::Camera3D::getTransform
			// Access:    public 
			// Returns:   GFXEngine::Math::Transform&
			// Qualifier:
			//************************************
			GFXEngine::Math::Transform& getTransform() { return m_transform; }
			
			//************************************
			// Method:    getCameraBufferObject
			// FullName:  GFXEngine::Graphics::Camera3D::getCameraBufferObject
			// Access:    public 
			// Returns:   GFXEngine::EngineTypes::CameraBufferObject
			// Qualifier: const
			//************************************
			GFXEngine::EngineTypes::CameraBufferObject getCameraBufferObject() const;

			//************************************
			// Method:    createDescriptorSets
			// FullName:  GFXEngine::Graphics::Camera3D::createDescriptorSets
			// Access:    public 
			// Returns:   void
			// Qualifier:
			// Parameter: Renderer & renderer
			// Parameter: VkDescriptorSetLayout descriptorSetLayout
			//************************************
			void createDescriptorSets(Renderer& renderer, VkDescriptorSetLayout descriptorSetLayout) override;
			
			//************************************
			// Method:    updateCameraBuffers
			// FullName:  GFXEngine::Graphics::Camera3D::updateCameraBuffers
			// Access:    public 
			// Returns:   void
			// Qualifier:
			// Parameter: Renderer & renderer
			// Parameter: uint32_t imageIndex
			//************************************
			void updateCameraBuffers(Renderer& renderer, uint32_t imageIndex) override;
			
			//************************************
			// Method:    destroyDescriptorSets
			// FullName:  GFXEngine::Graphics::Camera3D::destroyDescriptorSets
			// Access:    public 
			// Returns:   void
			// Qualifier:
			// Parameter: Renderer & renderer
			//************************************
			void destroyDescriptorSets(Renderer& renderer) override;
			
			//************************************
			// Method:    setAspectRatio
			// FullName:  GFXEngine::Graphics::Camera3D::setAspectRatio
			// Access:    public 
			// Returns:   void
			// Qualifier:
			// Parameter: float aspect
			//************************************
			void setAspectRatio(float aspect) { m_aspectRatio = aspect; }
			
			//************************************
			// Method:    getDescriptorSet
			// FullName:  GFXEngine::Graphics::Camera3D::getDescriptorSet
			// Access:    public 
			// Returns:   VkDescriptorSet
			// Qualifier: const 
			// Parameter: uint32_t imageIndex
			//************************************
			VkDescriptorSet getDescriptorSet(uint32_t imageIndex) const override { return m_descriptorSets[imageIndex]; }
		};
	}
}
