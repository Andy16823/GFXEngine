#pragma once
#include "EditorPlugin.h"
#include "Material.h"
#include <optional>

namespace GFXEditor {
	namespace Plugins {

		using MaterialDialogCallback = std::function<void(class MaterialDialog&, GFXEngine::Graphics::Material*)>;

		class MaterialDialog : public EditorPlugin
		{
		private:
			GFXEngine::Graphics::Material* m_material = nullptr;
			bool m_visible = false;
			std::optional<MaterialDialogCallback> m_callback;

		public:
			MaterialDialog() = default;

		public:
			void show(GFXEngine::Graphics::Material* material, MaterialDialogCallback callback = nullptr);
			void hide() { m_visible = false; m_material = nullptr; m_callback.reset(); }
			bool isEnabled() const override;
			void onRegister(WorldEditor& editor) override;
			void init(GFXEditor::WorldEditor& editor, GFXEngine::Core::UIContext& context, GFXEngine::Graphics::Renderer& renderer) override;
			void update(GFXEditor::WorldEditor& editor, GFXEngine::Core::UIContext& context, GFXEngine::InputManager& input, float deltaTime) override;
			void beforeRender(GFXEditor::WorldEditor& editor, GFXEngine::Core::UIContext& context, GFXEngine::Graphics::Renderer& renderer, uint32_t imageIndex) override;
			void render(GFXEditor::WorldEditor& editor, GFXEngine::Core::UIContext& context, GFXEngine::Graphics::Renderer& renderer, uint32_t imageIndex) override;
			void afterRender(GFXEditor::WorldEditor& editor, GFXEngine::Core::UIContext& context, GFXEngine::Graphics::Renderer& renderer, uint32_t imageIndex) override;
			void handleInput(GFXEditor::WorldEditor& editor, GLFWwindow* window, int key, int scancode, int action, int mods) override;
			void handleMouseInput(GFXEditor::WorldEditor& editor, GLFWwindow* window, int button, int action, int mods) override;
			void handleMouseMove(GFXEditor::WorldEditor& editor, GLFWwindow* window, double xpos, double ypos) override;
			void dispose(GFXEditor::WorldEditor& editor, GFXEngine::Core::UIContext& context, GFXEngine::Graphics::Renderer& renderer) override;
		};
	}
}