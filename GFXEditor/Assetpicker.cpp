#include "Assetpicker.h"
#include <imgui.h>
#include <misc/cpp/imgui_stdlib.h>
#include "WorldEditor.h"

namespace GFXEditor {
namespace Plugins {

AssetPicker::AssetPicker() {}

void AssetPicker::show(AssetPickerCallback callback)
{
    m_callback = std::move(callback);
    m_visible = true;
}

void AssetPicker::hide()
{
    m_callback.reset();
    m_selectedAsset = nullptr;
    m_visible = false;
}

void AssetPicker::onRegister(WorldEditor &editor)
{

}

void AssetPicker::init(WorldEditor &editor, GFXEngine::Core::UIContext &context, GFXEngine::Graphics::Renderer &renderer)
{

}

void AssetPicker::update(WorldEditor &editor, GFXEngine::Core::UIContext &context, GFXEngine::InputManager &input, float deltaTime)
{

}

void AssetPicker::beforeRender(WorldEditor &editor, GFXEngine::Core::UIContext &context, GFXEngine::Graphics::Renderer &renderer, uint32_t imageIndex)
{

}

void AssetPicker::render(WorldEditor &editor, GFXEngine::Core::UIContext &context, GFXEngine::Graphics::Renderer &renderer, uint32_t imageIndex)
{
    if(m_visible) {
        ImGui::Begin("Select Asset");

        GFXEngine::AssetManager *manager = editor.getAssetManager();
        if(ImGui::BeginCombo("Assets", "Please Select")) {
            manager->forEachAssetOfType<GFXEngine::Graphics::StaticMeshModel>([this](GFXEngine::Graphics::StaticMeshModel* model) {
                if(ImGui::Selectable(model->getName().c_str())) {
                    m_selectedAsset = model;
                }
            });

            ImGui::EndCombo();
        }

        if(ImGui::Button("Select")) {
            if(m_callback && (*m_callback)(*this, m_selectedAsset)) {
                this->hide();
            }
            else {
                this->hide();
            }
        }

        ImGui::SameLine();

        if(ImGui::Button("Cancel")) {
            this->hide();
        }

        ImGui::End();
    }
}

void AssetPicker::afterRender(WorldEditor &editor, GFXEngine::Core::UIContext &context, GFXEngine::Graphics::Renderer &renderer, uint32_t imageIndex)
{

}

void AssetPicker::handleInput(WorldEditor &editor, GLFWwindow *window, int key, int scancode, int action, int mods)
{

}

void AssetPicker::handleMouseInput(WorldEditor &editor, GLFWwindow *window, int button, int action, int mods)
{

}

void AssetPicker::handleMouseMove(WorldEditor &editor, GLFWwindow *window, double xpos, double ypos)
{

}

void AssetPicker::dispose(WorldEditor &editor, GFXEngine::Core::UIContext &context, GFXEngine::Graphics::Renderer &renderer)
{

}

} // namespace Plugins
} // namespace GFXEditor
