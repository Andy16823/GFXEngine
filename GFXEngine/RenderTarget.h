#pragma once
#include <vulkan/vulkan.h>
#include <span>
#include "Renderer.h"
#include "RenderPass.h"
#include "RenderPipeline.h"

namespace GFXEngine {
	namespace Graphics {
		class RenderTarget
		{
		public:
			//************************************
			// Method:    ~RenderTarget
			// FullName:  GFXEngine::Graphics::RenderTarget::~RenderTarget
			// Access:    virtual public 
			// Returns:   
			// Qualifier:
			//************************************
			virtual ~RenderTarget() = default;

		public:
			//************************************
			// Method:    getFramebuffer
			// FullName:  GFXEngine::Graphics::RenderTarget::getFramebuffer
			// Access:    virtual public 
			// Returns:   VkFramebuffer
			// Qualifier: const
			//************************************
			virtual VkFramebuffer getFramebuffer() const = 0;
			
			//************************************
			// Method:    getExtent
			// FullName:  GFXEngine::Graphics::RenderTarget::getExtent
			// Access:    virtual public 
			// Returns:   VkExtent2D
			// Qualifier: const
			//************************************
			virtual VkExtent2D getExtent() const = 0;
			
			//************************************
			// Method:    getClearValues
			// FullName:  GFXEngine::Graphics::RenderTarget::getClearValues
			// Access:    virtual public 
			// Returns:   std::span<const VkClearValue>
			// Qualifier: const
			//************************************
			virtual std::span<const VkClearValue> getClearValues() const = 0;
			
		public:
			//************************************
			// Method:    create
			// FullName:  GFXEngine::Graphics::RenderTarget::create
			// Access:    virtual public 
			// Returns:   void
			// Qualifier:
			// Parameter: Renderer & renderer
			// Parameter: VkExtent2D extend
			// Parameter: const LibGFX::RenderPass & renderpass
			//************************************
			virtual void create(Renderer& renderer, VkExtent2D extend, const LibGFX::RenderPass& renderpass) = 0;
			
			//************************************
			// Method:    createDescriptorSet
			// FullName:  GFXEngine::Graphics::RenderTarget::createDescriptorSet
			// Access:    virtual public 
			// Returns:   void
			// Qualifier:
			// Parameter: Renderer & renderer
			// Parameter: uint32_t binding
			// Parameter: VkDescriptorSetLayout layout
			//************************************
			virtual void createDescriptorSet(Renderer& renderer, uint32_t binding, VkDescriptorSetLayout layout) = 0;
			
			//************************************
			// Method:    updateDescriptorSet
			// FullName:  GFXEngine::Graphics::RenderTarget::updateDescriptorSet
			// Access:    virtual public 
			// Returns:   void
			// Qualifier:
			// Parameter: Renderer & renderer
			// Parameter: uint32_t binding
			// Parameter: VkDescriptorSetLayout layout
			//************************************
			virtual void updateDescriptorSet(Renderer& renderer, uint32_t binding, VkDescriptorSetLayout layout) = 0;
			
			//************************************
			// Method:    draw
			// FullName:  GFXEngine::Graphics::RenderTarget::draw
			// Access:    virtual public 
			// Returns:   void
			// Qualifier:
			// Parameter: Renderer & renderer
			// Parameter: RenderPipeline & pipeline
			// Parameter: uint32_t imageIndex
			//************************************
			virtual void draw(Renderer& renderer, RenderPipeline& pipeline, uint32_t imageIndex) = 0;
			
			//************************************
			// Method:    resize
			// FullName:  GFXEngine::Graphics::RenderTarget::resize
			// Access:    virtual public 
			// Returns:   void
			// Qualifier:
			// Parameter: Renderer & renderer
			// Parameter: VkExtent2D newExtent
			// Parameter: const LibGFX::RenderPass & renderpass
			//************************************
			virtual void resize(Renderer& renderer, VkExtent2D newExtent, const LibGFX::RenderPass& renderpass) = 0;
			
			//************************************
			// Method:    destroy
			// FullName:  GFXEngine::Graphics::RenderTarget::destroy
			// Access:    virtual public 
			// Returns:   void
			// Qualifier:
			// Parameter: Renderer & renderer
			//************************************
			virtual void destroy(Renderer& renderer) = 0;
		};
	}
}
