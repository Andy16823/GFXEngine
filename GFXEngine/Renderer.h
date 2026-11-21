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
#include <cstring>

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
			bool m_framebufferResized = false; // Set externally when the window/framebuffer size changes (e.g. resize or maximize)
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

		public:
			
			/// <summary>
			/// Default constructor for the Renderer class. 
			/// Initializes the renderer with default settings.
			/// </summary>
			Renderer() = default;
			
			/// <summary>
			/// Default destructor for the Renderer class. 
			/// Cleans up resources used by the renderer.
			/// </summary>
			~Renderer() = default;

		public:
			/// <summary>
			/// Initializes the renderer with the specified GLFW window.
			/// </summary>
			/// <param name="window"></param>
			void init(GLFWwindow* window);
			
			/// <summary>
			/// Recreates the swapchain and associated resources when 
			/// the window is resized or the swapchain becomes incompatible.
			/// </summary>
			void recreate();
			
			/// <summary>
			/// Creates synchronization objects (semaphores and fences) 
			/// for frame rendering.
			/// </summary>
			void createSyncObjects();
			
			/// <summary>
			/// Acquires the next available image from the swapchain for rendering.
			/// </summary>
			/// <returns></returns>
			uint32_t nextImage();
			
			/// <summary>
			/// Begins recording a single-use command buffer for one-time operations.
			/// </summary>
			/// <returns></returns>
			VkCommandBuffer beginSingleTimeCommands();
			
			/// <summary>
			/// Ends recording of a single-use command buffer and submits it for execution.
			/// </summary>
			/// <param name="commandBuffer"></param>
			void endSingleTimeCommands(VkCommandBuffer commandBuffer);
			
			/// <summary>
			/// Begins recording commands for a frame, preparing the command buffer for rendering.
			/// </summary>
			/// <param name="imageIndex"></param>
			void beginFrame(uint32_t imageIndex);
			
			/// <summary>
			/// Begins a render pass with the specified renderpass and framebuffer for the given image index.
			/// </summary>
			/// <param name="renderpass"></param>
			/// <param name="imageIndex"></param>
			void beginRenderPass(const LibGFX::RenderPass& renderpass, uint32_t imageIndex);
			
			/// <summary>
			/// Begins a render pass with the specified renderpass, framebuffer, and extent for the given image index.
			/// </summary>
			/// <param name="renderpass"></param>
			/// <param name="framebuffer"></param>
			/// <param name="imageIndex"></param>
			void beginRenderPass(const LibGFX::RenderPass& renderpass, const VkFramebuffer& framebuffer, uint32_t imageIndex);
			
			/// <summary>
			/// Begins a render pass with the specified renderpass, framebuffer, extent, and image index.
			/// </summary>
			/// <param name="renderpass"></param>
			/// <param name="framebuffer"></param>
			/// <param name="extent"></param>
			/// <param name="imageIndex"></param>
			void beginRenderPass(const LibGFX::RenderPass& renderpass, const VkFramebuffer& framebuffer, VkExtent2D extent, uint32_t imageIndex);
			
			/// <summary>
			/// Begins a render pass with the specified renderpass, framebuffer, viewport, scissors, and image index.
			/// </summary>
			/// <param name="renderpass"></param>
			/// <param name="framebuffer"></param>
			/// <param name="viewport"></param>
			/// <param name="scissors"></param>
			/// <param name="imageIndex"></param>
			void beginRenderPass(const LibGFX::RenderPass& renderpass, const VkFramebuffer& framebuffer, const VkViewport& viewport, const VkRect2D& scissors, uint32_t imageIndex);
			
			/// <summary>
			/// Uses the specified render pipeline for rendering commands in the current command buffer.
			/// </summary>
			/// <param name="pipeline"></param>
			/// <param name="imageIndex"></param>
			void usePipeline(const RenderPipeline& pipeline, uint32_t imageIndex);
			
			/// <summary>
			/// Ends the current render pass for the given image index, finalizing rendering commands.
			/// </summary>
			/// <param name="imageIndex"></param>
			void endRenderPass(uint32_t imageIndex);
			
			/// <summary>
			/// Ends recording commands for a frame, finalizing the command buffer for submission.
			/// </summary>
			/// <param name="imageIndex"></param>
			void endFrame(uint32_t imageIndex);
			
			/// <summary>
			/// Submits the recorded command buffer for execution and presents the rendered frame to the swapchain for the given image index.
			/// </summary>
			/// <param name="imageIndex"></param>
			void submitFrame(uint32_t imageIndex);
			
			/// <summary>
			/// Presents the rendered frame to the swapchain for the given image index, displaying it on the screen.
			/// </summary>
			/// <param name="imageIndex"></param>
			void presentFrame(uint32_t imageIndex);
			
			/// <summary>
			/// Notifies the renderer that the framebuffer has been resized, triggering a swapchain recreation on the next frame.
			/// </summary>
			void notifyFramebufferResized();
			
			/// <summary>
			/// Advances to the next frame in the rendering loop, updating the current image index and 
			/// handling synchronization for multi-frame rendering.
			/// </summary>
			void advanceFrame();
			
			/// <summary>
			/// Binds push constants to the specified pipeline layout for the given image index, 
			/// allowing for dynamic data to be passed to shaders during rendering.
			/// </summary>
			/// <param name="data"></param>
			/// <param name="size"></param>
			/// <param name="offset"></param>
			/// <param name="pipelineLayout"></param>
			/// <param name="imageIndex"></param>
			void bindPushConstants(const void* data, size_t size, size_t offset, VkPipelineLayout pipelineLayout, uint32_t imageIndex);
			
			/// <summary>
			/// Binds push constants to the specified pipeline layout for the given image index,
			/// </summary>
			/// <param name="data"></param>
			/// <param name="size"></param>
			/// <param name="pipelineLayout"></param>
			/// <param name="imageIndex"></param>
			void bindPushConstants(const void* data, size_t size, VkPipelineLayout pipelineLayout, uint32_t imageIndex);
			
			/// <summary>
			/// Binds a single descriptor set to the specified pipeline layout for the given image index,
			/// </summary>
			/// <param name="descriptorSet"></param>
			/// <param name="pipelineLayout"></param>
			/// <param name="firstSet"></param>
			/// <param name="imageIndex"></param>
			void bindDescriptorSet(const VkDescriptorSet& descriptorSet, VkPipelineLayout pipelineLayout, uint32_t firstSet, uint32_t imageIndex);
			
			/// <summary>
			/// Binds multiple descriptor sets to the specified pipeline layout for the given image index, allowing for efficient resource binding during rendering.
			/// </summary>
			/// <param name="descriptorSets"></param>
			/// <param name="pipelineLayout"></param>
			/// <param name="imageIndex"></param>
			void bindDescriptorSets(const std::vector<VkDescriptorSet>& descriptorSets, VkPipelineLayout pipelineLayout, uint32_t imageIndex);
			
			/// <summary>
			/// Draws indexed geometry using the specified vertex and index buffers for the given image index, 
			/// allowing for efficient rendering of complex meshes.
			/// </summary>
			/// <param name="vertexBuffer"></param>
			/// <param name="indexBuffer"></param>
			/// <param name="indexCount"></param>
			/// <param name="imageIndex"></param>
			/// <param name="instanceCount"></param>
			void drawBuffers(const LibGFX::Buffer& vertexBuffer, const LibGFX::Buffer& indexBuffer, uint32_t indexCount, uint32_t imageIndex, uint32_t instanceCount = 1);
			
			/// <summary>
			/// Draws a frame by acquiring the next image, recording commands, submitting the command buffer, and presenting the rendered frame to the swapchain.
			/// </summary>
			void drawFrame();
			
			/// <summary>
			/// Waits for the device to become idle, ensuring that all pending operations have completed before proceeding.
			/// </summary>
			void waitIdle() { m_context->waitIdle(); }
			
			/// <summary>
			/// Disposes of the renderer, releasing all allocated resources and cleaning up Vulkan objects.
			/// </summary>
			void dispose();

		public:
			/// <summary>
			/// Creates a descriptor set layout with the specified binding, descriptor type, and shader stage flags, allowing for efficient resource binding in shaders.
			/// </summary>
			/// <param name="binding"></param>
			/// <param name="type"></param>
			/// <param name="stageFlags"></param>
			/// <returns></returns>
			VkDescriptorSetLayout createDescriptorSetLayout(uint32_t binding, VkDescriptorType type, VkShaderStageFlags stageFlags);
			
			/// <summary>
			/// Destroys a descriptor set layout, releasing the associated resources and cleaning up Vulkan objects.
			/// </summary>
			/// <param name="layout"></param>
			void destroyDescriptorSetLayout(VkDescriptorSetLayout layout);

			/// <summary>
			/// Allocates a descriptor set for a texture image with the specified binding, allowing for efficient resource binding in shaders.
			/// </summary>
			/// <param name="image"></param>
			/// <param name="binding"></param>
			/// <returns></returns>
			VkDescriptorSet allocateTextureDescriptorSet(const LibGFX::Image& image, uint32_t binding);
			
			/// <summary>
			/// Allocates a descriptor set for a cubemap texture with the specified binding, allowing for efficient resource binding in shaders.
			/// </summary>
			/// <param name="cubemap"></param>
			/// <param name="binding"></param>
			/// <returns></returns>
			VkDescriptorSet allocateCubemapDescriptorSet(const LibGFX::Cubemap& cubemap, uint32_t binding);
			
			/// <summary>
			/// Allocates a descriptor set for a PBR material with the specified albedo, normal, metallic-roughness, 
			/// and ambient occlusion textures, allowing for efficient resource binding in shaders.
			/// </summary>
			/// <param name="albedo"></param>
			/// <param name="normal"></param>
			/// <param name="metallicRoughness"></param>
			/// <param name="ao"></param>
			/// <param name="binding"></param>
			/// <returns></returns>
			VkDescriptorSet allocatePBRMaterialDescriptorSet(const LibGFX::Image& albedo, const LibGFX::Image& normal, const LibGFX::Image& metallicRoughness, const LibGFX::Image& ao, uint32_t binding);
			
			/// <summary>
			/// Frees a previously allocated texture descriptor set, releasing the associated resources and cleaning up Vulkan objects.
			/// </summary>
			/// <param name="descriptorSet"></param>
			void freeTextureDescriptorSet(VkDescriptorSet descriptorSet); // TODO: Not used, consider removing
			
			/// <summary>
			/// Frees a previously allocated cubemap descriptor set, releasing the associated resources and cleaning up Vulkan objects.
			/// </summary>
			/// <param name="descriptorSet"></param>
			void freeCubemapDescriptorSet(VkDescriptorSet descriptorSet); // TODO: Not used, consider removing
			
			/// <summary>
			/// Frees a previously allocated PBR material descriptor set, releasing the associated resources and cleaning up Vulkan objects.
			/// </summary>
			/// <param name="descriptorSet"></param>
			void freePBRMaterialDescriptorSet(VkDescriptorSet descriptorSet); // TODO: Not used, consider removing

			/// <summary>
			/// Allocates a descriptor set for a uniform buffer with the specified binding and layout, 
			/// allowing for efficient resource binding in shaders.
			/// </summary>
			/// <param name="buffer"></param>
			/// <param name="binding"></param>
			/// <param name="layout"></param>
			/// <returns></returns>
			VkDescriptorSet allocateUniformBufferDescriptorSet(const LibGFX::Buffer& buffer, uint32_t binding, VkDescriptorSetLayout layout);
			
			/// <summary>
			/// Frees a previously allocated uniform buffer descriptor set, 
			/// releasing the associated resources and cleaning up Vulkan objects.
			/// </summary>
			/// <param name="descriptorSet"></param>
			void freeUniformBufferDescriptorSet(VkDescriptorSet descriptorSet);

			/// <summary>
			/// Allocates a descriptor set for a storage buffer with the specified binding and layout,
			/// </summary>
			/// <param name="buffer"></param>
			/// <param name="binding"></param>
			/// <param name="layout"></param>
			/// <returns></returns>
			VkDescriptorSet allocateStorageBufferDescriptorSet(const LibGFX::Buffer& buffer, uint32_t binding, VkDescriptorSetLayout layout);
			
			/// <summary>
			/// Frees a previously allocated storage buffer descriptor set, releasing the associated resources and cleaning up Vulkan objects.
			/// </summary>
			/// <param name="descriptorSet"></param>
			void freeStorageBufferDescriptorSet(VkDescriptorSet descriptorSet);

		public:
			/// <summary>
			/// Creates a shader module from the provided SPIR-V bytecode, allowing for the use of custom shaders in the rendering pipeline.
			/// </summary>
			/// <param name="code"></param>
			/// <returns></returns>
			VkShaderModule createShaderModule(const std::vector<char>& code);

		public:
			/// <summary>
			/// Creates an image with the specified extent, format, usage, and memory properties, 
			/// allowing for efficient texture and framebuffer management in Vulkan.
			/// </summary>
			/// <param name="extent"></param>
			/// <param name="format"></param>
			/// <param name="usage"></param>
			/// <param name="properties"></param>
			/// <returns></returns>
			LibGFX::Image createImage(VkExtent2D extent, VkFormat format, VkImageUsageFlags usage, VkMemoryPropertyFlags properties);
			
			/// <summary>
			/// Loads a texture from the provided image data, creating a Vulkan image and associated resources for efficient rendering.
			/// </summary>
			/// <param name="imageData"></param>
			/// <returns></returns>
			LibGFX::Image loadTexture(const LibGFX::ImageData& imageData);
			
			/// <summary>
			/// Loads a cubemap texture from the provided cubemap data, creating a Vulkan image 
			/// and associated resources for efficient rendering of environment maps.
			/// </summary>
			/// <param name="cubemapData"></param>
			/// <returns></returns>
			LibGFX::Cubemap loadCubemap(const LibGFX::CubemapData& cubemapData);
			
			/// <summary>
			/// Disposes of a previously created texture, releasing the associated resources and cleaning up Vulkan objects.
			/// </summary>
			/// <param name="image"></param>
			void disposeTexture(LibGFX::Image& image);
			
			/// <summary>
			/// Disposes of a previously created cubemap texture, releasing the associated resources and cleaning up Vulkan objects.
			/// </summary>
			/// <param name="cubemap"></param>
			void disposeCubemap(LibGFX::Cubemap& cubemap);
		
		public:
			
			/// <summary>
			/// Manages a render pipeline by associating it with a unique pipeline ID, 
			/// allowing for efficient retrieval and usage of different rendering pipelines in the renderer.
			/// </summary>
			/// <param name="pipelineId"></param>
			/// <param name="pipeline"></param>
			void managePipeline(unsigned int pipelineId, std::unique_ptr<RenderPipeline> pipeline);
			
			/// <summary>
			/// Gets a managed render pipeline ptr by its unique pipeline ID, 
			/// allowing for efficient retrieval and usage of different rendering pipelines in the renderer.
			/// </summary>
			/// <typeparam name="T"></typeparam>
			/// <param name="pipelineId"></param>
			/// <returns></returns>
			template<typename T>
			T* getPipeline(unsigned int pipelineId) const {
				return m_pipelineManager.getPipeline<T>(pipelineId);
			}

		public:
			
			/// <summary>
			/// Creates a depth buffer with the specified extent and format, allowing for efficient depth testing and rendering in Vulkan.
			/// </summary>
			/// <param name="extent"></param>
			/// <param name="format"></param>
			/// <returns></returns>
			LibGFX::DepthBuffer createDepthBuffer(VkExtent2D extent, VkFormat format);
			
			/// <summary>
			/// Destroys a previously created depth buffer, releasing the associated resources and cleaning up Vulkan objects.
			/// </summary>
			/// <param name="depthBuffer"></param>
			void destroyDepthBuffer(LibGFX::DepthBuffer& depthBuffer);

		public:
			
			/// <summary>
			/// Creates a buffer with the specified size, usage, and memory properties, allowing for efficient data storage and transfer in Vulkan.
			/// </summary>
			/// <param name="size"></param>
			/// <param name="usage"></param>
			/// <param name="properties"></param>
			/// <returns></returns>
			LibGFX::Buffer createBuffer(VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties);
			
			/// <summary>
			/// Copies data from the source buffer to the destination buffer, allowing for efficient data transfer between buffers in Vulkan.
			/// </summary>
			/// <param name="srcBuffer"></param>
			/// <param name="dstBuffer"></param>
			/// <param name="size"></param>
			void copyBuffer(const LibGFX::Buffer& srcBuffer, const LibGFX::Buffer& dstBuffer, VkDeviceSize size);
			
			/// <summary>
			/// Resizes a buffer to the specified new size, updating its usage and memory properties as needed, 
			/// allowing for dynamic buffer management in Vulkan.
			/// </summary>
			/// <param name="buffer"></param>
			/// <param name="newSize"></param>
			/// <param name="usage"></param>
			/// <param name="properties"></param>
			void resizeBuffer(LibGFX::Buffer& buffer, VkDeviceSize newSize, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties);
			
			/// <summary>
			/// Recreates a buffer with the specified new size, usage, and memory properties,
			/// </summary>
			/// <param name="buffer"></param>
			/// <param name="newSize"></param>
			/// <param name="usage"></param>
			/// <param name="properties"></param>
			void recreateBuffer(LibGFX::Buffer& buffer, VkDeviceSize newSize, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties);
			
			/// <summary>
			/// Flushes the specified buffer, ensuring that any pending writes to 
			/// the buffer are made visible to the GPU for subsequent rendering operations.
			/// </summary>
			/// <param name="buffer"></param>
			void flushBuffer(const LibGFX::Buffer& buffer);
			
			/// <summary>
			/// Destroys a previously created buffer, 
			/// releasing the associated resources and cleaning up Vulkan objects.
			/// </summary>
			/// <param name="buffer"></param>
			void destroyBuffer(LibGFX::Buffer& buffer);

			/// <summary>
			/// Updates the contents of a buffer with the specified data, 
			/// allowing for efficient data transfer to the GPU for rendering operations.
			/// </summary>
			/// <typeparam name="T">The type of the data elements.</typeparam>
			/// <param name="buffer">The buffer to update.</param>
			/// <param name="data">The data to copy into the buffer.</param>
			/// <param name="count">The number of elements to copy (not the number of bytes).</param>
			/// <param name="flush">Whether to flush the buffer after updating.</param>
			template<typename T>
			void updateBuffer(const LibGFX::Buffer& buffer, const T* data, size_t count, bool flush = false) {
				VkDeviceSize totalSize = sizeof(T) * count;
				assert(totalSize <= buffer.size);

				void* mappedData;
				vkMapMemory(m_context->getDevice(), buffer.memory, 0, buffer.size, 0, &mappedData);
				memcpy(mappedData, data, totalSize);
				if (flush)
				{
					this->flushBuffer(buffer);
				}
				vkUnmapMemory(m_context->getDevice(), buffer.memory);
			}

			/// <summary>
			/// Updates a specific range of a buffer with the specified data, allowing for efficient partial updates to the buffer's contents.
			/// </summary>
			/// <typeparam name="T">The type of the data elements.</typeparam>
			/// <param name="buffer">The buffer to update.</param>
			/// <param name="data">The data to copy into the buffer.</param>
			/// <param name="offset">The offset within the buffer to start updating.</param>
			/// <param name="flush">Whether to flush the buffer after updating.</param>
			template<typename T>
			void updateBufferRange(const LibGFX::Buffer& buffer, const T* data, size_t count, size_t offset, bool flush = false) {
				VkDeviceSize totalSize = sizeof(T) * count;
				VkDeviceSize offsetSize = offset * sizeof(T);

				assert(offsetSize + totalSize <= buffer.size);

				void* mappedData;
				vkMapMemory(m_context->getDevice(), buffer.memory, 0, buffer.size, 0, &mappedData); // Map the entire buffer to ensure we can write to the specified range
				memcpy(static_cast<char*>(mappedData) + offsetSize, data, totalSize);
				if (flush) {
					this->flushBuffer(buffer);
				}
				vkUnmapMemory(m_context->getDevice(), buffer.memory);
			}

			/// <summary>
			/// Maps a buffer's memory to a CPU-accessible pointer, 
			/// allowing for direct access to the buffer's contents for reading or writing.
			/// </summary>
			/// <param name="buffer"></param>
			/// <returns></returns>
			void* mapBuffer(const LibGFX::Buffer& buffer);
			
			/// <summary>
			/// Unmaps a previously mapped buffer's memory, 
			/// ensuring that any changes made to the buffer's contents are properly synchronized with the GPU.
			/// </summary>
			/// <param name="buffer"></param>
			void unmapBuffer(const LibGFX::Buffer& buffer);

			/// <summary>
			/// Updates the contents of a mapped buffer with the specified data, 
			/// allowing for efficient data transfer to the GPU for rendering operations.
			/// </summary>
			/// <typeparam name="T"></typeparam>
			/// <param name="mappedData"></param>
			/// <param name="bufferSize"></param>
			/// <param name="data"></param>
			/// <param name="count"></param>
			template<typename T>
			void updateMappedBuffer(void* mappedData, size_t bufferSize, const T* data, size_t count) {
				size_t totalSize = sizeof(T) * count;
				assert(totalSize <= bufferSize);
				memcpy(mappedData, data, totalSize);
			}

			/// <summary>
			/// Updates a specific range of a mapped buffer with the specified data, 
			/// allowing for efficient partial updates to the buffer's contents.
			/// </summary>
			/// <typeparam name="T"></typeparam>
			/// <param name="mappedData"></param>
			/// <param name="bufferSize"></param>
			/// <param name="data"></param>
			/// <param name="count"></param>
			/// <param name="elementOffset"></param>
			template<typename T>
			void updateMappedBufferRange(void* mappedData, size_t bufferSize, const T* data, size_t count, size_t elementOffset) {
				size_t byteOffset = elementOffset * sizeof(T);
				size_t totalSize = sizeof(T) * count;
				assert(byteOffset + totalSize <= bufferSize);
				auto dest = static_cast<char*>(mappedData) + byteOffset;
				memcpy(dest, data, totalSize);
			}

		public:

			/// <summary>
			/// Gets the command buffer for the specified image index, 
			/// allowing for recording rendering commands for that specific frame.
			/// </summary>
			/// <param name="imageIndex"></param>
			/// <returns></returns>
			VkCommandBuffer getCommandBuffer(uint32_t imageIndex) const { return m_commandBuffers[imageIndex]; }
			
			/// <summary>
			/// Gets the number of images in the swapchain, allowing for efficient management of frame rendering and presentation.
			/// </summary>
			/// <returns></returns>
			size_t getSwapchainImageCount() const { return m_swapchainInfo.imageViews.size(); }
			
			/// <summary>
			/// Gets the number of framebuffers created for the swapchain, allowing for efficient management of frame rendering and presentation.
			/// </summary>
			/// <returns></returns>
			size_t getFramebufferCount() const { return m_framebuffers.size(); }
			
			/// <summary>
			/// Gets the current image index being rendered, allowing for efficient management of frame rendering and presentation.
			/// </summary>
			/// <returns></returns>
			VkRect2D getScissor() const { return m_scissor; }
			
			/// <summary>
			/// Gets the current viewport being used for rendering, allowing for efficient management of frame rendering and presentation.
			/// </summary>
			/// <returns></returns>
			VkViewport getViewport() const { return m_viewport; }
			
			/// <summary>
			/// Gets the RenderPass used for rendering.
			/// </summary>
			/// <returns></returns>
			LibGFX::RenderPass& getRenderPass() const { return *m_renderPass; }	
			
			/// <summary>
			/// Gets the OffscreenRenderPass used for offscreen rendering.
			/// </summary>
			/// <returns></returns>
			LibGFX::RenderPass& getOffscreenRenderPass() const { return *m_offscreenRenderPass; }
			
			/// <summary>
			/// Gets the SwapchainInfo containing details about the swapchain, including image views, format, and extent.
			/// </summary>
			/// <returns></returns>
			SwapchainInfo& getSwapchainInfo() { return m_swapchainInfo; }
			
			/// <summary>
			/// Gets the depth format used for depth buffering, allowing for efficient depth testing and rendering in Vulkan.
			/// </summary>
			/// <returns></returns>
			VkFormat getDepthFormat() const { return m_depthFormat; }
			
			/// <summary>
			/// Gets the VkContext used for managing Vulkan resources and operations.
			/// </summary>
			/// <returns></returns>
			LibGFX::VkContext& getContext() { return *m_context; }
			
			/// <summary>
			/// Gets the texture sampler used for sampling textures in shaders, 
			/// allowing for efficient texture filtering and sampling in Vulkan.
			/// </summary>
			/// <returns></returns>
			VkSampler getTextureSampler() const { return m_textureSampler; }
			
			/// <summary>
			/// Gets the sampler layout used for binding texture samplers in descriptor sets
			/// </summary>
			/// <returns></returns>
			VkDescriptorSetLayout getSamplerLayout() const { return m_samplerLayout; }
			
			/// <summary>
			/// Gets the cubemap sampler layout used for binding cubemap samplers in descriptor sets
			/// </summary>
			/// <returns></returns>
			VkDescriptorSetLayout getCubemapSamplerLayout() const { return m_cubemapSamplerLayout; }
			
			/// <summary>
			/// Gets the uniform buffer layout used for binding uniform buffers in descriptor sets, 
			/// allowing for efficient resource binding in shaders.
			/// </summary>
			/// <returns></returns>
			VkDescriptorSetLayout getUniformBufferLayout() const { return m_uniformBuffferLayout; }
			
			/// <summary>
			/// Gets the storage buffer layout used for binding storage buffers in descriptor sets
			/// </summary>
			/// <returns></returns>
			VkDescriptorSetLayout getStorageBufferLayout() const { return m_storageBufferLayout; }
			
			/// <summary>
			/// Gets the PBR material layout used for binding PBR material resources in descriptor sets.
			/// </summary>
			/// <returns></returns>
			VkDescriptorSetLayout getPBRMaterialLayout() const { return m_pbrMaterialLayout; }
			
			/// <summary>
			/// Checks if validation layers are enabled for the renderer, allowing for debugging and validation of Vulkan API usage.
			/// </summary>
			/// <returns></returns>
			bool isValidationEnabled() const { return m_enableValidationLayers; }
			
			/// <summary>
			/// Gets the queue family indices for the renderer.
			/// </summary>
			/// <returns></returns>
			LibGFX::QueueFamilyIndices getQueueFamilyIndices() const { return m_queueFamilyIndices; }

		public:
			/// <summary>
			/// Sets whether validation layers are enabled for the renderer, 
			/// allowing for debugging and validation of Vulkan API usage.
			/// </summary>
			/// <param name="enabled"></param>
			void setValidationEnabled(bool enabled) { m_enableValidationLayers = enabled; }
			
			/// <summary>
			/// Sets the viewport for rendering.
			/// </summary>
			/// <param name="viewport"></param>
			void setViewport(const VkViewport& viewport) { m_viewport = viewport; }
			
			/// <summary>
			/// Sets the scissor rectangle for rendering.
			/// </summary>
			/// <param name="scissor"></param>
			void setScissor(const VkRect2D& scissor) { m_scissor = scissor; }

		public:
			/// <summary>
			/// Registers a callback function to be called when the swapchain is cleaned up, allowing for custom resource management during swapchain recreation.
			/// </summary>
			/// <param name="callback"></param>
			void registerSwapchainCleanupCallback(std::function<void(Renderer&)> callback) {
				m_swapchainCleanupCallbacks.push_back(callback);
			}
			
			/// <summary>
			/// Registers a callback function to be called when the swapchain is recreated, allowing for custom resource management during swapchain recreation.
			/// </summary>
			/// <param name="callback"></param>
			void registerSwapchainRecreationCallback(std::function<void(Renderer&, VkViewport, VkRect2D)> callback) {
				m_swapchainRecreationCallbacks.push_back(callback);
			}
		};
	}
}
