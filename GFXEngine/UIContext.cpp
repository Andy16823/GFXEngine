#include "UIContext.h"
#include "DescriptorPoolBuilder.h"
#include <iostream>
#include "glm/gtc/type_ptr.hpp"
#include "imguizmo.h"

using namespace GFXEngine::Core;
using namespace LibGFX;

void GFXEngine::Core::UIContext::init(GFXEngine::Graphics::Renderer& renderer, GLFWwindow* window)
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

bool UIContext::gizmoIsUsing()
{
	return ImGuizmo::IsUsing();
}

bool UIContext::gizmoIsOver()
{
	return ImGuizmo::IsOver();
}

bool UIContext::transformGizmo(const glm::mat4& view, const glm::mat4& projection, glm::mat4& transform, const glm::vec4& rect, GuizmoOperation operation)
{
	ImGuizmo::SetOrthographic(false);
	ImGuizmo::BeginFrame();
	ImGuizmo::SetDrawlist(ImGui::GetWindowDrawList());
	ImGuizmo::SetRect(rect.x, rect.y, rect.z, rect.w);

	glm::mat4 adjustedProjection = projection;
	adjustedProjection[1][1] *= -1.0f; // Y-Flip für Vulkan

	ImGuizmo::OPERATION guizmoOperation;
	switch (operation)
	{
	case GFXEngine::Core::GuizmoOperation::Translate:
		guizmoOperation = ImGuizmo::TRANSLATE;
		break;
	case GFXEngine::Core::GuizmoOperation::Rotate:
		guizmoOperation = ImGuizmo::ROTATE;
		break;
	case GFXEngine::Core::GuizmoOperation::Scale:
		guizmoOperation = ImGuizmo::SCALE;
		break;
	default:
		guizmoOperation = ImGuizmo::TRANSLATE;
		break;
	}

	ImGuizmo::Manipulate(
		glm::value_ptr(view),
		glm::value_ptr(adjustedProjection),
		guizmoOperation,
		ImGuizmo::WORLD,
		glm::value_ptr(transform)
	);

	return ImGuizmo::IsUsing();
}

void UIContext::freeTextureDescriptorSet(GFXEngine::Graphics::Renderer& renderer, VkDescriptorSet descriptorSet)
{
	vkFreeDescriptorSets(renderer.getContext().getDevice(), m_descriptorPool, 1, &descriptorSet);
}

VkDescriptorSet UIContext::createTextureDescriptorSet(GFXEngine::Graphics::Renderer& renderer, const GFXEngine::Graphics::RenderTexture& renderTexture)
{
	VkDescriptorSet descriptorSet = ImGui_ImplVulkan_AddTexture(
		renderer.getTextureSampler(),
		renderTexture.getColorImageView(),
		VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL
	);
	return descriptorSet;
}

void UIContext::beginnFullscreen(const char* title, ImGuiWindowFlags flags /*= ImGuiWindowFlags_None*/)
{
	ImGuiIO& io = ImGui::GetIO();
	ImGui::SetNextWindowPos(ImVec2(0.0f, 0.0f));
	ImGui::SetNextWindowSize(io.DisplaySize);

	ImGuiWindowFlags windowFlags = ImGuiWindowFlags_NoTitleBar | 
		ImGuiWindowFlags_NoCollapse |
		ImGuiWindowFlags_NoResize |
		ImGuiWindowFlags_NoMove |
		ImGuiWindowFlags_NoBringToFrontOnFocus |
		ImGuiWindowFlags_NoNavFocus;

	windowFlags |= flags;

	ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
	ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));

	ImGui::Begin(title, nullptr, windowFlags);
	ImGui::PopStyleVar(3);
}

void UIContext::createButton(const char* label, const std::function<void()>& onClick)
{
	if (ImGui::Button(label))
	{
		onClick();
	}
}

void UIContext::createImage(VkDescriptorSet descriptorSet, const glm::vec2& size)
{
	ImGui::Image(reinterpret_cast<ImTextureID>(descriptorSet), ImVec2(size.x, size.y));
}

void UIContext::dispose(GFXEngine::Graphics::Renderer& renderer)
{
	ImGui_ImplVulkan_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
	renderer.getContext().destroyDescriptorSetPool(m_descriptorPool);
}

void UIContext::render(GFXEngine::Graphics::Renderer& renderer, uint32_t imageIndex)
{
	ImGui::Render();
	auto commandBuffer = renderer.getCommandBuffer(imageIndex);
	ImGui_ImplVulkan_RenderDrawData(ImGui::GetDrawData(), commandBuffer);
}

void UIContext::newFrame()
{
	ImGui_ImplVulkan_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
}
