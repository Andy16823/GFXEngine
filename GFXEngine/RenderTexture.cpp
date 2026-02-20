#include "RenderTexture.h"
#include <iostream>

VkFramebuffer GFXEngine::Graphics::RenderTexture::getFramebuffer() const
{
	return m_framebuffer;
}

VkExtent2D GFXEngine::Graphics::RenderTexture::getExtent() const
{
	return m_extent;
}

std::span<const VkClearValue> GFXEngine::Graphics::RenderTexture::getClearValues() const
{
	return {};
}

void GFXEngine::Graphics::RenderTexture::create(Renderer& renderer, VkExtent2D extend, const LibGFX::RenderPass& renderpass)
{
	auto ctx = renderer.getContext();

	m_extent = extend;
	VkFormat format = renderer.getSwapchainInfo().surfaceFormat.format;
	m_colorAttachment = renderer.createImage(m_extent, format, VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT | VK_IMAGE_USAGE_SAMPLED_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);
	m_depthAttachment = renderer.createDepthBuffer(extend, renderer.getDepthFormat());

	VkImageView attachments[] = {
		m_colorAttachment.imageView,
		m_depthAttachment.imageView
	};

	VkFramebufferCreateInfo framebufferInfo = {};
	framebufferInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
	framebufferInfo.renderPass = renderpass.getRenderPass();
	framebufferInfo.attachmentCount = 2;
	framebufferInfo.pAttachments = attachments;
	framebufferInfo.width = m_extent.width;
	framebufferInfo.height = m_extent.height;
	framebufferInfo.layers = 1;

	if (vkCreateFramebuffer(ctx.getDevice(), &framebufferInfo, nullptr, &m_framebuffer) != VK_SUCCESS) {
		throw std::runtime_error("Failed to create framebuffer for render texture");
	}
	std::cout << "Created render texture with extent: " << m_extent.width << "x" << m_extent.height << std::endl;
}
