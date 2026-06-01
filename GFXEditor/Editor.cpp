#include "Editor.h"
#include "PresentPipeline.h"
#include "EngineDefinitions.h"

using namespace GFXEditor;
using namespace GFXEngine;
using namespace GFXEngine::Core;
using namespace GFXEngine::Graphics;

void GFXEditor::Editor::onInit(Graphics::Renderer& renderer)
{
	auto size = this->getWindowSize();
	uint32_t width = size.x;
	uint32_t height = size.y;

	m_camera = std::make_unique<Camera3D>(glm::vec3(0.0f, 35.0f, 0.0f), static_cast<float>(width) / static_cast<float>(height), 0.1f, 1000.0f);
	m_camera->getTransform().rotateWorld(-35.0f, 45.0f, 0.0f);
	m_camera->createDescriptorSets(renderer, renderer.getUniformBufferLayout());
	for (uint32_t i = 0; i < renderer.getSwapchainImageCount(); i++)
	{
		m_camera->updateCameraBuffers(renderer, i);
	}

	m_renderTexture = std::make_unique<RenderTexture>();
	m_renderTexture->create(renderer, { width, height }, renderer.getOffscreenRenderPass());
	m_renderTexture->createDescriptorSet(renderer, 0, renderer.getSamplerLayout());

	m_scene = std::make_unique<Scene3D>();
	m_scene->init(renderer);
}

void GFXEditor::Editor::onStart(Graphics::Renderer & renderer)
{}

void GFXEditor::Editor::onUpdate(Graphics::Renderer & renderer, uint32_t imageIndex, float deltaTime)
{}

void GFXEditor::Editor::beforeRender(Graphics::Renderer & renderer, uint32_t imageIndex)
{}

void GFXEditor::Editor::onRender(Graphics::Renderer & renderer, uint32_t imageIndex)
{
	// Offscreen render pass
	renderer.beginRenderPass(renderer.getOffscreenRenderPass(), m_renderTexture->getFramebuffer(), imageIndex);
	m_scene->render(renderer, *m_camera, imageIndex);
	renderer.endRenderPass(imageIndex);

	// Present render pass
	auto presentPipeline = renderer.getPipeline<GFXEngine::Graphics::PresentPipeline>(Defintions::PipelineType::PRESENT_PIPELINE);
	renderer.beginRenderPass(renderer.getRenderPass(), imageIndex);
	renderer.usePipeline(*presentPipeline, imageIndex);
	m_renderTexture->draw(renderer, *presentPipeline, imageIndex);
	renderer.endRenderPass(imageIndex);

}

void GFXEditor::Editor::afterRender(Graphics::Renderer & renderer, uint32_t imageIndex)
{}

void GFXEditor::Editor::onDestroy(Graphics::Renderer & renderer)
{
	m_camera->destroyDescriptorSets(renderer);
	m_renderTexture->destroy(renderer);
	m_scene->destroy(renderer);
}

void GFXEditor::Editor::onInput(int key, int mods, int action)
{}

void GFXEditor::Editor::onMouseInput(int button, int mods, int action)
{}

void GFXEditor::Editor::onMouseMove(double xpos, double ypos)
{}

void GFXEditor::Editor::onScroll(double xoffset, double yoffset)
{}

void GFXEditor::Editor::onSwapchainRecreate(Graphics::Renderer & renderer)
{}

void GFXEditor::Editor::afterSwapchainRecreate(Graphics::Renderer & renderer, VkViewport viewport, VkRect2D scissor)
{
	m_renderTexture->resize(renderer, { static_cast<uint32_t>(viewport.width), static_cast<uint32_t>(viewport.height) }, renderer.getOffscreenRenderPass());
	m_renderTexture->updateDescriptorSet(renderer, 0, renderer.getSamplerLayout());
}
