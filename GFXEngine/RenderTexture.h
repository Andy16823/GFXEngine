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
			VkDescriptorSet m_descriptorSet;

		public:
			//************************************
			// Method:    RenderTexture
			// FullName:  GFXEngine::Graphics::RenderTexture::RenderTexture
			// Access:    public 
			// Returns:   
			// Qualifier:
			//************************************
			RenderTexture() = default;
			
			//************************************
			// Method:    ~RenderTexture
			// FullName:  GFXEngine::Graphics::RenderTexture::~RenderTexture
			// Access:    virtual public 
			// Returns:   
			// Qualifier:
			//************************************
			virtual ~RenderTexture() = default;
			
		public:
			//************************************
			// Method:    getFramebuffer
			// FullName:  GFXEngine::Graphics::RenderTexture::getFramebuffer
			// Access:    virtual public 
			// Returns:   VkFramebuffer
			// Qualifier: const 
			//************************************
			virtual VkFramebuffer getFramebuffer() const override;
			
			//************************************
			// Method:    getExtent
			// FullName:  GFXEngine::Graphics::RenderTexture::getExtent
			// Access:    virtual public 
			// Returns:   VkExtent2D
			// Qualifier: const 
			//************************************
			virtual VkExtent2D getExtent() const override;
			
			//************************************
			// Method:    getClearValues
			// FullName:  GFXEngine::Graphics::RenderTexture::getClearValues
			// Access:    virtual public 
			// Returns:   std::span<const VkClearValue>
			// Qualifier: const 
			//************************************
			virtual std::span<const VkClearValue> getClearValues() const override;

			//************************************
			// Method:    getColorImageView
			// FullName:  GFXEngine::Graphics::RenderTexture::getColorImageView
			// Access:    public 
			// Returns:   VkImageView
			// Qualifier: const
			//************************************
			VkImageView getColorImageView() const { return m_colorAttachment.imageView; }
			
			//************************************
			// Method:    getDepthImageView
			// FullName:  GFXEngine::Graphics::RenderTexture::getDepthImageView
			// Access:    public 
			// Returns:   VkImageView
			// Qualifier: const
			//************************************
			VkImageView getDepthImageView() const { return m_depthAttachment.imageView; }
			
			//************************************
			// Method:    getViewport
			// FullName:  GFXEngine::Graphics::RenderTexture::getViewport
			// Access:    public 
			// Returns:   VkViewport
			// Qualifier: const
			//************************************
			VkViewport getViewport() const { return VkViewport{ 0.0f, 0.0f, static_cast<float>(m_extent.width), static_cast<float>(m_extent.height), 0.0f, 1.0f }; }
			
			//************************************
			// Method:    getViewport
			// FullName:  GFXEngine::Graphics::RenderTexture::getViewport
			// Access:    public 
			// Returns:   VkRect2D
			// Qualifier: const
			//************************************
			VkRect2D getScissor() const { return VkRect2D{ {0, 0}, m_extent }; }
			
			//************************************
			// Method:    getSize
			// FullName:  GFXEngine::Graphics::RenderTexture::getSize
			// Access:    public 
			// Returns:   glm::vec2
			// Qualifier: const
			//************************************
			glm::vec2 getSize() const { return glm::vec2(static_cast<float>(m_extent.width), static_cast<float>(m_extent.height)); }
			
			//************************************
			// Method:    getIntSize
			// FullName:  GFXEngine::Graphics::RenderTexture::getIntSize
			// Access:    public 
			// Returns:   glm::ivec2
			// Qualifier: const
			//************************************
			glm::ivec2 getIntSize() const { return glm::ivec2(m_extent.width, m_extent.height); }
		public:
			//************************************
			// Method:    create
			// FullName:  GFXEngine::Graphics::RenderTexture::create
			// Access:    virtual public 
			// Returns:   void
			// Qualifier:
			// Parameter: Renderer & renderer
			// Parameter: VkExtent2D extend
			// Parameter: const LibGFX::RenderPass & renderpass
			//************************************
			virtual void create(Renderer& renderer, VkExtent2D extend, const LibGFX::RenderPass& renderpass) override;
			
			//************************************
			// Method:    createDescriptorSet
			// FullName:  GFXEngine::Graphics::RenderTexture::createDescriptorSet
			// Access:    public 
			// Returns:   void
			// Qualifier:
			// Parameter: Renderer & renderer
			// Parameter: uint32_t binding
			// Parameter: VkDescriptorSetLayout layout
			//************************************
			void createDescriptorSet(Renderer& renderer, uint32_t binding, VkDescriptorSetLayout layout) override;
			
			//************************************
			// Method:    updateDescriptorSet
			// FullName:  GFXEngine::Graphics::RenderTexture::updateDescriptorSet
			// Access:    public 
			// Returns:   void
			// Qualifier:
			// Parameter: Renderer & renderer
			// Parameter: uint32_t binding
			// Parameter: VkDescriptorSetLayout layout
			//************************************
			void updateDescriptorSet(Renderer& renderer, uint32_t binding, VkDescriptorSetLayout layout) override;
			
			//************************************
			// Method:    draw
			// FullName:  GFXEngine::Graphics::RenderTexture::draw
			// Access:    public 
			// Returns:   void
			// Qualifier:
			// Parameter: Renderer & renderer
			// Parameter: RenderPipeline & pipeline
			// Parameter: uint32_t imageIndex
			//************************************
			void draw(Renderer& renderer, RenderPipeline& pipeline, uint32_t imageIndex) override;
			
			//************************************
			// Method:    resize
			// FullName:  GFXEngine::Graphics::RenderTexture::resize
			// Access:    virtual public 
			// Returns:   void
			// Qualifier:
			// Parameter: Renderer & renderer
			// Parameter: VkExtent2D newExtent
			// Parameter: const LibGFX::RenderPass & renderpass
			//************************************
			virtual void resize(Renderer& renderer, VkExtent2D newExtent, const LibGFX::RenderPass& renderpass) override;
			
			//************************************
			// Method:    destroy
			// FullName:  GFXEngine::Graphics::RenderTexture::destroy
			// Access:    virtual public 
			// Returns:   void
			// Qualifier:
			// Parameter: Renderer & renderer
			//************************************
			virtual void destroy(Renderer& renderer) override;
		};
	}
}
