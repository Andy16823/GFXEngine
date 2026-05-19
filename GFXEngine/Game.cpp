#include "Game.h"
#include <thread>
#include "RuntimeContext.h"
#include "Model.h"
#include "InstancedModel.h"
#include "Sprite.h"
#include "InputManager.h"

void GFXEngine::Core::Game::start(uint32_t width, uint32_t height, const std::string& shadersDirectory, const std::string& title /*= "My Game"*/, bool fullscreen /*= false*/, bool validationLayers /*= true*/)
{
	// Register core entity types in the entity factory
	this->entityFactory->registerEntity<GFXEngine::Core::Model>();
	this->entityFactory->registerEntity<GFXEngine::Core::InstancedModel>();
	//this->entityFactory->registerEntity<GFXEngine::Core::Sprite>(); TODO: Add a default constructor to Sprite that initializes the material and mesh references, then register it here.

	// Create the window and initialize the renderer
	m_windowSize = { static_cast<int>(width), static_cast<int>(height) };
	m_window = LibGFX::GFX::createWindow(width, height, title.c_str(), fullscreen, m_resizable);
	glfwSetWindowUserPointer(m_window, this);
	this->inputManager->init(m_window);

	// Create the static runtime context and register core services
	GFXEngine::RuntimeContext::get().setWindow(m_window);
	GFXEngine::RuntimeContext::get().setServiceManager(serviceManager.get());
	GFXEngine::RuntimeContext::get().setAssetManager(assetManager.get());
	GFXEngine::RuntimeContext::get().setBehaviorRegistry(behaviorRegistry.get());
	GFXEngine::RuntimeContext::get().setEntityFactory(entityFactory.get());
	GFXEngine::RuntimeContext::get().setInputManager(inputManager.get());

	// Input callback
	glfwSetKeyCallback(m_window, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
		Game* game = reinterpret_cast<Game*>(glfwGetWindowUserPointer(window));
		if (game) {
			game->onInput(key, mods, action);
			game->inputManager->handleInput(key, mods, action);
		}
	});

	glfwSetMouseButtonCallback(m_window, [](GLFWwindow* window, int button, int action, int mods) {
		Game* game = reinterpret_cast<Game*>(glfwGetWindowUserPointer(window));
		if (game) 
		{ 
			game->onMouseInput(button, mods, action);
			game->inputManager->handleMouseButton(button, mods, action);
		}
	});

	glfwSetCursorPosCallback(m_window, [](GLFWwindow* window, double xpos, double ypos) {
		Game* game = reinterpret_cast<Game*>(glfwGetWindowUserPointer(window));
		if (game) 
		{
			game->onMouseMove(xpos, ypos);
			game->inputManager->handleMouseMove(xpos, ypos);
		}
	});

	glfwSetScrollCallback(m_window, [](GLFWwindow* window, double xoffset, double yoffset) {
		Game* game = reinterpret_cast<Game*>(glfwGetWindowUserPointer(window));
		if (game) 
		{
			game->onScroll(xoffset, yoffset);
			game->inputManager->handleScroll(xoffset, yoffset);
		}
	});

	m_renderer = std::make_unique<Graphics::Renderer>();
	m_renderer->setValidationEnabled(validationLayers);
	m_renderer->init(m_window, shadersDirectory);

	// Register swapchain recreation callbacks
	m_renderer->registerSwapchainCleanupCallback([this](Graphics::Renderer& renderer) {
		this->onSwapchainRecreate(renderer);
		});

	m_renderer->registerSwapchainRecreationCallback([this](Graphics::Renderer& renderer, VkViewport viewport, VkRect2D scissor) {
		int width, height;
		glfwGetWindowSize(m_window, &width, &height);
		m_windowSize = { width, height };
		this->afterSwapchainRecreate(renderer, viewport, scissor);
		});

	// Load assets and register behaviors before initialization
	this->registerBehaviors(*behaviorRegistry);
	this->loadAssets(*assetManager);
	
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

		// Call user-defined before render
		this->beforeRender(*m_renderer, imageIndex);

		// Start recording commands for the current frame
		m_renderer->beginFrame(imageIndex);
		this->onRender(*m_renderer, imageIndex);

		// End recording and submit the command buffer, then present the frame
		m_renderer->endFrame(imageIndex);
		m_renderer->submitFrame(imageIndex);
		m_renderer->presentFrame(imageIndex);

		// Call user-defined after render
		this->afterRender(*m_renderer, imageIndex);

		// Advance to the next frame
		m_renderer->advanceFrame();
	}
	m_renderer->waitIdle();

	// Call user-defined cleanup
	this->onDestroy(*m_renderer);
	m_renderer->dispose();
	
	// Clean up assets and behaviors
	assetManager->clear();
	behaviorRegistry->clear();
	entityFactory->clear();
	inputManager->clearCallbacks();
}

glm::vec2 GFXEngine::Core::Game::getCursorPos() const
{
	double x, y;
	glfwGetCursorPos(m_window, &x, &y);
	return { static_cast<float>(x), static_cast<float>(y) };
}
