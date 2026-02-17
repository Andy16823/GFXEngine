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

namespace GFXEngine {
	namespace Graphics {
		class Renderer
		{
		private:
			VkRect2D m_scissor;
			VkViewport m_viewport;

			// Synchronization objects
			int m_currentImage = 0;
			int m_maxFramesInFlight = 2;
			std::vector<VkFence> m_imagesInFlight; // Track which fence is currently using each swapchain image
			std::vector<VkFence> m_inFlightFences;
			std::vector<VkSemaphore> m_imageAvailableSemaphores;
			std::vector<VkSemaphore> m_renderFinishedSemaphores;

			std::unique_ptr<LibGFX::VkContext> m_context;
			SwapchainInfo m_swapchainInfo;
			VkFormat m_depthFormat;
			LibGFX::DepthBuffer m_depthBuffer;
			std::unique_ptr<LibGFX::Presets::DefaultRenderPass> m_renderPass;
			std::unique_ptr<OffscreenRenderPass> m_offscreenRenderPass;
			std::vector<VkFramebuffer> m_framebuffers;
			LibGFX::QueueFamilyIndices m_queueFamilyIndices;
			std::vector<VkCommandBuffer> m_commandBuffers;

			// Texture samplers
			VkDescriptorPool m_textureDescriptorPool;
			VkSampler m_textureSampler;


			// Descriptor pools
			

			VkCommandPool m_commandPool;

		public:
			Renderer() = default;
			~Renderer() = default;
			void init(GLFWwindow* window);
			void createSyncObjects();
			uint32_t nextImage();
			void beginFrame(uint32_t imageIndex);
			void usePipeline(LibGFX::Pipeline& pipeline, uint32_t imageIndex);
			void endFrame(uint32_t imageIndex);
			void submitFrame(uint32_t imageIndex);
			void presentFrame(uint32_t imageIndex);
			void advanceFrame();
			void drawFrame();
			void dispose();
			LibGFX::Image loadTexture(const LibGFX::ImageData& imageData);
			void disposeTexture(LibGFX::Image& image);
			VkDescriptorSet allocateTextureDescriptorSet(const LibGFX::Image& image, uint32_t binding, VkDescriptorSetLayout layout);
			void freeTextureDescriptorSet(VkDescriptorSet descriptorSet);
			void createPipeline(LibGFX::Pipeline& pipeline);
			void destroyPipeline(LibGFX::Pipeline& pipeline);
			void waitIdle() { m_context->waitIdle(); }
			LibGFX::Buffer createVertexBuffer(const std::vector<EngineTypes::Vertex3D>& vertices);
			LibGFX::Buffer createIndexBuffer(const std::vector<uint32_t>& indices);
			// Getters and Setters
			VkRect2D getScissor() const { return m_scissor; }
			VkViewport getViewport() const { return m_viewport; }
			LibGFX::RenderPass& getRenderPass() const { return *m_renderPass; }
		};
	}
}
