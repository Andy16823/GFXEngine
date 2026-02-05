#pragma once
#include "VkContext.h"
#include "LibGFX.h"
#include "SwapchainInfo.h"
#include "DefaultRenderPass.h"
#include "OffscreenRenderPass.h"
#include <GLFW/glfw3.h>
#include <memory>

namespace GFX {
	namespace Graphics {
		class Renderer
		{
		private:
			std::unique_ptr<LibGFX::VkContext> m_context;
			SwapchainInfo m_swapchainInfo;
			VkFormat m_depthFormat;
			LibGFX::DepthBuffer m_depthBuffer;
			std::unique_ptr<LibGFX::Presets::DefaultRenderPass> m_renderPass;
			std::unique_ptr<OffscreenRenderPass> m_offscreenRenderPass;

		public:
			Renderer() = default;
			~Renderer() = default;
			void init(GLFWwindow* window);
			void drawFrame();
			void dispose();
		};
	}
}
