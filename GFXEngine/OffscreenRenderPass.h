#pragma once
#include "LibGFX.h"
#include "RenderPass.h"
#include <array>
#include "VkContext.h"

namespace GFXEngine {
	namespace Graphics {
		class OffscreenRenderPass : public LibGFX::RenderPass
		{
		public:
			OffscreenRenderPass() = default;
			VkRenderPass getRenderPass() const override;
			std::span<const VkClearValue> getClearValues() const override;
			bool create(LibGFX::VkContext& context, VkFormat swapchainImageFormat, VkFormat depthFormat) override;
			void destroy(LibGFX::VkContext& context) override;
		private:
			VkRenderPass m_renderPass;
			std::array<VkClearValue, 2> m_clearValues;
		};
	}
}
