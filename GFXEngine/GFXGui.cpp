#include "GFXGui.h"
#include "DescriptorPoolBuilder.h"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_vulkan.h"
#include <iostream>

using namespace GFXEngine::Core;
using namespace LibGFX;

void GFXEngine::Core::GFXGui::init(GFXEngine::Graphics::Renderer& renderer, GLFWwindow* window)
{
	std::cout << "Initializing ImGui..." << std::endl;
	
	std::cout << "Creating descriptor pool for ImGui..." << std::endl;
	DescriptorPoolBuilder descriptorPoolBuilder;
	descriptorPoolBuilder.addPoolSize(VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, 1000);
	m_descriptorPool = descriptorPoolBuilder.build(renderer.getContext());
	std::cout << "Descriptor pool created: " << m_descriptorPool << std::endl;

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();

	ImGuiIO& io = ImGui::GetIO();
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable; 
	ImGui::StyleColorsDark();

	ImGui_ImplGlfw_InitForVulkan(window, true);

	ImGui_ImplVulkan_InitInfo initInfo = {};
	initInfo.Instance = renderer.getContext().getInstance();
	initInfo.PhysicalDevice = renderer.getContext().getPhysicalDevice();
	initInfo.Device = renderer.getContext().getDevice();
	initInfo.QueueFamily = renderer.getQueueFamilyIndices().graphicsFamily;
	initInfo.Queue = renderer.getContext().getGraphicsQueue();
	initInfo.PipelineCache = VK_NULL_HANDLE;
	initInfo.DescriptorPool = m_descriptorPool;
	initInfo.Allocator = nullptr;
	initInfo.PipelineInfoMain.MSAASamples = VK_SAMPLE_COUNT_1_BIT;
	initInfo.PipelineInfoMain.RenderPass = renderer.getRenderPass().getRenderPass();
	initInfo.PipelineInfoMain.Subpass = 0;
	initInfo.MinImageCount = renderer.getSwapchainInfo().imageCount;
	initInfo.ImageCount = renderer.getSwapchainInfo().imageCount;

	ImGui_ImplVulkan_Init(&initInfo);
}

void GFXGui::dispose(GFXEngine::Graphics::Renderer& renderer)
{
	renderer.getContext().destroyDescriptorSetPool(m_descriptorPool);
	ImGui_ImplVulkan_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
}

void GFXGui::render(GFXEngine::Graphics::Renderer& renderer, uint32_t imageIndex)
{
	auto commandBuffer = renderer.getCommandBuffer(imageIndex);
	ImGui_ImplVulkan_RenderDrawData(ImGui::GetDrawData(), commandBuffer);
}

void GFXGui::buildGui()
{
	ImGui::Begin("Hello, ImGui!");
	ImGui::Text("This is a simple ImGui window.");
	ImGui::End();
	ImGui::Render();
}

void GFXGui::newFrame()
{
	ImGui_ImplVulkan_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
}
