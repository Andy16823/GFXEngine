#include "RenderTexture.h"
#include <iostream>
#include "Shapes.h"

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

	// Create color and depth attachments
	m_extent = extend;
	VkFormat format = renderer.getSwapchainInfo().surfaceFormat.format;
	m_colorAttachment = renderer.createImage(m_extent, format, VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT | VK_IMAGE_USAGE_SAMPLED_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);
	m_depthAttachment = renderer.createDepthBuffer(extend, renderer.getDepthFormat());

	// Create attachments array for framebuffer creation
	VkImageView attachments[] = {
		m_colorAttachment.imageView,
		m_depthAttachment.imageView
	};

	// Create framebuffer
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

	auto [vertices, indices] = Shapes::createFramebufferQuad();
	size_t vertexBufferSize = vertices.size() * sizeof(EngineTypes::Vertex3D);
	m_vertexBuffer = renderer.createBuffer(vertexBufferSize, VK_BUFFER_USAGE_VERTEX_BUFFER_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT);
	renderer.updateBuffer(m_vertexBuffer, vertices.data(), vertices.size());

	size_t indexBufferSize = indices.size() * sizeof(uint32_t);
	m_indexBuffer = renderer.createBuffer(indexBufferSize, VK_BUFFER_USAGE_INDEX_BUFFER_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT);
	renderer.updateBuffer(m_indexBuffer, indices.data(), indices.size());
}

void GFXEngine::Graphics::RenderTexture::destroy(Renderer& renderer)
{
	renderer.disposeTexture(m_colorAttachment);
	renderer.destroyDepthBuffer(m_depthAttachment);
	vkDestroyFramebuffer(renderer.getContext().getDevice(), m_framebuffer, nullptr);
}

void GFXEngine::Graphics::RenderTexture::createDescriptorSet(Renderer& renderer, uint32_t binding, VkDescriptorSetLayout layout)
{
	// Create descriptor set for the color attachment
	m_descriptorSet = renderer.allocateTextureDescriptorSet(m_colorAttachment, binding, layout);
}

void GFXEngine::Graphics::RenderTexture::draw(Renderer& renderer, VkPipelineLayout pipelineLayout, uint32_t imageIndex)
{
	// Bind the descriptor set for the color attachment
	renderer.bindDescriptorSet(m_descriptorSet, pipelineLayout, 0, imageIndex);
	// Draw a full-screen quad using the vertex and index buffers
	renderer.drawBuffers(m_vertexBuffer, m_indexBuffer, 6, imageIndex);
}
