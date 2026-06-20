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
			ProjectExplorer(const std::filesystem::path& initialPath) : m_currentExplorerPath(initialPath) {}

			void onRegister(WorldEditor& editor) override;
			void init(GFXEditor::WorldEditor& editor, GFXEngine::Core::UIContext& context, GFXEngine::Graphics::Renderer& renderer) override;
			void update(GFXEditor::WorldEditor& editor, GFXEngine::Core::UIContext& context, GFXEngine::InputManager& input, float deltaTime) override;
			void beforeRender(GFXEditor::WorldEditor& editor, GFXEngine::Core::UIContext& context, GFXEngine::Graphics::Renderer& renderer, uint32_t imageIndex) override;
			void render(GFXEditor::WorldEditor& editor, GFXEngine::Core::UIContext& context, GFXEngine::Graphics::Renderer& renderer, uint32_t imageIndex) override;
			void afterRender(GFXEditor::WorldEditor& editor, GFXEngine::Core::UIContext& context, GFXEngine::Graphics::Renderer& renderer, uint32_t imageIndex) override;
			void handleInput(GFXEditor::WorldEditor& editor, GLFWwindow* window, int key, int mods, int action) override;
			void handleMouseInput(GFXEditor::WorldEditor& editor, GLFWwindow* window, int button, int mods, int action) override;
			void handleMouseMove(GFXEditor::WorldEditor& editor, GLFWwindow* window, double xpos, double ypos) override;
			void dispose(GFXEditor::WorldEditor& editor, GFXEngine::Core::UIContext& context, GFXEngine::Graphics::Renderer& renderer) override;
			void dockspace(GFXEditor::WorldEditor& editor, GFXEngine::Core::UIContext& context) override;
		};
	}
}