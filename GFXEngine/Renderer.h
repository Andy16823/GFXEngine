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
#include "RenderPipeline.h"
#include "GraphicResources.h"

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

			// Callbacks
			std::vector<std::function<void(Renderer&)>> m_swapchainCleanupCallbacks;
			std::vector<std::function<void(Renderer&, VkViewport viewport, VkRect2D scissors)>> m_swapchainRecreationCallbacks;

			const std::string* m_shadersDirectory;

		private:
			//************************************
			// Method:    createPipelines
			// FullName:  GFXEngine::Graphics::Renderer::createPipelines
			// Access:    private 
			// Returns:   void
			// Qualifier:
			// Parameter: const std::string & shadersDirectory
			//************************************
			void createPipelines(const std::string& shadersDirectory);

		public:
			//************************************
			// Method:    Renderer
			// FullName:  GFXEngine::Graphics::Renderer::Renderer
			// Access:    public 
			// Returns:   
			// Qualifier:
			//************************************
			Renderer() = default;
			
			//************************************
			// Method:    ~Renderer
			// FullName:  GFXEngine::Graphics::Renderer::~Renderer
			// Access:    public 
			// Returns:   
			// Qualifier:
			//************************************
			~Renderer() = default;

		public:
			//************************************
			// Method:    init
			// FullName:  GFXEngine::Graphics::Renderer::init
			// Access:    public 
			// Returns:   void
			// Qualifier:
			// Parameter: GLFWwindow * window
			// Parameter: const std::string & shadersDirectory
			//************************************
			void init(GLFWwindow* window, const std::string& shadersDirectory);
			
			//************************************
			// Method:    recreate
			// FullName:  GFXEngine::Graphics::Renderer::recreate
			// Access:    public 
			// Returns:   void
			// Qualifier:
			//************************************
			void recreate();
			
			//************************************
			// Method:    createSyncObjects
			// FullName:  GFXEngine::Graphics::Renderer::createSyncObjects
			// Access:    public 
			// Returns:   void
			// Qualifier:
			//************************************
			void createSyncObjects();
			
			//************************************
			// Method:    nextImage
			// FullName:  GFXEngine::Graphics::Renderer::nextImage
			// Access:    public 
			// Returns:   uint32_t
			// Qualifier:
			//************************************
			uint32_t nextImage();
			
			//************************************
			// Method:    beginSingleTimeCommands
			// FullName:  GFXEngine::Graphics::Renderer::beginSingleTimeCommands
			// Access:    public 
			// Returns:   VkCommandBuffer
			// Qualifier:
			//************************************
			VkCommandBuffer beginSingleTimeCommands();
			
			//************************************
			// Method:    endSingleTimeCommands
			// FullName:  GFXEngine::Graphics::Renderer::endSingleTimeCommands
			// Access:    public 
			// Returns:   void
			// Qualifier:
			// Parameter: VkCommandBuffer commandBuffer
			//************************************
			void endSingleTimeCommands(VkCommandBuffer commandBuffer);
			
			//************************************
			// Method:    beginFrame
			// FullName:  GFXEngine::Graphics::Renderer::beginFrame
			// Access:    public 
			// Returns:   void
			// Qualifier:
			// Parameter: uint32_t imageIndex
			//************************************
			void beginFrame(uint32_t imageIndex);
			
			//************************************
			// Method:    beginRenderPass
			// FullName:  GFXEngine::Graphics::Renderer::beginRenderPass
			// Access:    public 
			// Returns:   void
			// Qualifier:
			// Parameter: const LibGFX::RenderPass & renderpass
			// Parameter: uint32_t imageIndex
			//************************************
			void beginRenderPass(const LibGFX::RenderPass& renderpass, uint32_t imageIndex);
			
			//************************************
			// Method:    beginRenderPass
			// FullName:  GFXEngine::Graphics::Renderer::beginRenderPass
			// Access:    public 
			// Returns:   void
			// Qualifier:
			// Parameter: const LibGFX::RenderPass & renderpass
			// Parameter: const VkFramebuffer & framebuffer
			// Parameter: uint32_t imageIndex
			//************************************
			void beginRenderPass(const LibGFX::RenderPass& renderpass, const VkFramebuffer& framebuffer, uint32_t imageIndex);
			
			//************************************
			// Method:    beginRenderPass
			// FullName:  GFXEngine::Graphics::Renderer::beginRenderPass
			// Access:    public 
			// Returns:   void
			// Qualifier:
			// Parameter: const LibGFX::RenderPass & renderpass
			// Parameter: const VkFramebuffer & framebuffer
			// Parameter: VkExtent2D extent
			// Parameter: uint32_t imageIndex
			//************************************
			void beginRenderPass(const LibGFX::RenderPass& renderpass, const VkFramebuffer& framebuffer, VkExtent2D extent, uint32_t imageIndex);
			
			//************************************
			// Method:    beginRenderPass
			// FullName:  GFXEngine::Graphics::Renderer::beginRenderPass
			// Access:    public 
			// Returns:   void
			// Qualifier:
			// Parameter: const LibGFX::RenderPass & renderpass
			// Parameter: const VkFramebuffer & framebuffer
			// Parameter: const VkViewport & viewport
			// Parameter: const VkRect2D & scissors
			// Parameter: uint32_t imageIndex
			//************************************
			void beginRenderPass(const LibGFX::RenderPass& renderpass, const VkFramebuffer& framebuffer, const VkViewport& viewport, const VkRect2D& scissors, uint32_t imageIndex);
			
			//************************************
			// Method:    usePipeline
			// FullName:  GFXEngine::Graphics::Renderer::usePipeline
			// Access:    public 
			// Returns:   void
			// Qualifier:
			// Parameter: const RenderPipeline & pipeline
			// Parameter: uint32_t imageIndex
			//************************************
			void usePipeline(const RenderPipeline& pipeline, uint32_t imageIndex);
			
			//************************************
			// Method:    usePipeline
			// FullName:  GFXEngine::Graphics::Renderer::usePipeline
			// Access:    public 
			// Returns:   void
			// Qualifier:
			// Parameter: uint32_t imageIndex
			//************************************
			void endRenderPass(uint32_t imageIndex);
			
			//************************************
			// Method:    endFrame
			// FullName:  GFXEngine::Graphics::Renderer::endFrame
			// Access:    public 
			// Returns:   void
			// Qualifier:
			// Parameter: uint32_t imageIndex
			//************************************
			void endFrame(uint32_t imageIndex);
			
			//************************************
			// Method:    submitFrame
			// FullName:  GFXEngine::Graphics::Renderer::submitFrame
			// Access:    public 
			// Returns:   void
			// Qualifier:
			// Parameter: uint32_t imageIndex
			//************************************
			void submitFrame(uint32_t imageIndex);
			
			//************************************
			// Method:    presentFrame
			// FullName:  GFXEngine::Graphics::Renderer::presentFrame
			// Access:    public 
			// Returns:   void
			// Qualifier:
			// Parameter: uint32_t imageIndex
			//************************************
			void presentFrame(uint32_t imageIndex);
			
			//************************************
			// Method:    advanceFrame
			// FullName:  GFXEngine::Graphics::Renderer::advanceFrame
			// Access:    public 
			// Returns:   void
			// Qualifier:
			//************************************
			void advanceFrame();
			
			//************************************
			// Method:    bindPushConstants
			// FullName:  GFXEngine::Graphics::Renderer::bindPushConstants
			// Access:    public 
			// Returns:   void
			// Qualifier:
			// Parameter: const void * data
			// Parameter: size_t size
			// Parameter: size_t offset
			// Parameter: VkPipelineLayout pipelineLayout
			// Parameter: uint32_t imageIndex
			//************************************
			void bindPushConstants(const void* data, size_t size, size_t offset, VkPipelineLayout pipelineLayout, uint32_t imageIndex);
			
			//************************************
			// Method:    bindPushConstants
			// FullName:  GFXEngine::Graphics::Renderer::bindPushConstants
			// Access:    public 
			// Returns:   void
			// Qualifier:
			// Parameter: const void * data
			// Parameter: size_t size
			// Parameter: VkPipelineLayout pipelineLayout
			// Parameter: uint32_t imageIndex
			//************************************
			void bindPushConstants(const void* data, size_t size, VkPipelineLayout pipelineLayout, uint32_t imageIndex);
			
			//************************************
			// Method:    bindDescriptorSet
			// FullName:  GFXEngine::Graphics::Renderer::bindDescriptorSet
			// Access:    public 
			// Returns:   void
			// Qualifier:
			// Parameter: const VkDescriptorSet & descriptorSet
			// Parameter: VkPipelineLayout pipelineLayout
			// Parameter: uint32_t firstSet
			// Parameter: uint32_t imageIndex
			//************************************
			void bindDescriptorSet(const VkDescriptorSet& descriptorSet, VkPipelineLayout pipelineLayout, uint32_t firstSet, uint32_t imageIndex);
			
			//************************************
			// Method:    bindDescriptorSets
			// FullName:  GFXEngine::Graphics::Renderer::bindDescriptorSets
			// Access:    public 
			// Returns:   void
			// Qualifier:
			// Parameter: const std::vector<VkDescriptorSet> & descriptorSets
			// Parameter: VkPipelineLayout pipelineLayout
			// Parameter: uint32_t imageIndex
			//************************************
			void bindDescriptorSets(const std::vector<VkDescriptorSet>& descriptorSets, VkPipelineLayout pipelineLayout, uint32_t imageIndex);
			
			//************************************
			// Method:    drawBuffers
			// FullName:  GFXEngine::Graphics::Renderer::drawBuffers
			// Access:    public 
			// Returns:   void
			// Qualifier:
			// Parameter: const LibGFX::Buffer & vertexBuffer
			// Parameter: const LibGFX::Buffer & indexBuffer
			// Parameter: uint32_t indexCount
			// Parameter: uint32_t imageIndex
			// Parameter: uint32_t instanceCount
			//************************************
			void drawBuffers(const LibGFX::Buffer& vertexBuffer, const LibGFX::Buffer& indexBuffer, uint32_t indexCount, uint32_t imageIndex, uint32_t instanceCount = 1);
			
			//************************************
			// Method:    drawFrame
			// FullName:  GFXEngine::Graphics::Renderer::drawFrame
			// Access:    public 
			// Returns:   void
			// Qualifier:
			//************************************
			void drawFrame();
			
			//************************************
			// Method:    waitIdle
			// FullName:  GFXEngine::Graphics::Renderer::waitIdle
			// Access:    public 
			// Returns:   void
			// Qualifier:
			//************************************
			void waitIdle() { m_context->waitIdle(); }
			
			//************************************
			// Method:    dispose
			// FullName:  GFXEngine::Graphics::Renderer::dispose
			// Access:    public 
			// Returns:   void
			// Qualifier:
			//************************************
			void dispose();

		public:
			//************************************
			// Method:    createDescriptorSetLayout
			// FullName:  GFXEngine::Graphics::Renderer::createDescriptorSetLayout
			// Access:    public 
			// Returns:   VkDescriptorSetLayout
			// Qualifier:
			// Parameter: uint32_t binding
			// Parameter: VkDescriptorType type
			// Parameter: VkShaderStageFlags stageFlags
			//************************************
			VkDescriptorSetLayout createDescriptorSetLayout(uint32_t binding, VkDescriptorType type, VkShaderStageFlags stageFlags);
			
			//************************************
			// Method:    destroyDescriptorSetLayout
			// FullName:  GFXEngine::Graphics::Renderer::destroyDescriptorSetLayout
			// Access:    public 
			// Returns:   void
			// Qualifier:
			// Parameter: VkDescriptorSetLayout layout
			//************************************
			void destroyDescriptorSetLayout(VkDescriptorSetLayout layout);

			//************************************
			// Method:    allocateTextureDescriptorSet
			// FullName:  GFXEngine::Graphics::Renderer::allocateTextureDescriptorSet
			// Access:    public 
			// Returns:   VkDescriptorSet
			// Qualifier:
			// Parameter: const LibGFX::Image & image
			// Parameter: uint32_t binding
			//************************************
			VkDescriptorSet allocateTextureDescriptorSet(const LibGFX::Image& image, uint32_t binding);
			
			//************************************
			// Method:    allocateCubemapDescriptorSet
			// FullName:  GFXEngine::Graphics::Renderer::allocateCubemapDescriptorSet
			// Access:    public 
			// Returns:   VkDescriptorSet
			// Qualifier:
			// Parameter: const LibGFX::Cubemap & cubemap
			// Parameter: uint32_t binding
			//************************************
			VkDescriptorSet allocateCubemapDescriptorSet(const LibGFX::Cubemap& cubemap, uint32_t binding);
			
			//************************************
			// Method:    allocatePBRMaterialDescriptorSet
			// FullName:  GFXEngine::Graphics::Renderer::allocatePBRMaterialDescriptorSet
			// Access:    public 
			// Returns:   VkDescriptorSet
			// Qualifier:
			// Parameter: const LibGFX::Image & albedo
			// Parameter: const LibGFX::Image & normal
			// Parameter: const LibGFX::Image & metallicRoughness
			// Parameter: const LibGFX::Image & ao
			// Parameter: uint32_t binding
			//************************************
			VkDescriptorSet allocatePBRMaterialDescriptorSet(const LibGFX::Image& albedo, const LibGFX::Image& normal, const LibGFX::Image& metallicRoughness, const LibGFX::Image& ao, uint32_t binding);
			
			//************************************
			// Method:    freeTextureDescriptorSet
			// FullName:  GFXEngine::Graphics::Renderer::freeTextureDescriptorSet
			// Access:    public 
			// Returns:   void
			// Qualifier:
			// Parameter: VkDescriptorSet descriptorSet
			//************************************
			void freeTextureDescriptorSet(VkDescriptorSet descriptorSet); // TODO: Not used, consider removing
			
			//************************************
			// Method:    freeCubemapDescriptorSet
			// FullName:  GFXEngine::Graphics::Renderer::freeCubemapDescriptorSet
			// Access:    public 
			// Returns:   void
			// Qualifier:
			// Parameter: VkDescriptorSet descriptorSet
			//************************************
			void freeCubemapDescriptorSet(VkDescriptorSet descriptorSet); // TODO: Not used, consider removing
			
			//************************************
			// Method:    freePBRMaterialDescriptorSet
			// FullName:  GFXEngine::Graphics::Renderer::freePBRMaterialDescriptorSet
			// Access:    public 
			// Returns:   void
			// Qualifier:
			// Parameter: VkDescriptorSet descriptorSet
			//************************************
			void freePBRMaterialDescriptorSet(VkDescriptorSet descriptorSet); // TODO: Not used, consider removing

			//************************************
			// Method:    allocateUniformBufferDescriptorSet
			// FullName:  GFXEngine::Graphics::Renderer::allocateUniformBufferDescriptorSet
			// Access:    public 
			// Returns:   VkDescriptorSet
			// Qualifier:
			// Parameter: const LibGFX::Buffer & buffer
			// Parameter: uint32_t binding
			// Parameter: VkDescriptorSetLayout layout
			//************************************
			VkDescriptorSet allocateUniformBufferDescriptorSet(const LibGFX::Buffer& buffer, uint32_t binding, VkDescriptorSetLayout layout);
			
			//************************************
			// Method:    freeUniformBufferDescriptorSet
			// FullName:  GFXEngine::Graphics::Renderer::freeUniformBufferDescriptorSet
			// Access:    public 
			// Returns:   void
			// Qualifier:
			// Parameter: VkDescriptorSet descriptorSet
			//************************************
			void freeUniformBufferDescriptorSet(VkDescriptorSet descriptorSet);

			//************************************
			// Method:    allocateStorageBufferDescriptorSet
			// FullName:  GFXEngine::Graphics::Renderer::allocateStorageBufferDescriptorSet
			// Access:    public 
			// Returns:   VkDescriptorSet
			// Qualifier:
			// Parameter: const LibGFX::Buffer & buffer
			// Parameter: uint32_t binding
			// Parameter: VkDescriptorSetLayout layout
			//************************************
			VkDescriptorSet allocateStorageBufferDescriptorSet(const LibGFX::Buffer& buffer, uint32_t binding, VkDescriptorSetLayout layout);
			
			//************************************
			// Method:    freeStorageBufferDescriptorSet
			// FullName:  GFXEngine::Graphics::Renderer::freeStorageBufferDescriptorSet
			// Access:    public 
			// Returns:   void
			// Qualifier:
			// Parameter: VkDescriptorSet descriptorSet
			//************************************
			void freeStorageBufferDescriptorSet(VkDescriptorSet descriptorSet);

		public:
			//************************************
			// Method:    createShaderModule
			// FullName:  GFXEngine::Graphics::Renderer::createShaderModule
			// Access:    public 
			// Returns:   VkShaderModule
			// Qualifier:
			// Parameter: const std::vector<char> & code
			//************************************
			VkShaderModule createShaderModule(const std::vector<char>& code);

		public:
			//************************************
			// Method:    createImage
			// FullName:  GFXEngine::Graphics::Renderer::createImage
			// Access:    public 
			// Returns:   LibGFX::Image
			// Qualifier:
			// Parameter: VkExtent2D extent
			// Parameter: VkFormat format
			// Parameter: VkImageUsageFlags usage
			// Parameter: VkMemoryPropertyFlags properties
			//************************************
			LibGFX::Image createImage(VkExtent2D extent, VkFormat format, VkImageUsageFlags usage, VkMemoryPropertyFlags properties);
			
			//************************************
			// Method:    loadTexture
			// FullName:  GFXEngine::Graphics::Renderer::loadTexture
			// Access:    public 
			// Returns:   LibGFX::Image
			// Qualifier:
			// Parameter: const LibGFX::ImageData & imageData
			//************************************
			LibGFX::Image loadTexture(const LibGFX::ImageData& imageData);
			
			//************************************
			// Method:    loadCubemap
			// FullName:  GFXEngine::Graphics::Renderer::loadCubemap
			// Access:    public 
			// Returns:   LibGFX::Cubemap
			// Qualifier:
			// Parameter: const LibGFX::CubemapData & cubemapData
			//************************************
			LibGFX::Cubemap loadCubemap(const LibGFX::CubemapData& cubemapData);
			
			//************************************
			// Method:    disposeTexture
			// FullName:  GFXEngine::Graphics::Renderer::disposeTexture
			// Access:    public 
			// Returns:   void
			// Qualifier:
			// Parameter: LibGFX::Image & image
			//************************************
			void disposeTexture(LibGFX::Image& image);
			
			//************************************
			// Method:    disposeCubemap
			// FullName:  GFXEngine::Graphics::Renderer::disposeCubemap
			// Access:    public 
			// Returns:   void
			// Qualifier:
			// Parameter: LibGFX::Cubemap & cubemap
			//************************************
			void disposeCubemap(LibGFX::Cubemap& cubemap);
		

		public:
			//************************************
			// Method:    managePipeline
			// FullName:  GFXEngine::Graphics::Renderer::managePipeline
			// Access:    public 
			// Returns:   void
			// Qualifier:
			// Parameter: unsigned int pipelineId
			// Parameter: std::unique_ptr<RenderPipeline> pipeline
			//************************************
			void managePipeline(unsigned int pipelineId, std::unique_ptr<RenderPipeline> pipeline);
			
			//************************************
			// Method:    getPipeline
			// FullName:  GFXEngine::Graphics::Renderer::getPipeline
			// Access:    public 
			// Returns:   T*
			// Qualifier: const
			// Parameter: unsigned int pipelineId
			//************************************
			template<typename T>
			T* getPipeline(unsigned int pipelineId) const {
				return m_pipelineManager.getPipeline<T>(pipelineId);
			}

		public:
			//************************************
			// Method:    createDepthBuffer
			// FullName:  GFXEngine::Graphics::Renderer::createDepthBuffer
			// Access:    public 
			// Returns:   LibGFX::DepthBuffer
			// Qualifier:
			// Parameter: VkExtent2D extent
			// Parameter: VkFormat format
			//************************************
			LibGFX::DepthBuffer createDepthBuffer(VkExtent2D extent, VkFormat format);
			
			//************************************
			// Method:    destroyDepthBuffer
			// FullName:  GFXEngine::Graphics::Renderer::destroyDepthBuffer
			// Access:    public 
			// Returns:   void
			// Qualifier:
			// Parameter: LibGFX::DepthBuffer & depthBuffer
			//************************************
			void destroyDepthBuffer(LibGFX::DepthBuffer& depthBuffer);

		public:
			//************************************
			// Method:    createBuffer
			// FullName:  GFXEngine::Graphics::Renderer::createBuffer
			// Access:    public 
			// Returns:   LibGFX::Buffer
			// Qualifier:
			// Parameter: VkDeviceSize size
			// Parameter: VkBufferUsageFlags usage
			// Parameter: VkMemoryPropertyFlags properties
			//************************************
			LibGFX::Buffer createBuffer(VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties);
			
			//************************************
			// Method:    copyBuffer
			// FullName:  GFXEngine::Graphics::Renderer::copyBuffer
			// Access:    public 
			// Returns:   void
			// Qualifier:
			// Parameter: const LibGFX::Buffer & srcBuffer
			// Parameter: const LibGFX::Buffer & dstBuffer
			// Parameter: VkDeviceSize size
			//************************************
			void copyBuffer(const LibGFX::Buffer& srcBuffer, const LibGFX::Buffer& dstBuffer, VkDeviceSize size);
			
			//************************************
			// Method:    resizeBuffer
			// FullName:  GFXEngine::Graphics::Renderer::resizeBuffer
			// Access:    public 
			// Returns:   void
			// Qualifier:
			// Parameter: LibGFX::Buffer & buffer
			// Parameter: VkDeviceSize newSize
			// Parameter: VkBufferUsageFlags usage
			// Parameter: VkMemoryPropertyFlags properties
			//************************************
			void resizeBuffer(LibGFX::Buffer& buffer, VkDeviceSize newSize, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties);
			
			//************************************
			// Method:    recreateBuffer
			// FullName:  GFXEngine::Graphics::Renderer::recreateBuffer
			// Access:    public 
			// Returns:   void
			// Qualifier:
			// Parameter: LibGFX::Buffer & buffer
			// Parameter: VkDeviceSize newSize
			// Parameter: VkBufferUsageFlags usage
			// Parameter: VkMemoryPropertyFlags properties
			//************************************
			void recreateBuffer(LibGFX::Buffer& buffer, VkDeviceSize newSize, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties);
			
			//************************************
			// Method:    flushBuffer
			// FullName:  GFXEngine::Graphics::Renderer::flushBuffer
			// Access:    public 
			// Returns:   void
			// Qualifier:
			// Parameter: const LibGFX::Buffer & buffer
			//************************************
			void flushBuffer(const LibGFX::Buffer& buffer);
			
			//************************************
			// Method:    destroyBuffer
			// FullName:  GFXEngine::Graphics::Renderer::destroyBuffer
			// Access:    public 
			// Returns:   void
			// Qualifier:
			// Parameter: LibGFX::Buffer & buffer
			//************************************
			void destroyBuffer(LibGFX::Buffer& buffer);

			//************************************
			// Method:    updateBuffer
			// FullName:  GFXEngine::Graphics::Renderer::updateBuffer
			// Access:    public 
			// Returns:   void
			// Qualifier:
			// Parameter: const LibGFX::Buffer & buffer
			// Parameter: const T * data
			// Parameter: size_t count
			// Parameter: bool flush
			//************************************
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

			//************************************
			// Method:    updateBufferRange
			// FullName:  GFXEngine::Graphics::Renderer::updateBufferRange
			// Access:    public 
			// Returns:   void
			// Qualifier:
			// Parameter: const LibGFX::Buffer & buffer
			// Parameter: const T * data
			// Parameter: size_t offset
			// Parameter: bool flush
			//************************************
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

			//************************************
			// Method:    mapBuffer
			// FullName:  GFXEngine::Graphics::Renderer::mapBuffer
			// Access:    public 
			// Returns:   void*
			// Qualifier:
			// Parameter: const LibGFX::Buffer & buffer
			//************************************
			void* mapBuffer(const LibGFX::Buffer& buffer);
			
			//************************************
			// Method:    unmapBuffer
			// FullName:  GFXEngine::Graphics::Renderer::unmapBuffer
			// Access:    public 
			// Returns:   void
			// Qualifier:
			// Parameter: const LibGFX::Buffer & buffer
			//************************************
			void unmapBuffer(const LibGFX::Buffer& buffer);

			//************************************
			// Method:    updateMappedBuffer
			// FullName:  GFXEngine::Graphics::Renderer::updateMappedBuffer
			// Access:    public 
			// Returns:   void
			// Qualifier:
			// Parameter: void * mappedData
			// Parameter: size_t bufferSize
			// Parameter: const T * data
			// Parameter: size_t count
			//************************************
			template<typename T>
			void updateMappedBuffer(void* mappedData, size_t bufferSize, const T* data, size_t count) {
				size_t totalSize = sizeof(T) * count;
				assert(totalSize <= bufferSize, "Buffer update size exceeds buffer size");
				memcpy(mappedData, data, totalSize);
			}

			//************************************
			// Method:    updateMappedBufferRange
			// FullName:  GFXEngine::Graphics::Renderer::updateMappedBufferRange
			// Access:    public 
			// Returns:   void
			// Qualifier:
			// Parameter: void * mappedData
			// Parameter: size_t bufferSize
			// Parameter: const T * data
			// Parameter: size_t count
			// Parameter: size_t elementOffset
			//************************************
			template<typename T>
			void updateMappedBufferRange(void* mappedData, size_t bufferSize, const T* data, size_t count, size_t elementOffset) {
				size_t byteOffset = elementOffset * sizeof(T);
				size_t totalSize = sizeof(T) * count;
				assert(byteOffset + totalSize <= bufferSize, "Buffer update range exceeds buffer size");
				auto dest = static_cast<char*>(mappedData) + byteOffset;
				memcpy(dest, data, totalSize);
			}

		public:
			//************************************
			// Method:    getCommandBuffer
			// FullName:  GFXEngine::Graphics::Renderer::getCommandBuffer
			// Access:    public 
			// Returns:   VkCommandBuffer
			// Qualifier: const
			// Parameter: uint32_t imageIndex
			//************************************
			VkCommandBuffer getCommandBuffer(uint32_t imageIndex) const { return m_commandBuffers[imageIndex]; }
			
			//************************************
			// Method:    getSwapchainImageCount
			// FullName:  GFXEngine::Graphics::Renderer::getSwapchainImageCount
			// Access:    public 
			// Returns:   std::size_t
			// Qualifier: const
			//************************************
			size_t getSwapchainImageCount() const { return m_swapchainInfo.imageViews.size(); }
			
			//************************************
			// Method:    getFramebufferCount
			// FullName:  GFXEngine::Graphics::Renderer::getFramebufferCount
			// Access:    public 
			// Returns:   std::size_t
			// Qualifier: const
			//************************************
			size_t getFramebufferCount() const { return m_framebuffers.size(); }
			
			//************************************
			// Method:    getScissor
			// FullName:  GFXEngine::Graphics::Renderer::getScissor
			// Access:    public 
			// Returns:   VkRect2D
			// Qualifier: const
			//************************************
			VkRect2D getScissor() const { return m_scissor; }
			
			//************************************
			// Method:    getViewport
			// FullName:  GFXEngine::Graphics::Renderer::getViewport
			// Access:    public 
			// Returns:   VkViewport
			// Qualifier: const
			//************************************
			VkViewport getViewport() const { return m_viewport; }
			
			//************************************
			// Method:    getRenderPass
			// FullName:  GFXEngine::Graphics::Renderer::getRenderPass
			// Access:    public 
			// Returns:   LibGFX::RenderPass&
			// Qualifier: const
			//************************************
			LibGFX::RenderPass& getRenderPass() const { return *m_renderPass; }	
			
			//************************************
			// Method:    getOffscreenRenderPass
			// FullName:  GFXEngine::Graphics::Renderer::getOffscreenRenderPass
			// Access:    public 
			// Returns:   LibGFX::RenderPass&
			// Qualifier: const
			//************************************
			LibGFX::RenderPass& getOffscreenRenderPass() const { return *m_offscreenRenderPass; }
			
			//************************************
			// Method:    getSwapchainInfo
			// FullName:  GFXEngine::Graphics::Renderer::getSwapchainInfo
			// Access:    public 
			// Returns:   SwapchainInfo&
			// Qualifier:
			//************************************
			SwapchainInfo& getSwapchainInfo() { return m_swapchainInfo; }
			
			//************************************
			// Method:    getDepthFormat
			// FullName:  GFXEngine::Graphics::Renderer::getDepthFormat
			// Access:    public 
			// Returns:   VkFormat
			// Qualifier: const
			//************************************
			VkFormat getDepthFormat() const { return m_depthFormat; }
			
			//************************************
			// Method:    getContext
			// FullName:  GFXEngine::Graphics::Renderer::getContext
			// Access:    public 
			// Returns:   LibGFX::VkContext&
			// Qualifier:
			//************************************
			LibGFX::VkContext& getContext() { return *m_context; }
			
			//************************************
			// Method:    getTextureSampler
			// FullName:  GFXEngine::Graphics::Renderer::getTextureSampler
			// Access:    public 
			// Returns:   VkSampler
			// Qualifier: const
			//************************************
			VkSampler getTextureSampler() const { return m_textureSampler; }
			
			//************************************
			// Method:    getSamplerLayout
			// FullName:  GFXEngine::Graphics::Renderer::getSamplerLayout
			// Access:    public 
			// Returns:   VkDescriptorSetLayout
			// Qualifier: const
			//************************************
			VkDescriptorSetLayout getSamplerLayout() const { return m_samplerLayout; }
			
			//************************************
			// Method:    getCubemapSamplerLayout
			// FullName:  GFXEngine::Graphics::Renderer::getCubemapSamplerLayout
			// Access:    public 
			// Returns:   VkDescriptorSetLayout
			// Qualifier: const
			//************************************
			VkDescriptorSetLayout getCubemapSamplerLayout() const { return m_cubemapSamplerLayout; }
			
			//************************************
			// Method:    getUniformBufferLayout
			// FullName:  GFXEngine::Graphics::Renderer::getUniformBufferLayout
			// Access:    public 
			// Returns:   VkDescriptorSetLayout
			// Qualifier: const
			//************************************
			VkDescriptorSetLayout getUniformBufferLayout() const { return m_uniformBuffferLayout; }
			
			//************************************
			// Method:    getStorageBufferLayout
			// FullName:  GFXEngine::Graphics::Renderer::getStorageBufferLayout
			// Access:    public 
			// Returns:   VkDescriptorSetLayout
			// Qualifier: const
			//************************************
			VkDescriptorSetLayout getStorageBufferLayout() const { return m_storageBufferLayout; }
			
			//************************************
			// Method:    getPBRMaterialLayout
			// FullName:  GFXEngine::Graphics::Renderer::getPBRMaterialLayout
			// Access:    public 
			// Returns:   VkDescriptorSetLayout
			// Qualifier: const
			//************************************
			VkDescriptorSetLayout getPBRMaterialLayout() const { return m_pbrMaterialLayout; }
			
			//************************************
			// Method:    isValidationEnabled
			// FullName:  GFXEngine::Graphics::Renderer::isValidationEnabled
			// Access:    public 
			// Returns:   bool
			// Qualifier: const
			//************************************
			bool isValidationEnabled() const { return m_enableValidationLayers; }
			
			//************************************
			// Method:    getQueueFamilyIndices
			// FullName:  GFXEngine::Graphics::Renderer::getQueueFamilyIndices
			// Access:    public 
			// Returns:   LibGFX::QueueFamilyIndices
			// Qualifier: const
			//************************************
			LibGFX::QueueFamilyIndices getQueueFamilyIndices() const { return m_queueFamilyIndices; }

		public:
			//************************************
			// Method:    setValidationEnabled
			// FullName:  GFXEngine::Graphics::Renderer::setValidationEnabled
			// Access:    public 
			// Returns:   void
			// Qualifier:
			// Parameter: bool enabled
			//************************************
			void setValidationEnabled(bool enabled) { m_enableValidationLayers = enabled; }
			
			//************************************
			// Method:    setViewport
			// FullName:  GFXEngine::Graphics::Renderer::setViewport
			// Access:    public 
			// Returns:   void
			// Qualifier:
			// Parameter: const VkViewport & viewport
			//************************************
			void setViewport(const VkViewport& viewport) { m_viewport = viewport; }
			
			//************************************
			// Method:    setScissor
			// FullName:  GFXEngine::Graphics::Renderer::setScissor
			// Access:    public 
			// Returns:   void
			// Qualifier:
			// Parameter: const VkRect2D & scissor
			//************************************
			void setScissor(const VkRect2D& scissor) { m_scissor = scissor; }

		public:
			//************************************
			// Method:    registerSwapchainCleanupCallback
			// FullName:  GFXEngine::Graphics::Renderer::registerSwapchainCleanupCallback
			// Access:    public 
			// Returns:   void
			// Qualifier:
			// Parameter: std::function<void
			// Parameter: Renderer & 
			// Parameter: > callback
			//************************************
			void registerSwapchainCleanupCallback(std::function<void(Renderer&)> callback) {
				m_swapchainCleanupCallbacks.push_back(callback);
			}
			
			//************************************
			// Method:    registerSwapchainRecreationCallback
			// FullName:  GFXEngine::Graphics::Renderer::registerSwapchainRecreationCallback
			// Access:    public 
			// Returns:   void
			// Qualifier:
			// Parameter: std::function<void
			// Parameter: Renderer &
			// Parameter: VkViewport
			// Parameter: VkRect2D
			// Parameter: > callback
			//************************************
			void registerSwapchainRecreationCallback(std::function<void(Renderer&, VkViewport, VkRect2D)> callback) {
				m_swapchainRecreationCallbacks.push_back(callback);
			}
		};
	}
}
