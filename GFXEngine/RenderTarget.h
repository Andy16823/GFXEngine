#pragma once
#include <vulkan/vulkan.h>
#include <span>
#include "Renderer.h"
#include "RenderPass.h"

namespace GFXEngine {
	namespace Graphics {
		class RenderTarget
		{
		public:
			virtual ~RenderTarget() = default;
			virtual VkFramebuffer getFramebuffer() const = 0;
			virtual VkExtent2D getExtent() const = 0;
			virtual std::span<const VkClearValue> getClearValues() const = 0;
			virtual void create(Renderer& renderer, VkExtent2D extend, const LibGFX::RenderPass& renderpass) = 0;
			virtual void createDescriptorSet(Renderer& renderer, uint32_t binding, VkDescriptorSetLayout layout) = 0;
			virtual void draw(Renderer& renderer, VkPipelineLayout pipelineLayout, uint32_t imageIndex) = 0;
			virtual void destroy(Renderer& renderer) = 0;
			virtual LibGFX::Buffer& getVertexBuffer() = 0;
			virtual LibGFX::Buffer& getIndexBuffer() = 0;
		};
	}
}
