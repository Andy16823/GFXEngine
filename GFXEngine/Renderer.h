#pragma once
#include "VkContext.h"
#include "DataTypes.h"
#include "LibGFX.h"
#include "Buffer.h"
#include "SwapchainInfo.h"
#include "DefaultRenderPass.h"
#include "OffscreenRenderPass.h"
#include "PipelineManager.h"
#include <GLFW/glfw3.h>
#include <memory>
#include "QueueFamilyIndices.h"
#include "Imaging.h"

const uint32_t TEXTURE_SAMPLER_DESCRIPTOR_COUNT = 16;
const uint32_t TEXTURE_SAMPLER_MAX_SETS = 512;
const uint32_t UNIFORM_BUFFER_DESCRIPTOR_COUNT = 16;
const uint32_t UNIFORM_BUFFER_MAX_SETS = 512;
const uint32_t STORAGE_BUFFER_DESCRIPTOR_COUNT = 16;
const uint32_t STORAGE_BUFFER_MAX_SETS = 512;

namespace GFXEngine {
	namespace Graphics {
		class Renderer
		{
		private:
			// BASIC RENDERING RESOURCES
			std::unique_ptr<LibGFX::VkContext> m_context;
			VkRect2D m_scissor;
			VkViewport m_viewport;

			// SYNC OBJECTS
			int m_currentImage = 0;
			int m_maxFramesInFlight = 2;
			std::vector<VkFence> m_imagesInFlight; // Track which fence is currently using each swapchain image
			std::vector<VkFence> m_inFlightFences;
			std::vector<VkSemaphore> m_imageAvailableSemaphores;
			std::vector<VkSemaphore> m_renderFinishedSemaphores;

			// SWAPCHAIN & RENDER PASS
			SwapchainInfo m_swapchainInfo;
			VkFormat m_depthFormat;
			LibGFX::DepthBuffer m_depthBuffer;
			std::unique_ptr<LibGFX::Presets::DefaultRenderPass> m_renderPass;
			std::unique_ptr<OffscreenRenderPass> m_offscreenRenderPass;

			// FRAMEBUFFERS & COMMAND BUFFERS
			std::vector<VkFramebuffer> m_framebuffers;
			LibGFX::QueueFamilyIndices m_queueFamilyIndices;
			std::vector<VkCommandBuffer> m_commandBuffers;

			// TEXTURE SAMPLERS
			VkDescriptorPool m_textureDescriptorPool;
			VkSampler m_textureSampler;

			// UNIFORM BUFFER DESCRIPTOR POOL
			VkDescriptorPool m_uniformBufferDescriptorPool;

			// STORAGE BUFFER DESCRIPTOR POOL
			VkDescriptorPool m_storageBufferDescriptorPool;

			// COMMAND POOL
			VkCommandPool m_commandPool;

		public:
			// CONSTRUCTORS & DESTRUCTORS
			Renderer() = default;
			~Renderer() = default;

			// MAIN LOOP FUNCTIONS
			void init(GLFWwindow* window);
			void createSyncObjects();
			uint32_t nextImage();
			void beginFrame(uint32_t imageIndex);
			void beginRenderPass(const LibGFX::RenderPass& renderpass, uint32_t imageIndex);
			void beginRenderPass(const LibGFX::RenderPass& renderpass, const VkFramebuffer& framebuffer, uint32_t imageIndex);
			void usePipeline(const LibGFX::Pipeline& pipeline, uint32_t imageIndex);
			void endRenderPass(uint32_t imageIndex);
			void endFrame(uint32_t imageIndex);
			void submitFrame(uint32_t imageIndex);
			void presentFrame(uint32_t imageIndex);
			void advanceFrame();
			void bindPushConstants(const void* data, size_t size, VkPipelineLayout pipelineLayout, uint32_t imageIndex);
			void bindDescriptorSet(const VkDescriptorSet& descriptorSet, VkPipelineLayout pipelineLayout, uint32_t firstSet, uint32_t imageIndex);
			void bindDescriptorSets(const std::vector<VkDescriptorSet>& descriptorSets, VkPipelineLayout pipelineLayout, uint32_t imageIndex);
			void drawBuffers(const LibGFX::Buffer& vertexBuffer, const LibGFX::Buffer& indexBuffer, uint32_t indexCount, uint32_t imageIndex, uint32_t instanceCount = 1);
			void drawFrame();
			void waitIdle() { m_context->waitIdle(); }
			void dispose();

			// DESCRIPTOR SET LAYOUTS
			VkDescriptorSetLayout createDescriptorSetLayout(uint32_t binding, VkDescriptorType type, VkShaderStageFlags stageFlags);

			// TEXTURES
			LibGFX::Image createImage(VkExtent2D extent, VkFormat format, VkImageUsageFlags usage, VkMemoryPropertyFlags properties);
			LibGFX::Image loadTexture(const LibGFX::ImageData& imageData);
			void disposeTexture(LibGFX::Image& image);
			VkDescriptorSet allocateTextureDescriptorSet(const LibGFX::Image& image, uint32_t binding, VkDescriptorSetLayout layout);
			void freeTextureDescriptorSet(VkDescriptorSet descriptorSet);

			// UNIFORM BUFFERS
			VkDescriptorSet allocateUniformBufferDescriptorSet(const LibGFX::Buffer& buffer, uint32_t binding, VkDescriptorSetLayout layout);
			void freeUniformBufferDescriptorSet(VkDescriptorSet descriptorSet);	

			// SSBO's
			VkDescriptorSet allocateStorageBufferDescriptorSet(const LibGFX::Buffer& buffer, uint32_t binding, VkDescriptorSetLayout layout);
			void freeStorageBufferDescriptorSet(VkDescriptorSet descriptorSet);

			// PIPELINES
			void createPipeline(LibGFX::Pipeline& pipeline);
			void destroyPipeline(LibGFX::Pipeline& pipeline);

			// Framebuffers
			LibGFX::DepthBuffer createDepthBuffer(VkExtent2D extent, VkFormat format);
			void destroyDepthBuffer(LibGFX::DepthBuffer& depthBuffer);

			// BUFFERS
			LibGFX::Buffer createBuffer(VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties);
			void copyBuffer(const LibGFX::Buffer& srcBuffer, const LibGFX::Buffer& dstBuffer, VkDeviceSize size);
			void resizeBuffer(LibGFX::Buffer& buffer, VkDeviceSize newSize, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties);
			void recreateBuffer(LibGFX::Buffer& buffer, VkDeviceSize newSize, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties);

			template<typename T>
			void updateBuffer(const LibGFX::Buffer& buffer, const T* data, size_t count) {
				void* mappedData;

				vkMapMemory(m_context->getDevice(), buffer.memory, 0, buffer.size, 0, &mappedData);
				memcpy(mappedData, data, sizeof(T) * count);
				vkUnmapMemory(m_context->getDevice(), buffer.memory);
			}
			void destroyBuffer(LibGFX::Buffer& buffer);

			// GETTERS
			VkCommandBuffer getCommandBuffer(uint32_t imageIndex) const { return m_commandBuffers[imageIndex]; }
			size_t getSwapchainImageCount() const { return m_swapchainInfo.imageViews.size(); }
			size_t getFramebufferCount() const { return m_framebuffers.size(); }
			VkRect2D getScissor() const { return m_scissor; }
			VkViewport getViewport() const { return m_viewport; }
			LibGFX::RenderPass& getRenderPass() const { return *m_renderPass; }	
			LibGFX::RenderPass& getOffscreenRenderPass() const { return *m_offscreenRenderPass; }
			SwapchainInfo& getSwapchainInfo() { return m_swapchainInfo; }
			VkFormat getDepthFormat() const { return m_depthFormat; }
			LibGFX::VkContext& getContext() { return *m_context; }
		};
	}
}
