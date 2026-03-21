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
	descriptorPoolBuilder.setMaxSets(1000);
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

ImTextureID GFXGui::createTexture(GFXEngine::Graphics::Renderer& renderer, const GFXEngine::Graphics::RenderTexture& renderTexture)
{
	VkDescriptorSet descriptorSet = ImGui_ImplVulkan_AddTexture(
		renderer.getTextureSampler(),
		renderTexture.getColorImageView(),
		VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL
	);

	return reinterpret_cast<ImTextureID>(descriptorSet);
}

void GFXGui::beginUI(const char* title)
{
	ImGui::Begin(title);
}

void GFXGui::createText(const char* text)
{
	ImGui::Text("%s", text);
}

void GFXGui::createButton(const char* label, const std::function<void()>& onClick)
{
	if (ImGui::Button(label))
	{
		onClick();
	}
}

void GFXGui::createImage(ImTextureID textureId, const ImVec2& size)
{
	ImGui::Image(textureId, size);
}

void GFXGui::endUI()
{
	ImGui::End();
}

void GFXGui::dispose(GFXEngine::Graphics::Renderer& renderer)
{
	ImGui_ImplVulkan_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
	renderer.getContext().destroyDescriptorSetPool(m_descriptorPool);
}

void GFXGui::render(GFXEngine::Graphics::Renderer& renderer, uint32_t imageIndex)
{
	ImGui::Render();
	auto commandBuffer = renderer.getCommandBuffer(imageIndex);
	ImGui_ImplVulkan_RenderDrawData(ImGui::GetDrawData(), commandBuffer);
}

void GFXGui::newFrame()
{
	ImGui_ImplVulkan_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
}
