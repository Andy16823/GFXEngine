#pragma once
#include "GLFW/glfw3.h"
#include "Glm/glm.hpp"
#include <functional>
#include <unordered_map>

namespace GFXEngine {
	class InputManager
	{
	private:
		using InputCallback = std::function<void(int key, int mods, int action)>;
		using MouseButtonCallback = std::function<void(int button, int mods, int action)>;
		using MouseMoveCallback = std::function<void(double xpos, double ypos)>;
		using ScrollCallback = std::function<void(double xoffset, double yoffset)>;

	private:
		GLFWwindow* m_window;
		std::unordered_map<uint32_t, InputCallback> m_inputCallbacks;
		std::unordered_map<uint32_t, MouseButtonCallback> m_mouseButtonCallbacks;
		std::unordered_map<uint32_t, MouseMoveCallback> m_mouseMoveCallbacks;
		std::unordered_map<uint32_t, ScrollCallback> m_scrollCallbacks;
		uint32_t m_nextCallbackId = 0;

		//************************************
		// Method:    generateCallbackId
		// FullName:  GFXEngine::InputManager::generateCallbackId
		// Access:    private 
		// Returns:   uint32_t
		// Qualifier:
		//************************************
		uint32_t generateCallbackId() {	return m_nextCallbackId++; }
	public:
		
		//************************************
		// Method:    InputManager
		// FullName:  GFXEngine::InputManager::InputManager
		// Access:    public 
		// Returns:   
		// Qualifier:
		//************************************
		InputManager() = default;
		
		//************************************
		// Method:    InputManager
		// FullName:  GFXEngine::InputManager::InputManager
		// Access:    public 
		// Returns:   
		// Qualifier: : m_window(window)
		// Parameter: GLFWwindow * window
		//************************************
		InputManager(GLFWwindow* window) : m_window(window) {}
		
		//************************************
		// Method:    ~InputManager
		// FullName:  GFXEngine::InputManager::~InputManager
		// Access:    public 
		// Returns:   
		// Qualifier:
		//************************************
		~InputManager() = default;

		//************************************
		// Method:    init
		// FullName:  GFXEngine::InputManager::init
		// Access:    public 
		// Returns:   void
		// Qualifier:
		// Parameter: GLFWwindow * window
		//************************************
		void init(GLFWwindow* window) { m_window = window; }

		//************************************
		// Method:    isKeyPressed
		// FullName:  GFXEngine::InputManager::isKeyPressed
		// Access:    public 
		// Returns:   bool
		// Qualifier: const
		// Parameter: int key
		//************************************
		bool isKeyPressed(int key) const;
		
		//************************************
		// Method:    isKeyReleased
		// FullName:  GFXEngine::InputManager::isKeyReleased
		// Access:    public 
		// Returns:   bool
		// Qualifier: const
		// Parameter: int key
		//************************************
		bool isKeyReleased(int key) const;
		
		//************************************
		// Method:    isMouseButtonPressed
		// FullName:  GFXEngine::InputManager::isMouseButtonPressed
		// Access:    public 
		// Returns:   bool
		// Qualifier: const
		// Parameter: int button
		//************************************
		bool isMouseButtonPressed(int button) const;
		
		//************************************
		// Method:    isMouseButtonReleased
		// FullName:  GFXEngine::InputManager::isMouseButtonReleased
		// Access:    public 
		// Returns:   bool
		// Qualifier: const
		// Parameter: int button
		//************************************
		bool isMouseButtonReleased(int button) const;
		
		//************************************
		// Method:    getCursorPosition
		// FullName:  GFXEngine::InputManager::getCursorPosition
		// Access:    public 
		// Returns:   glm::vec2
		// Qualifier: const
		//************************************
		glm::vec2 getCursorPosition() const;

		//************************************
		// Method:    registerInputCallback
		// FullName:  GFXEngine::InputManager::registerInputCallback
		// Access:    public 
		// Returns:   uint32_t
		// Qualifier:
		// Parameter: const InputCallback & callback
		//************************************
		uint32_t registerInputCallback(const InputCallback& callback);
		
		//************************************
		// Method:    registerMouseButtonCallback
		// FullName:  GFXEngine::InputManager::registerMouseButtonCallback
		// Access:    public 
		// Returns:   uint32_t
		// Qualifier:
		// Parameter: const MouseButtonCallback & callback
		//************************************
		uint32_t registerMouseButtonCallback(const MouseButtonCallback& callback);
		
		//************************************
		// Method:    registerMouseMoveCallback
		// FullName:  GFXEngine::InputManager::registerMouseMoveCallback
		// Access:    public 
		// Returns:   uint32_t
		// Qualifier:
		// Parameter: const MouseMoveCallback & callback
		//************************************
		uint32_t registerMouseMoveCallback(const MouseMoveCallback& callback);
		
		//************************************
		// Method:    registerScrollCallback
		// FullName:  GFXEngine::InputManager::registerScrollCallback
		// Access:    public 
		// Returns:   uint32_t
		// Qualifier:
		// Parameter: const ScrollCallback & callback
		//************************************
		uint32_t registerScrollCallback(const ScrollCallback& callback);

		//************************************
		// Method:    unregisterInputCallback
		// FullName:  GFXEngine::InputManager::unregisterInputCallback
		// Access:    public 
		// Returns:   void
		// Qualifier:
		// Parameter: uint32_t callbackId
		//************************************
		void unregisterInputCallback(uint32_t callbackId);
		
		//************************************
		// Method:    unregisterMouseButtonCallback
		// FullName:  GFXEngine::InputManager::unregisterMouseButtonCallback
		// Access:    public 
		// Returns:   void
		// Qualifier:
		// Parameter: uint32_t callbackId
		//************************************
		void unregisterMouseButtonCallback(uint32_t callbackId);
		
		//************************************
		// Method:    unregisterMouseMoveCallback
		// FullName:  GFXEngine::InputManager::unregisterMouseMoveCallback
		// Access:    public 
		// Returns:   void
		// Qualifier:
		// Parameter: uint32_t callbackId
		//************************************
		void unregisterMouseMoveCallback(uint32_t callbackId);
		
		//************************************
		// Method:    unregisterScrollCallback
		// FullName:  GFXEngine::InputManager::unregisterScrollCallback
		// Access:    public 
		// Returns:   void
		// Qualifier:
		// Parameter: uint32_t callbackId
		//************************************
		void unregisterScrollCallback(uint32_t callbackId);

		//************************************
		// Method:    handleInput
		// FullName:  GFXEngine::InputManager::handleInput
		// Access:    public 
		// Returns:   void
		// Qualifier:
		// Parameter: int key
		// Parameter: int mods
		// Parameter: int action
		//************************************
		void handleInput(int key, int mods, int action);
		
		//************************************
		// Method:    handleMouseButton
		// FullName:  GFXEngine::InputManager::handleMouseButton
		// Access:    public 
		// Returns:   void
		// Qualifier:
		// Parameter: int button
		// Parameter: int mods
		// Parameter: int action
		//************************************
		void handleMouseButton(int button, int mods, int action);
		
		//************************************
		// Method:    handleMouseMove
		// FullName:  GFXEngine::InputManager::handleMouseMove
		// Access:    public 
		// Returns:   void
		// Qualifier:
		// Parameter: double xpos
		// Parameter: double ypos
		//************************************
		void handleMouseMove(double xpos, double ypos);
		
		//************************************
		// Method:    handleScroll
		// FullName:  GFXEngine::InputManager::handleScroll
		// Access:    public 
		// Returns:   void
		// Qualifier:
		// Parameter: double xoffset
		// Parameter: double yoffset
		//************************************
		void handleScroll(double xoffset, double yoffset);

		//************************************
		// Method:    clearCallbacks
		// FullName:  GFXEngine::InputManager::clearCallbacks
		// Access:    public 
		// Returns:   void
		// Qualifier:
		//************************************
		void clearCallbacks();
	};
}