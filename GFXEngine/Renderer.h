#pragma once
#include "VkContext.h"
#include "LibGFX.h"
#include "SwapchainInfo.h"
#include "DefaultRenderPass.h"
#include <GLFW/glfw3.h>
#include <memory>

class Renderer
{
public:
	Renderer();
	~Renderer();
	void Init(GLFWwindow* window);
	void DrawFrame();
private:
	std::unique_ptr<LibGFX::VkContext> m_context;
	SwapchainInfo m_swapchainInfo;
	VkFormat m_depthFormat;
	LibGFX::DepthBuffer m_depthBuffer;
	std::unique_ptr<LibGFX::Presets::DefaultRenderPass> m_renderPass;
};
