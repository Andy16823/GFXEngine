#include "Renderer.h"
#include <stdexcept>
#include "RenderShader.h"
#include "DefaultPipeline.h"
#include "DescriptorPoolBuilder.h"
#include "DescriptorSetWriter.h"


using namespace std;
using namespace GFXEngine::Graphics;

void Renderer::init(GLFWwindow* window)
{
	// Create Vulkan context
	m_context = LibGFX::GFX::createContext(window);
	m_context->initialize(LibGFX::VkContext::defaultAppInfo());

	// Create swapchain and depth buffer
	m_swapchainInfo = m_context->createSwapChain(VK_PRESENT_MODE_MAILBOX_KHR);
	m_depthFormat = m_context->findSuitableDepthFormat();
	m_depthBuffer = m_context->createDepthBuffer(m_swapchainInfo.extent, m_depthFormat);

	// Create screespace render pass
	m_renderPass = std::make_unique<LibGFX::Presets::DefaultRenderPass>();
	if (!m_renderPass->create(*m_context, m_swapchainInfo.surfaceFormat.format, m_depthBuffer.format)) {
		throw std::runtime_error("Failed to create render pass");
	}

	// Offscreen render pass
	m_offscreenRenderPass = std::make_unique<OffscreenRenderPass>();
	if (!m_offscreenRenderPass->create(*m_context, m_swapchainInfo.surfaceFormat.format, m_depthBuffer.format)) {
		throw std::runtime_error("Failed to create offscreen render pass");
	}

	// Viewport & Scissor
	m_viewport = m_context->createViewport(0.0f, 0.0f, m_swapchainInfo.extent);
	m_scissor = m_context->createScissorRect(0, 0, m_swapchainInfo.extent);

	// Create framebuffers for each swapchain image
	m_framebuffers = m_context->createFramebuffers(*m_renderPass, m_swapchainInfo, m_depthBuffer);

	m_queueFamilyIndices = m_context->getQueueFamilyIndices(m_context->getPhysicalDevice());
	m_commandPool = m_context->createCommandPool(m_queueFamilyIndices.graphicsFamily, VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT);
	m_commandBuffers = m_context->allocateCommandBuffers(m_commandPool, static_cast<uint32_t>(m_framebuffers.size()));

	// Texture sampler
	m_textureSampler = m_context->createTextureSampler();
	LibGFX::DescriptorPoolBuilder descriptorPoolBuilder;

	// Create descriptor pool for texture samplers
	descriptorPoolBuilder.addPoolSize(VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, TEXTURE_SAMPLER_DESCRIPTOR_COUNT);
	descriptorPoolBuilder.setMaxSets(TEXTURE_SAMPLER_MAX_SETS);
	m_textureDescriptorPool = descriptorPoolBuilder.build(*m_context);
	descriptorPoolBuilder.clear();

	// Create descriptor pool for uniform buffers
	descriptorPoolBuilder.addPoolSize(VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, UNIFORM_BUFFER_DESCRIPTOR_COUNT);
	descriptorPoolBuilder.setMaxSets(UNIFORM_BUFFER_MAX_SETS);
	m_uniformBufferDescriptorPool = descriptorPoolBuilder.build(*m_context);
	descriptorPoolBuilder.clear();
}

void Renderer::drawFrame()
{

}

void Renderer::dispose()
{
	// Wait for idle
	m_context->waitIdle();

	m_context->destroySemaphores(m_imageAvailableSemaphores);
	m_context->destroySemaphores(m_renderFinishedSemaphores);
	m_context->destroyFences(m_inFlightFences);
	m_context->destroySampler(m_textureSampler);
	m_context->destroyDescriptorSetPool(m_textureDescriptorPool);
	m_context->destroyDescriptorSetPool(m_uniformBufferDescriptorPool);
	m_context->destroyCommandPool(m_commandPool);

	// Clean up resources
	for (auto framebuffer : m_framebuffers) {
		vkDestroyFramebuffer(m_context->getDevice(), framebuffer, nullptr);
	}
	m_renderPass->destroy(*m_context);
	m_offscreenRenderPass->destroy(*m_context);
	m_context->destroyDepthBuffer(m_depthBuffer);
	m_context->destroySwapChain(m_swapchainInfo);
	m_context->dispose();
}

void Renderer::createSyncObjects()
{
	m_maxFramesInFlight = static_cast<int>(m_framebuffers.size());
	m_imagesInFlight = std::vector<VkFence>(m_maxFramesInFlight, VK_NULL_HANDLE);
	m_inFlightFences = m_context->createFences(m_maxFramesInFlight, VK_FENCE_CREATE_SIGNALED_BIT);
	m_imageAvailableSemaphores = m_context->createSemaphores(m_maxFramesInFlight);
	m_renderFinishedSemaphores = m_context->createSemaphores(m_maxFramesInFlight);
}

uint32_t Renderer::nextImage()
{
	// Wait for the previous frame to finish
	m_context->waitForFence(m_inFlightFences[m_currentImage]);

	uint32_t imageIndex;
	m_context->acquireNextImage(m_swapchainInfo, m_imageAvailableSemaphores[m_currentImage], VK_NULL_HANDLE, imageIndex);

	if(m_imagesInFlight[imageIndex] != VK_NULL_HANDLE) {
		m_context->waitForFence(m_imagesInFlight[imageIndex]);
	} 
	m_imagesInFlight[imageIndex] = m_inFlightFences[m_currentImage];
	m_context->resetFence(m_inFlightFences[m_currentImage]);

	return imageIndex;
}

void Renderer::beginFrame(uint32_t imageIndex)
{
	m_context->beginCommandBuffer(m_commandBuffers[imageIndex]);
	m_context->beginRenderPass(m_commandBuffers[imageIndex], *m_renderPass.get(), m_framebuffers[imageIndex], m_swapchainInfo.extent);
}

void Renderer::endFrame(uint32_t imageIndex)
{
	m_context->endRenderPass(m_commandBuffers[imageIndex]);
	m_context->endCommandBuffer(m_commandBuffers[imageIndex]);
}

void Renderer::submitFrame(uint32_t imageIndex)
{
	VkPipelineStageFlags waitStages[] = { VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT };

	VkSubmitInfo submitInfo = {
		.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO,
		.waitSemaphoreCount = 1,
		.pWaitSemaphores = &m_imageAvailableSemaphores[m_currentImage],
		.pWaitDstStageMask = waitStages,
		.commandBufferCount = 1,
		.pCommandBuffers = &m_commandBuffers[imageIndex],
		.signalSemaphoreCount = 1,
		.pSignalSemaphores = &m_renderFinishedSemaphores[m_currentImage]
	};
	m_context->submitCommandBuffer(submitInfo, m_inFlightFences[m_currentImage]);
}

void Renderer::presentFrame(uint32_t imageIndex)
{
	VkPresentInfoKHR presentInfo = {
		.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR,
		.waitSemaphoreCount = 1,
		.pWaitSemaphores = &m_renderFinishedSemaphores[m_currentImage],
		.swapchainCount = 1,
		.pSwapchains = &m_swapchainInfo.swapchain,
		.pImageIndices = &imageIndex
	};
	m_context->queuePresent(presentInfo);
}

void Renderer::advanceFrame()
{
	m_currentImage = (m_currentImage + 1) % m_maxFramesInFlight;
}

LibGFX::Image Renderer::loadTexture(const LibGFX::ImageData& imageData)
{
	LibGFX::Image textureImage = m_context->createImage(imageData, m_commandPool);
	return textureImage;
}

void Renderer::disposeTexture(LibGFX::Image& image)
{
	m_context->destroyImage(image);
}

VkDescriptorSet Renderer::allocateTextureDescriptorSet(const LibGFX::Image& image, uint32_t binding, VkDescriptorSetLayout layout)
{
	VkDescriptorSet descriptorSet = m_context->allocateDescriptorSet(m_textureDescriptorPool, layout);
	LibGFX::DescriptorSetWriter writer;
	writer.addImageInfo(image.imageView, m_textureSampler, VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL)
		.write(*m_context, descriptorSet, binding, 0, VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER)
		.clear();

	return descriptorSet;
}

void Renderer::freeTextureDescriptorSet(VkDescriptorSet descriptorSet)
{
	m_context->freeDescriptorSet(m_textureDescriptorPool, descriptorSet);
}

void Renderer::createPipeline(LibGFX::Pipeline& pipeline)
{
	pipeline.create(*m_context);
}

void Renderer::destroyPipeline(LibGFX::Pipeline& pipeline)
{
	pipeline.destroy(*m_context);
}

void Renderer::usePipeline(const LibGFX::Pipeline& pipeline, uint32_t imageIndex)
{
	m_context->bindPipeline(m_commandBuffers[imageIndex], VK_PIPELINE_BIND_POINT_GRAPHICS, pipeline);
}

//LibGFX::Buffer Renderer::createVertexBuffer(const std::vector<EngineTypes::Vertex3D>& vertices)
//{
//	VkDeviceSize bufferSize = sizeof(vertices[0]) * vertices.size();
//	LibGFX::Buffer buffer = m_context->createBuffer(bufferSize, VK_BUFFER_USAGE_VERTEX_BUFFER_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT);
//	m_context->updateBuffer(buffer, vertices.data(), bufferSize);
//	return buffer;
//}
//
//LibGFX::Buffer Renderer::createIndexBuffer(const std::vector<uint32_t>& indices)
//{
//	VkDeviceSize bufferSize = sizeof(indices[0]) * indices.size();
//	LibGFX::Buffer buffer = m_context->createBuffer(bufferSize, VK_BUFFER_USAGE_INDEX_BUFFER_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT);
//	m_context->updateBuffer(buffer, indices.data(), bufferSize);
//	return buffer;
//}

LibGFX::Buffer Renderer::createBuffer(VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties)
{
	return m_context->createBuffer(size, usage, properties);
}

VkDescriptorSet Renderer::allocateUniformBufferDescriptorSet(const LibGFX::Buffer& buffer, uint32_t binding, VkDescriptorSetLayout layout)
{
	VkDescriptorSet descriptorSet = m_context->allocateDescriptorSet(m_uniformBufferDescriptorPool, layout);
	LibGFX::DescriptorSetWriter writer;
	writer.addBufferInfo(buffer.buffer, 0, buffer.size)
		.write(*m_context, descriptorSet, binding, 0, VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER)
		.clear();
	return descriptorSet;
}

void Renderer::freeUniformBufferDescriptorSet(VkDescriptorSet descriptorSet)
{
	m_context->freeDescriptorSet(m_uniformBufferDescriptorPool, descriptorSet);
}

void Renderer::destroyBuffer(LibGFX::Buffer& buffer)
{
	m_context->destroyBuffer(buffer);
}

void Renderer::bindDescriptorSets(const std::vector<VkDescriptorSet>& descriptorSets, VkPipelineLayout pipelineLayout, uint32_t imageIndex)
{
	VkCommandBuffer commandBuffer = this->getCommandBuffer(imageIndex);
	vkCmdBindDescriptorSets(
		commandBuffer,
		VK_PIPELINE_BIND_POINT_GRAPHICS,
		pipelineLayout,
		0,
		static_cast<uint32_t>(descriptorSets.size()),
		descriptorSets.data(),
		0,
		nullptr
	);
}

void Renderer::drawBuffers(const LibGFX::Buffer& vertexBuffer, const LibGFX::Buffer& indexBuffer, uint32_t indexCount, uint32_t imageIndex, uint32_t instanceCount /*= 1*/)
{
	VkCommandBuffer commandBuffer = this->getCommandBuffer(imageIndex);
	VkBuffer vertexBuffers[] = { vertexBuffer.buffer };
	VkDeviceSize offsets[] = { 0 };
	vkCmdBindVertexBuffers(commandBuffer, 0, 1, vertexBuffers, offsets);

	VkBuffer indexBuffers[] = { indexBuffer.buffer };
	vkCmdBindIndexBuffer(commandBuffer, indexBuffers[0], 0, VK_INDEX_TYPE_UINT32);
	vkCmdDrawIndexed(commandBuffer, indexCount, instanceCount, 0, 0, 0);
}

void Renderer::bindPushConstants(const void* data, size_t size, VkPipelineLayout pipelineLayout, uint32_t imageIndex)
{
	VkCommandBuffer commandBuffer = this->getCommandBuffer(imageIndex);
	vkCmdPushConstants(commandBuffer, pipelineLayout, VK_SHADER_STAGE_VERTEX_BIT | VK_SHADER_STAGE_FRAGMENT_BIT, 0, static_cast<uint32_t>(size), data);
}

void Renderer::bindDescriptorSet(const VkDescriptorSet& descriptorSet, VkPipelineLayout pipelineLayout, uint32_t firstSet, uint32_t imageIndex)
{
	VkCommandBuffer commandBuffer = this->getCommandBuffer(imageIndex);
	vkCmdBindDescriptorSets(
		commandBuffer,
		VK_PIPELINE_BIND_POINT_GRAPHICS,
		pipelineLayout,
		firstSet,
		1,
		&descriptorSet,
		0,
		nullptr
	);
}

LibGFX::Image Renderer::createImage(VkExtent2D extent, VkFormat format, VkImageUsageFlags usage, VkMemoryPropertyFlags properties)
{
	VkDeviceMemory imageMemory;

	VkImage image = m_context->createVkImage(
		m_context->getPhysicalDevice(),
		m_context->getDevice(),
		extent.width,
		extent.height,
		format,
		VK_IMAGE_TILING_OPTIMAL,
		usage,
		properties,
		&imageMemory);

	VkImageView imageView = m_context->createImageView(
		m_context->getDevice(), 
		image, 
		format, 
		VK_IMAGE_ASPECT_COLOR_BIT);

	LibGFX::Image result = {};
	result.image = image;
	result.imageView = imageView;
	result.memory = imageMemory;
	result.format = format;
	result.width = extent.width;
	result.height = extent.height;

	return result;
}

LibGFX::DepthBuffer Renderer::createDepthBuffer(VkExtent2D extent, VkFormat format)
{
	return m_context->createDepthBuffer(extent, format);
}

void Renderer::destroyDepthBuffer(LibGFX::DepthBuffer& depthBuffer)
{
	m_context->destroyDepthBuffer(depthBuffer);
}
