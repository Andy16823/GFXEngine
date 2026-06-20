#pragma once
#include "LibGFX.h"
#include "RenderPass.h"
#include <array>
#include "VkContext.h"

namespace GFXEngine {
	namespace Graphics {
		class OffscreenRenderPass : public LibGFX::RenderPass
		{
		private:
			VkRenderPass m_renderPass;
			std::array<VkClearValue, 2> m_clearValues;

		public:
			
			//************************************
			// Method:    OffscreenRenderPass
			// FullName:  GFXEngine::Graphics::OffscreenRenderPass::OffscreenRenderPass
			// Access:    public 
			// Returns:   
			// Qualifier:
			//************************************
			OffscreenRenderPass() = default;
			
			//************************************
			// Method:    getRenderPass
			// FullName:  GFXEngine::Graphics::OffscreenRenderPass::getRenderPass
			// Access:    public 
			// Returns:   VkRenderPass
			// Qualifier: const 
			//************************************
			VkRenderPass getRenderPass() const override;
			
			//************************************
			// Method:    getClearValues
			// FullName:  GFXEngine::Graphics::OffscreenRenderPass::getClearValues
			// Access:    public 
			// Returns:   std::span<const VkClearValue>
			// Qualifier: const 
			//************************************
			std::span<const VkClearValue> getClearValues() const override;
			
			//************************************
			// Method:    create
			// FullName:  GFXEngine::Graphics::OffscreenRenderPass::create
			// Access:    public 
			// Returns:   bool
			// Qualifier:
			// Parameter: LibGFX::VkContext & context
			// Parameter: VkFormat swapchainImageFormat
			// Parameter: VkFormat depthFormat
			//************************************
			bool create(LibGFX::VkContext& context, VkFormat swapchainImageFormat, VkFormat depthFormat) override;
			
			//************************************
			// Method:    destroy
			// FullName:  GFXEngine::Graphics::OffscreenRenderPass::destroy
			// Access:    public 
			// Returns:   void
			// Qualifier:
			// Parameter: LibGFX::VkContext & context
			//************************************
			void destroy(LibGFX::VkContext& context) override;
		};
	}
}
