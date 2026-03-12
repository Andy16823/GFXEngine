#include "Game.h"

void GFXEngine::Core::Game::start(uint32_t width, uint32_t height, const std::string& title /*= "My Game"*/, bool validationLayers /*= true*/)
{
	m_windowSize = { static_cast<float>(width), static_cast<float>(height) };

	// Create window and renderer
	m_window = LibGFX::GFX::createWindow(width, height, title.c_str());
	m_renderer = std::make_unique<Graphics::Renderer>();
	m_renderer->setValidationEnabled(validationLayers);
	m_renderer->init(m_window);

	// Call user-defined initialization
	this->onInit(*m_renderer);

	// Main loop
	m_renderer->createSyncObjects();
	while (!glfwWindowShouldClose(m_window))
	{
		// Poll for window events and acquire next image from the swapchain
		glfwPollEvents();
		auto imageIndex = m_renderer->nextImage();

		// Call user-defined update
		this->onUpdate(*m_renderer, imageIndex, 0.01f);

		// Start recording commands for the current frame
		m_renderer->beginFrame(imageIndex);
		this->onRender(*m_renderer, imageIndex);

		// End recording and submit the command buffer, then present the frame
		m_renderer->endFrame(imageIndex);
		m_renderer->submitFrame(imageIndex);
		m_renderer->presentFrame(imageIndex);

		// Advance to the next frame
		m_renderer->advanceFrame();
	}
	m_renderer->waitIdle();

	// Call user-defined cleanup
	this->onDestroy(*m_renderer);
	m_renderer->dispose();
}
