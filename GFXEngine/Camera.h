#pragma once
#include "glm/glm.hpp"
#include "Renderer.h"
#include "glm/gtc/matrix_transform.hpp"

namespace GFXEngine {
	namespace Graphics {

		class Camera
		{
		public:
			//************************************
			// Method:    ~Camera
			// FullName:  GFXEngine::Graphics::Camera::~Camera
			// Access:    virtual public 
			// Returns:   
			// Qualifier:
			//************************************
			virtual ~Camera() = default;
			
			//************************************
			// Method:    getViewMatrix
			// FullName:  GFXEngine::Graphics::Camera::getViewMatrix
			// Access:    virtual public 
			// Returns:   glm::mat4
			// Qualifier: const
			//************************************
			virtual glm::mat4 getViewMatrix() const = 0;
			
			//************************************
			// Method:    getProjectionMatrix
			// FullName:  GFXEngine::Graphics::Camera::getProjectionMatrix
			// Access:    virtual public 
			// Returns:   glm::mat4
			// Qualifier: const
			//************************************
			virtual glm::mat4 getProjectionMatrix() const = 0;
			
			//************************************
			// Method:    getPosition
			// FullName:  GFXEngine::Graphics::Camera::getPosition
			// Access:    virtual public 
			// Returns:   glm::vec3
			// Qualifier: const
			//************************************
			virtual glm::vec3 getPosition() const = 0;

			//************************************
			// Method:    createDescriptorSets
			// FullName:  GFXEngine::Graphics::Camera::createDescriptorSets
			// Access:    virtual public 
			// Returns:   void
			// Qualifier:
			// Parameter: Renderer & renderer
			// Parameter: VkDescriptorSetLayout descriptorSetLayout
			//************************************
			virtual void createDescriptorSets(Renderer& renderer, VkDescriptorSetLayout descriptorSetLayout) = 0;
			
			//************************************
			// Method:    updateCameraBuffers
			// FullName:  GFXEngine::Graphics::Camera::updateCameraBuffers
			// Access:    virtual public 
			// Returns:   void
			// Qualifier:
			// Parameter: Renderer & renderer
			// Parameter: uint32_t imageIndex
			//************************************
			virtual void updateCameraBuffers(Renderer& renderer, uint32_t imageIndex) = 0;
			
			//************************************
			// Method:    destroyDescriptorSets
			// FullName:  GFXEngine::Graphics::Camera::destroyDescriptorSets
			// Access:    virtual public 
			// Returns:   void
			// Qualifier:
			// Parameter: Renderer & renderer
			//************************************
			virtual void destroyDescriptorSets(Renderer& renderer) = 0;
			
			//************************************
			// Method:    getDescriptorSet
			// FullName:  GFXEngine::Graphics::Camera::getDescriptorSet
			// Access:    virtual public 
			// Returns:   VkDescriptorSet
			// Qualifier: const
			// Parameter: uint32_t imageIndex
			//************************************
			virtual VkDescriptorSet getDescriptorSet(uint32_t imageIndex) const = 0;

			//************************************
			// Method:    unprojectPosition
			// FullName:  GFXEngine::Graphics::Camera::unprojectPosition
			// Access:    public 
			// Returns:   glm::vec3
			// Qualifier: const
			// Parameter: const glm::vec3 & screenPosition
			// Parameter: const glm::vec4 viewport
			//************************************
			glm::vec3 unprojectPosition(const glm::vec3& screenPosition, const glm::vec4 viewport) const {
				auto view = getViewMatrix();
				auto projection = getProjectionMatrix();
				return glm::unProject(screenPosition, view, projection, viewport);
			}

			//************************************
			// Method:    projectPosition
			// FullName:  GFXEngine::Graphics::Camera::projectPosition
			// Access:    public 
			// Returns:   glm::vec3
			// Qualifier: const
			// Parameter: const glm::vec3 & worldPosition
			// Parameter: const glm::vec4 & viewport
			//************************************
			glm::vec3 projectPosition(const glm::vec3& worldPosition, const glm::vec4& viewport) const {
				auto view = getViewMatrix();
				auto projection = getProjectionMatrix();
				return glm::project(worldPosition, view, projection, viewport);
			}
		};
	}
}