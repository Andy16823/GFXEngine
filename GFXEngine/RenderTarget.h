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
			virtual void useAsColorAttachment(Renderer& renderer, uint32_t imageIndex, uint32_t attachmentIndex) const = 0;
			virtual void useAsDepthAttachment(Renderer& renderer, uint32_t imageIndex) const = 0;
			virtual void destroy(Renderer& renderer) = 0;
		};
	}
}
