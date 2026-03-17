#include "Game.h"
#include <thread>

void GFXEngine::Core::Game::start(uint32_t width, uint32_t height, const std::string& shadersDirectory, const std::string& title /*= "My Game"*/, bool validationLayers /*= true*/)
{
	m_windowSize = { static_cast<int>(width), static_cast<int>(height) };

	// Create window and renderer
	m_window = LibGFX::GFX::createWindow(width, height, title.c_str());
	glfwSetWindowUserPointer(m_window, this);

	// Input callback
	glfwSetKeyCallback(m_window, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
		Game* game = reinterpret_cast<Game*>(glfwGetWindowUserPointer(window));
		if (game) {
			game->onInput(key, mods, action);
		}
	});

	m_renderer = std::make_unique<Graphics::Renderer>();
	m_renderer->setValidationEnabled(validationLayers);
	m_renderer->init(m_window, shadersDirectory);

	// Call user-defined initialization
	this->onInit(*m_renderer);

	// Call user-defined start
	this->onStart(*m_renderer);

	// Set up timing for frame updates
	m_lastFrameTime = static_cast<float>(glfwGetTime());

	// Main loop
	m_renderer->createSyncObjects();
	while (!glfwWindowShouldClose(m_window))
	{
		// Poll for window events and acquire next image from the swapchain
		glfwPollEvents();

		// Calculate delta time for the current frame
		float currentTime = static_cast<float>(glfwGetTime());
		m_deltaTime = currentTime - m_lastFrameTime;
		m_lastFrameTime = currentTime;

		// Cap the frame rate if target FPS is set
		if (m_targetFPS > 0.0f) {
			float frameTime = 1.0f / m_targetFPS;
			if (m_deltaTime < frameTime) {
				std::this_thread::sleep_for(std::chrono::duration<float>(frameTime - m_deltaTime));
				currentTime = static_cast<float>(glfwGetTime());
				m_deltaTime = currentTime - m_lastFrameTime;
				m_lastFrameTime = currentTime;
			}
		}

		auto imageIndex = m_renderer->nextImage();

		// Call user-defined update
		this->onUpdate(*m_renderer, imageIndex, m_deltaTime);

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

glm::vec2 GFXEngine::Core::Game::getCursorPos() const
{
	double x, y;
	glfwGetCursorPos(m_window, &x, &y);
	return { static_cast<float>(x), static_cast<float>(y) };
}
