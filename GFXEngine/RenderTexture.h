#pragma once
#include "RenderTarget.h"
#include "Buffer.h"
#include "DepthBuffer.h"


namespace GFXEngine {
	namespace Graphics {
		class RenderTexture : public RenderTarget
		{
		private:
			LibGFX::Image m_colorAttachment;
			LibGFX::DepthBuffer m_depthAttachment;
			LibGFX::Buffer m_vertexBuffer;
			LibGFX::Buffer m_indexBuffer;
			VkFramebuffer m_framebuffer;
			VkExtent2D m_extent;

		public:
			RenderTexture() = default;
			virtual ~RenderTexture() = default;
			virtual VkFramebuffer getFramebuffer() const override;
			virtual VkExtent2D getExtent() const override;
			virtual std::span<const VkClearValue> getClearValues() const override;
			virtual void create(Renderer& renderer, VkExtent2D extend, const LibGFX::RenderPass& renderpass) override;
			virtual void useAsColorAttachment(Renderer& renderer, uint32_t imageIndex, uint32_t attachmentIndex) const override;
			virtual void useAsDepthAttachment(Renderer& renderer, uint32_t imageIndex) const override;
			virtual void destroy(Renderer& renderer) override;
		};
	}
}
