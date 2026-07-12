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
		//************************************
		// Method:    ~EditorPlugin
		// FullName:  GFXEditor::EditorPlugin::~EditorPlugin
		// Access:    virtual public 
		// Returns:   
		// Qualifier:
		//************************************
		virtual ~EditorPlugin() = default;
		
		//************************************
		// Method:    isEnabled
		// FullName:  GFXEditor::EditorPlugin::isEnabled
		// Access:    virtual public 
		// Returns:   bool
		// Qualifier: const
		//************************************
		virtual bool isEnabled() const { return true; }
		
		//************************************
		// Method:    onRegister
		// FullName:  GFXEditor::EditorPlugin::onRegister
		// Access:    virtual public 
		// Returns:   void
		// Qualifier:
		// Parameter: WorldEditor & editor
		//************************************
		virtual void onRegister(WorldEditor& editor) = 0;
		
		//************************************
		// Method:    init
		// FullName:  GFXEditor::EditorPlugin::init
		// Access:    virtual public 
		// Returns:   void
		// Qualifier:
		// Parameter: GFXEditor::WorldEditor & editor
		// Parameter: GFXEngine::Core::UIContext & context
		// Parameter: GFXEngine::Graphics::Renderer & renderer
		//************************************
		virtual void init(GFXEditor::WorldEditor& editor, GFXEngine::Core::UIContext& context, GFXEngine::Graphics::Renderer& renderer) = 0;
		
		//************************************
		// Method:    update
		// FullName:  GFXEditor::EditorPlugin::update
		// Access:    virtual public 
		// Returns:   void
		// Qualifier:
		// Parameter: GFXEditor::WorldEditor & editor
		// Parameter: GFXEngine::Core::UIContext & context
		// Parameter: GFXEngine::InputManager & input
		// Parameter: float deltaTime
		//************************************
		virtual void update(GFXEditor::WorldEditor& editor, GFXEngine::Core::UIContext& context, GFXEngine::InputManager& input, float deltaTime) = 0;
		
		//************************************
		// Method:    beforeRender
		// FullName:  GFXEditor::EditorPlugin::beforeRender
		// Access:    virtual public 
		// Returns:   void
		// Qualifier:
		// Parameter: GFXEditor::WorldEditor & editor
		// Parameter: GFXEngine::Core::UIContext & context
		// Parameter: GFXEngine::Graphics::Renderer & renderer
		// Parameter: uint32_t imageIndex
		//************************************
		virtual void beforeRender(GFXEditor::WorldEditor& editor, GFXEngine::Core::UIContext& context, GFXEngine::Graphics::Renderer& renderer, uint32_t imageIndex) = 0;
	
		//************************************
		// Method:    render
		// FullName:  GFXEditor::EditorPlugin::render
		// Access:    virtual public 
		// Returns:   void
		// Qualifier:
		// Parameter: GFXEditor::WorldEditor & editor
		// Parameter: GFXEngine::Core::UIContext & context
		// Parameter: GFXEngine::Graphics::Renderer & renderer
		// Parameter: uint32_t imageIndex
		//************************************
		virtual void render(GFXEditor::WorldEditor& editor, GFXEngine::Core::UIContext& context, GFXEngine::Graphics::Renderer& renderer, uint32_t imageIndex) = 0;
		
		//************************************
		// Method:    afterRender
		// FullName:  GFXEditor::EditorPlugin::afterRender
		// Access:    virtual public 
		// Returns:   void
		// Qualifier:
		// Parameter: GFXEditor::WorldEditor & editor
		// Parameter: GFXEngine::Core::UIContext & context
		// Parameter: GFXEngine::Graphics::Renderer & renderer
		// Parameter: uint32_t imageIndex
		//************************************
		virtual void afterRender(GFXEditor::WorldEditor& editor, GFXEngine::Core::UIContext& context, GFXEngine::Graphics::Renderer& renderer, uint32_t imageIndex) = 0;
		
		//************************************
		// Method:    handleInput
		// FullName:  GFXEditor::EditorPlugin::handleInput
		// Access:    virtual public 
		// Returns:   void
		// Qualifier:
		// Parameter: GFXEditor::WorldEditor & editor
		// Parameter: GLFWwindow * window
		// Parameter: int key
		// Parameter: int mods
		// Parameter: int action
		//************************************
		virtual void handleInput(GFXEditor::WorldEditor& editor, GLFWwindow* window, int key, int mods, int action) = 0;
		
		//************************************
		// Method:    handleMouseInput
		// FullName:  GFXEditor::EditorPlugin::handleMouseInput
		// Access:    virtual public 
		// Returns:   void
		// Qualifier:
		// Parameter: GFXEditor::WorldEditor & editor
		// Parameter: GLFWwindow * window
		// Parameter: int button
		// Parameter: int mods
		// Parameter: int action
		//************************************
		virtual void handleMouseInput(GFXEditor::WorldEditor& editor, GLFWwindow* window, int button, int mods, int action) = 0;
		
		//************************************
		// Method:    handleMouseMove
		// FullName:  GFXEditor::EditorPlugin::handleMouseMove
		// Access:    virtual public 
		// Returns:   void
		// Qualifier:
		// Parameter: GFXEditor::WorldEditor & editor
		// Parameter: GLFWwindow * window
		// Parameter: double xpos
		// Parameter: double ypos
		//************************************
		virtual void handleMouseMove(GFXEditor::WorldEditor& editor, GLFWwindow* window, double xpos, double ypos) = 0;
		
		//************************************
		// Method:    dispose
		// FullName:  GFXEditor::EditorPlugin::dispose
		// Access:    virtual public 
		// Returns:   void
		// Qualifier:
		// Parameter: GFXEditor::WorldEditor & editor
		// Parameter: GFXEngine::Core::UIContext & context
		// Parameter: GFXEngine::Graphics::Renderer & renderer
		//************************************
		virtual void dispose(GFXEditor::WorldEditor& editor, GFXEngine::Core::UIContext& context, GFXEngine::Graphics::Renderer& renderer) = 0;
		
		//************************************
		// Method:    dockspace
		// FullName:  GFXEditor::EditorPlugin::dockspace
		// Access:    virtual public 
		// Returns:   void
		// Qualifier:
		// Parameter: GFXEditor::WorldEditor & editor
		// Parameter: GFXEngine::Core::UIContext & context
		//************************************
		virtual void dockspace(GFXEditor::WorldEditor& editor, GFXEngine::Core::UIContext& context) {};
	};
}