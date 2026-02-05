#pragma once
#include "LibGFX.h"
#include "RenderPass.h"
#include <array>

namespace GFX {
	namespace Graphics {
		class OffscreenRenderPass : public LibGFX::RenderPass
		{
		public:
			OffscreenRenderPass() = default;
			VkRenderPass getRenderPass() const override;
			std::span<const VkClearValue> getClearValues() const override;
			bool create(VkDevice device, VkFormat swapchainImageFormat, VkFormat depthFormat) override;
			void destroy(VkDevice device) override;
		private:
			VkRenderPass m_renderPass;
			std::array<VkClearValue, 2> m_clearValues;
		};
	}
}
