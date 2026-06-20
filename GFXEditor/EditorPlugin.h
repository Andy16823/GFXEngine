#pragma once
#include "UIContext.h"
#include "Renderer.h"
#include "InputManager.h"
#include <unordered_map>

namespace GFXEditor
{
	class WorldEditor;

	/// <summary>
	/// Abstract base class for editor plugins. Plugins can be used to extend the functionality of the editor by implementing custom rendering, input handling, and other features.
	/// </summary>
	class EditorPlugin
	{
	public:
		virtual ~EditorPlugin() = default;
		virtual bool isEnabled() const { return true; }
		virtual void onRegister(WorldEditor& editor) = 0;
		virtual void init(GFXEditor::WorldEditor& editor, GFXEngine::Core::UIContext& context, GFXEngine::Graphics::Renderer& renderer) = 0;
		virtual void update(GFXEditor::WorldEditor& editor, GFXEngine::Core::UIContext& context, GFXEngine::InputManager& input, float deltaTime) = 0;
		virtual void beforeRender(GFXEditor::WorldEditor& editor, GFXEngine::Core::UIContext& context, GFXEngine::Graphics::Renderer& renderer, uint32_t imageIndex) = 0;
		virtual void render(GFXEditor::WorldEditor& editor, GFXEngine::Core::UIContext& context, GFXEngine::Graphics::Renderer& renderer, uint32_t imageIndex) = 0;
		virtual void afterRender(GFXEditor::WorldEditor& editor, GFXEngine::Core::UIContext& context, GFXEngine::Graphics::Renderer& renderer, uint32_t imageIndex) = 0;
		virtual void handleInput(GFXEditor::WorldEditor& editor, GLFWwindow* window, int key, int mods, int action) = 0;
		virtual void handleMouseInput(GFXEditor::WorldEditor& editor, GLFWwindow* window, int button, int mods, int action) = 0;
		virtual void handleMouseMove(GFXEditor::WorldEditor& editor, GLFWwindow* window, double xpos, double ypos) = 0;
		virtual void dispose(GFXEditor::WorldEditor& editor, GFXEngine::Core::UIContext& context, GFXEngine::Graphics::Renderer& renderer) = 0;
		virtual void dockspace(GFXEditor::WorldEditor& editor, GFXEngine::Core::UIContext& context) {};
	};
}