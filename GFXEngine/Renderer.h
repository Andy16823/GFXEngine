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
#include <vector>
#include <string>
#include "PresentPipeline.h"
#include "GeometryPipeline.h"
#include "InstancedGeometryPipeline.h"
#include "EnviromentPipeline.h"
#include "DebugPipeline.h"

const uint32_t TEXTURE_SAMPLER_DESCRIPTOR_COUNT = 16;
const uint32_t TEXTURE_SAMPLER_MAX_SETS = 512;
const uint32_t UNIFORM_BUFFER_DESCRIPTOR_COUNT = 16;
const uint32_t UNIFORM_BUFFER_MAX_SETS = 512;
const uint32_t STORAGE_BUFFER_DESCRIPTOR_COUNT = 16;
const uint32_t STORAGE_BUFFER_MAX_SETS = 512;

const uint32_t CAMERA_UBO_BINDING = 0;
const uint32_t MATERIAL_UBO_BINDING = 1;
const uint32_t LIGHTS_UBO_BINDING = 2;
const uint32_t INSTANCE_SSBO_BINDING = 3;

namespace GFXEngine {
	namespace Graphics {
		class Renderer
		{
		private:
			// BASIC RENDERING RESOURCES
			std::unique_ptr<LibGFX::VkContext> m_context;
			VkRect2D m_scissor;
			VkViewport m_viewport;
			bool m_enableValidationLayers = true;

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

			// Pipelines
			PipelineManager m_pipelineManager;

			// COMMAND POOL
			VkCommandPool m_commandPool;

			// TEXTURE SAMPLERS
			VkSampler m_textureSampler;
			VkSampler m_cubemapSampler;

			// DESCRIPTOR POOLS
			VkDescriptorPool m_samplerDescriptorPool;
			VkDescriptorPool m_uniformBufferDescriptorPool;
			VkDescriptorPool m_storageBufferDescriptorPool;

			// Descriptor set layouts
			VkDescriptorSetLayout m_samplerLayout;
			VkDescriptorSetLayout m_cubemapSamplerLayout;
			VkDescriptorSetLayout m_uniformBuffferLayout;
			VkDescriptorSetLayout m_storageBufferLayout;
			VkDescriptorSetLayout m_pbrMaterialLayout;

			void createPipelines(const std::string& shadersDirectory);

		public:
			// CONSTRUCTORS & DESTRUCTORS
			Renderer() = default;
			~Renderer() = default;

			// MAIN LOOP FUNCTIONS
			void init(GLFWwindow* window, const std::string& shadersDirectory);
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
			void destroyDescriptorSetLayout(VkDescriptorSetLayout layout);

			// TEXTURES
			LibGFX::Image createImage(VkExtent2D extent, VkFormat format, VkImageUsageFlags usage, VkMemoryPropertyFlags properties);
			LibGFX::Image loadTexture(const LibGFX::ImageData& imageData);
			LibGFX::Cubemap loadCubemap(const LibGFX::CubemapData& cubemapData);
			void disposeTexture(LibGFX::Image& image);
			void disposeCubemap(LibGFX::Cubemap& cubemap);
			VkDescriptorSet allocateTextureDescriptorSet(const LibGFX::Image& image, uint32_t binding);
			VkDescriptorSet allocateCubemapDescriptorSet(const LibGFX::Cubemap& cubemap, uint32_t binding);
			VkDescriptorSet allocatePBRMaterialDescriptorSet(const LibGFX::Image& albedo, const LibGFX::Image& normal, const LibGFX::Image& metallicRoughness, const LibGFX::Image& ao, uint32_t binding);
			void freeTextureDescriptorSet(VkDescriptorSet descriptorSet); // TODO: Not used, consider removing
			void freeCubemapDescriptorSet(VkDescriptorSet descriptorSet); // TODO: Not used, consider removing
			void freePBRMaterialDescriptorSet(VkDescriptorSet descriptorSet); // TODO: Not used, consider removing

			// UNIFORM BUFFERS
			VkDescriptorSet allocateUniformBufferDescriptorSet(const LibGFX::Buffer& buffer, uint32_t binding, VkDescriptorSetLayout layout);
			void freeUniformBufferDescriptorSet(VkDescriptorSet descriptorSet);	

			// SSBO's
			VkDescriptorSet allocateStorageBufferDescriptorSet(const LibGFX::Buffer& buffer, uint32_t binding, VkDescriptorSetLayout layout);
			void freeStorageBufferDescriptorSet(VkDescriptorSet descriptorSet);

			// PIPELINES
			void createPipeline(LibGFX::Pipeline& pipeline);
			void destroyPipeline(LibGFX::Pipeline& pipeline);
			void managePipeline(unsigned int pipelineId, std::unique_ptr<LibGFX::Pipeline> pipeline);
			template<typename T>
			T* getPipeline(unsigned int pipelineId) const {
				return m_pipelineManager.getPipeline<T>(pipelineId);
			}

			// Framebuffers
			LibGFX::DepthBuffer createDepthBuffer(VkExtent2D extent, VkFormat format);
			void destroyDepthBuffer(LibGFX::DepthBuffer& depthBuffer);

			// BUFFERS
			LibGFX::Buffer createBuffer(VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties);
			void copyBuffer(const LibGFX::Buffer& srcBuffer, const LibGFX::Buffer& dstBuffer, VkDeviceSize size);
			void resizeBuffer(LibGFX::Buffer& buffer, VkDeviceSize newSize, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties);
			void recreateBuffer(LibGFX::Buffer& buffer, VkDeviceSize newSize, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties);
			void flushBuffer(const LibGFX::Buffer& buffer);
			void destroyBuffer(LibGFX::Buffer& buffer);

			template<typename T>
			void updateBuffer(const LibGFX::Buffer& buffer, const T* data, size_t count, bool flush = false) {
				void* mappedData;

				vkMapMemory(m_context->getDevice(), buffer.memory, 0, buffer.size, 0, &mappedData);
				memcpy(mappedData, data, sizeof(T) * count);
				if (flush)
				{
					this->flushBuffer(buffer);
				}
				vkUnmapMemory(m_context->getDevice(), buffer.memory);
			}

			template<typename T>
			void updateBufferRange(const LibGFX::Buffer& buffer, const T* data, size_t offset, bool flush = false) {
				void* mappedData;
				vkMapMemory(m_context->getDevice(), buffer.memory, offset, sizeof(T), 0, &mappedData);
				memcpy(mappedData, data, sizeof(T));
				if (flush) {
					this->flushBuffer(buffer);
				}
				vkUnmapMemory(m_context->getDevice(), buffer.memory);
			}

			// Persitent mapping functions for dynamic buffers
			void* mapBuffer(const LibGFX::Buffer& buffer);
			void unmapBuffer(const LibGFX::Buffer& buffer);

			template<typename T>
			void updateMappedBuffer(void* mappedData, size_t bufferSize, const T* data, size_t count) {
				size_t totalSize = sizeof(T) * count;
				assert(totalSize <= bufferSize, "Buffer update size exceeds buffer size");
				memcpy(mappedData, data, totalSize);
			}

			template<typename T>
			void updateMappedBufferRange(void* mappedData, size_t bufferSize, const T* data, size_t count, size_t elementOffset) {
				size_t byteOffset = elementOffset * sizeof(T);
				size_t totalSize = sizeof(T) * count;
				assert(byteOffset + totalSize <= bufferSize, "Buffer update range exceeds buffer size");
				auto dest = static_cast<char*>(mappedData) + byteOffset;
				memcpy(dest, data, totalSize);
			}

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
			VkDescriptorSetLayout getSamplerLayout() const { return m_samplerLayout; }
			VkDescriptorSetLayout getCubemapSamplerLayout() const { return m_cubemapSamplerLayout; }
			VkDescriptorSetLayout getUniformBufferLayout() const { return m_uniformBuffferLayout; }
			VkDescriptorSetLayout getStorageBufferLayout() const { return m_storageBufferLayout; }
			VkDescriptorSetLayout getPBRMaterialLayout() const { return m_pbrMaterialLayout; }
			bool isValidationEnabled() const { return m_enableValidationLayers; }

			// SETTERS
			void setValidationEnabled(bool enabled) { m_enableValidationLayers = enabled; }
		};
	}
}
