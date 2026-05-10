#include "GFXGui.h"
#include "DescriptorPoolBuilder.h"
#include "imgui_internal.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_vulkan.h"
#include <iostream>
#include "glm/gtc/type_ptr.hpp"

using namespace GFXEngine::Core;
using namespace LibGFX;

void GFXEngine::Core::GFXGui::init(GFXEngine::Graphics::Renderer& renderer, GLFWwindow* window)
{
	std::cout << "Initializing ImGui..." << std::endl;
	
	std::cout << "Creating descriptor pool for ImGui..." << std::endl;
	DescriptorPoolBuilder descriptorPoolBuilder;
	descriptorPoolBuilder.addPoolSize(VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, 1000);
	descriptorPoolBuilder.addPoolSize(VK_DESCRIPTOR_TYPE_SAMPLER, 1000);
	descriptorPoolBuilder.addPoolSize(VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE, 1000);
	descriptorPoolBuilder.setMaxSets(1000);
	descriptorPoolBuilder.setFlags(VK_DESCRIPTOR_POOL_CREATE_FREE_DESCRIPTOR_SET_BIT);
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

glm::vec2 GFXGui::getMousePos() const
{
	auto pos = ImGui::GetMousePos();
	return glm::vec2(pos.x, pos.y);
}

glm::vec2 GFXGui::getCursorPos() const
{
	auto pos = ImGui::GetCursorPos();
	return glm::vec2(pos.x, pos.y);
}

glm::vec2 GFXGui::getCursorScreenPos() const
{
	auto pos = ImGui::GetCursorScreenPos();
	return glm::vec2(pos.x, pos.y);
}

void GFXGui::freeTextureDescriptorSet(GFXEngine::Graphics::Renderer& renderer, VkDescriptorSet descriptorSet)
{
	vkFreeDescriptorSets(renderer.getContext().getDevice(), m_descriptorPool, 1, &descriptorSet);
}

void GFXGui::setWindowSize(const glm::vec2& size)
{
	ImGui::SetWindowSize(ImVec2(size.x, size.y));
}

void GFXGui::setWindowPosition(const glm::vec2& position)
{
	ImGui::SetWindowPos(ImVec2(position.x, position.y));
}

void GFXGui::createDockingSpace(const char* id)
{
	ImGuiID dockspaceID = ImGui::GetID(id);
	ImGui::DockSpace(dockspaceID, ImVec2(0.0f, 0.0f), ImGuiDockNodeFlags_PassthruCentralNode);
}

void GFXGui::createDockingSpace(uint32_t id)
{
	ImGui::DockSpace(id, ImVec2(0.0f, 0.0f), ImGuiDockNodeFlags_PassthruCentralNode);
}

void GFXGui::dockbuilderRemoveNode(uint32_t id)
{
	ImGui::DockBuilderRemoveNode(id);
}

void GFXGui::dockbuilderAddNode(uint32_t nodeID)
{
	ImGui::DockBuilderAddNode(nodeID, ImGuiDockNodeFlags_DockSpace);
}

void GFXGui::dockbuilderSetNodeSize(uint32_t nodeID, const glm::vec2& size)
{
	ImGui::DockBuilderSetNodeSize(nodeID, ImVec2(size.x, size.y));
}

uint32_t GFXGui::dockbuilderSplitNode(uint32_t nodeID, DockingNodeSlot splitDir, float splitRatio, uint32_t* outIDAtDir /*= nullptr*/, uint32_t* outIDAtOppositeDir /*= nullptr*/)
{
	return ImGui::DockBuilderSplitNode(nodeID, static_cast<ImGuiDir>(splitDir), splitRatio, outIDAtDir, outIDAtOppositeDir);
}

void GFXGui::dockbuilderDockWindow(const char* windowLabel, uint32_t nodeID)
{
	ImGui::DockBuilderDockWindow(windowLabel, nodeID);
}

void GFXGui::dockbuilderFinish(uint32_t nodeID)
{
	ImGui::DockBuilderFinish(nodeID);
}

uint32_t GFXGui::getID(const char* label) const
{
	return ImGui::GetID(label);
}

void GFXGui::createTextAreaInput(const char* label, char* buffer, size_t bufferSize)
{
	ImGui::InputTextMultiline(label, buffer, bufferSize);
}

void GFXGui::createTreePop()
{
	ImGui::TreePop();
}

void GFXGui::createSameLine()
{
	ImGui::SameLine();
}

bool GFXGui::createTreeNode(const char* label)
{
	return ImGui::TreeNode(label);
}

void GFXGui::createVectorInput(const char* label, glm::vec2* value)
{
	ImGui::InputFloat2(label, glm::value_ptr(*value));
}

void GFXGui::createColorInput(const char* label, glm::vec4* color)
{
	ImGui::ColorEdit4(label, glm::value_ptr(*color));
}

void GFXGui::createColorInput(const char* label, glm::vec3* color)
{
	ImGui::ColorEdit3(label, glm::value_ptr(*color));
}

void GFXGui::createQuatInput(const char* label, glm::quat* value)
{
	ImGui::InputFloat4(label, glm::value_ptr(*value));
}

glm::vec2 GFXGui::getWindowPosition() const
{
	ImVec2 pos = ImGui::GetWindowPos();
	return glm::vec2(pos.x, pos.y);
}

glm::vec2 GFXGui::getClientAreaSize() const
{
	ImVec2 size = ImGui::GetContentRegionAvail();
	return glm::vec2(size.x, size.y);
}

void GFXGui::createVectorInput(const char* label, glm::vec4* value)
{
	ImGui::InputFloat4(label, glm::value_ptr(*value));
}

void GFXGui::createVectorInput(const char* label, glm::vec3* value)
{
	ImGui::InputFloat3(label, glm::value_ptr(*value));
}

bool GFXGui::createCollapsingHeader(const char* label)
{
	return ImGui::CollapsingHeader(label);
}

void GFXGui::createTextInput(const char* label, char* buffer, size_t bufferSize)
{
	ImGui::InputText(label, buffer, bufferSize);
}

void GFXGui::createFloatInput(const char* label, float* value)
{
	ImGui::InputFloat(label, value);
}

void GFXGui::createNumberInput(const char* label, int* value)
{
	ImGui::InputInt(label, value);
}

void GFXGui::createCheckbox(const char* label, bool* value)
{
	ImGui::Checkbox(label, value);
}

void GFXGui::createFloatSlider(const char* label, float* value, float min, float max)
{
	ImGui::SliderFloat(label, value, min, max);
}

VkDescriptorSet GFXGui::createTextureDescriptorSet(GFXEngine::Graphics::Renderer& renderer, const GFXEngine::Graphics::RenderTexture& renderTexture)
{
	VkDescriptorSet descriptorSet = ImGui_ImplVulkan_AddTexture(
		renderer.getTextureSampler(),
		renderTexture.getColorImageView(),
		VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL
	);
	return descriptorSet;
}

void GFXGui::beginUI(const char* title, bool docking)
{
	ImGuiWindowFlags windowFlags = ImGuiWindowFlags_None;
	if (docking)
	{
		windowFlags |= ImGuiWindowFlags_NoDocking;
	}
	ImGui::Begin(title, nullptr, windowFlags);
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

void GFXGui::createImage(VkDescriptorSet descriptorSet, const glm::vec2& size)
{
	ImGui::Image(reinterpret_cast<ImTextureID>(descriptorSet), ImVec2(size.x, size.y));
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
