#pragma once
#include "EditorPlugin.h"
#include <filesystem>

namespace GFXEditor {
	namespace Plugins {
		class ProjectExplorer : public EditorPlugin
		{
		private:
			std::filesystem::path m_currentExplorerPath;
			std::filesystem::path m_selectedFilePath;
		
		public:
			//************************************
			// Method:    ProjectExplorer
			// FullName:  GFXEditor::Plugins::ProjectExplorer::ProjectExplorer
			// Access:    public 
			// Returns:   
			// Qualifier: : m_currentExplorerPath(initialPath)
			// Parameter: const std::filesystem::path & initialPath
			//************************************
			ProjectExplorer(const std::filesystem::path& initialPath) : m_currentExplorerPath(initialPath) {}

			//************************************
			// Method:    onRegister
			// FullName:  GFXEditor::Plugins::ProjectExplorer::onRegister
			// Access:    public 
			// Returns:   void
			// Qualifier:
			// Parameter: WorldEditor & editor
			//************************************
			void onRegister(WorldEditor& editor) override;

			//************************************
			// Method:    init
			// FullName:  GFXEditor::Plugins::ProjectExplorer::init
			// Access:    public 
			// Returns:   void
			// Qualifier:
			// Parameter: GFXEditor::WorldEditor & editor
			// Parameter: GFXEngine::Core::UIContext & context
			// Parameter: GFXEngine::Graphics::Renderer & renderer
			//************************************
			void init(GFXEditor::WorldEditor& editor, GFXEngine::Core::UIContext& context, GFXEngine::Graphics::Renderer& renderer) override;
			
			//************************************
			// Method:    update
			// FullName:  GFXEditor::Plugins::ProjectExplorer::update
			// Access:    public 
			// Returns:   void
			// Qualifier:
			// Parameter: GFXEditor::WorldEditor & editor
			// Parameter: GFXEngine::Core::UIContext & context
			// Parameter: GFXEngine::InputManager & input
			// Parameter: float deltaTime
			//************************************
			void update(GFXEditor::WorldEditor& editor, GFXEngine::Core::UIContext& context, GFXEngine::InputManager& input, float deltaTime) override;

			//************************************
			// Method:    beforeRender
			// FullName:  GFXEditor::Plugins::ProjectExplorer::beforeRender
			// Access:    public 
			// Returns:   void
			// Qualifier:
			// Parameter: GFXEditor::WorldEditor & editor
			// Parameter: GFXEngine::Core::UIContext & context
			// Parameter: GFXEngine::Graphics::Renderer & renderer
			// Parameter: uint32_t imageIndex
			//************************************
			void beforeRender(GFXEditor::WorldEditor& editor, GFXEngine::Core::UIContext& context, GFXEngine::Graphics::Renderer& renderer, uint32_t imageIndex) override;
			
			//************************************
			// Method:    render
			// FullName:  GFXEditor::Plugins::ProjectExplorer::render
			// Access:    public 
			// Returns:   void
			// Qualifier:
			// Parameter: GFXEditor::WorldEditor & editor
			// Parameter: GFXEngine::Core::UIContext & context
			// Parameter: GFXEngine::Graphics::Renderer & renderer
			// Parameter: uint32_t imageIndex
			//************************************
			void render(GFXEditor::WorldEditor& editor, GFXEngine::Core::UIContext& context, GFXEngine::Graphics::Renderer& renderer, uint32_t imageIndex) override;
			
			//************************************
			// Method:    afterRender
			// FullName:  GFXEditor::Plugins::ProjectExplorer::afterRender
			// Access:    public 
			// Returns:   void
			// Qualifier:
			// Parameter: GFXEditor::WorldEditor & editor
			// Parameter: GFXEngine::Core::UIContext & context
			// Parameter: GFXEngine::Graphics::Renderer & renderer
			// Parameter: uint32_t imageIndex
			//************************************
			void afterRender(GFXEditor::WorldEditor& editor, GFXEngine::Core::UIContext& context, GFXEngine::Graphics::Renderer& renderer, uint32_t imageIndex) override;
			
			//************************************
			// Method:    handleInput
			// FullName:  GFXEditor::Plugins::ProjectExplorer::handleInput
			// Access:    public 
			// Returns:   void
			// Qualifier:
			// Parameter: GFXEditor::WorldEditor & editor
			// Parameter: GLFWwindow * window
			// Parameter: int key
			// Parameter: int mods
			// Parameter: int action
			//************************************
			void handleInput(GFXEditor::WorldEditor& editor, GLFWwindow* window, int key, int mods, int action) override;
			
			//************************************
			// Method:    handleMouseInput
			// FullName:  GFXEditor::Plugins::ProjectExplorer::handleMouseInput
			// Access:    public 
			// Returns:   void
			// Qualifier:
			// Parameter: GFXEditor::WorldEditor & editor
			// Parameter: GLFWwindow * window
			// Parameter: int button
			// Parameter: int mods
			// Parameter: int action
			//************************************
			void handleMouseInput(GFXEditor::WorldEditor& editor, GLFWwindow* window, int button, int mods, int action) override;
			
			//************************************
			// Method:    handleMouseMove
			// FullName:  GFXEditor::Plugins::ProjectExplorer::handleMouseMove
			// Access:    public 
			// Returns:   void
			// Qualifier:
			// Parameter: GFXEditor::WorldEditor & editor
			// Parameter: GLFWwindow * window
			// Parameter: double xpos
			// Parameter: double ypos
			//************************************
			void handleMouseMove(GFXEditor::WorldEditor& editor, GLFWwindow* window, double xpos, double ypos) override;
			
			//************************************
			// Method:    dispose
			// FullName:  GFXEditor::Plugins::ProjectExplorer::dispose
			// Access:    public 
			// Returns:   void
			// Qualifier:
			// Parameter: GFXEditor::WorldEditor & editor
			// Parameter: GFXEngine::Core::UIContext & context
			// Parameter: GFXEngine::Graphics::Renderer & renderer
			//************************************
			void dispose(GFXEditor::WorldEditor& editor, GFXEngine::Core::UIContext& context, GFXEngine::Graphics::Renderer& renderer) override;
			
			//************************************
			// Method:    dockspace
			// FullName:  GFXEditor::Plugins::ProjectExplorer::dockspace
			// Access:    public 
			// Returns:   void
			// Qualifier:
			// Parameter: GFXEditor::WorldEditor & editor
			// Parameter: GFXEngine::Core::UIContext & context
			//************************************
			void dockspace(GFXEditor::WorldEditor& editor, GFXEngine::Core::UIContext& context) override;
		};
	}
}