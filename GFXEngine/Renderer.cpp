#include "Renderer.h"
#include <stdexcept>

void Renderer::Init(GLFWwindow* window)
{
	m_context = LibGFX::GFX::createContext(window);
	m_context->initialize(LibGFX::VkContext::defaultAppInfo());

	m_swapchainInfo = m_context->createSwapChain(VK_PRESENT_MODE_MAILBOX_KHR);
	m_depthFormat = m_context->findSuitableDepthFormat();
	m_depthBuffer = m_context->createDepthBuffer(m_swapchainInfo.extent, m_depthFormat);

	m_renderPass = std::make_unique<LibGFX::Presets::DefaultRenderPass>();
	if (!m_renderPass->create(m_context->getDevice(), m_swapchainInfo.surfaceFormat.format, m_depthBuffer.format)) {
		throw std::runtime_error("Failed to create render pass");
	}
}
