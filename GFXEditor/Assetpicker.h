#ifndef ASSETPICKER_H
#define ASSETPICKER_H

#include "EditorPlugin.h"
#include "Asset.h"
#include <functional>
#include <optional>

namespace GFXEditor {
namespace Plugins {

using AssetPickerCallback = std::function<bool(class AssetPicker&, GFXEngine::Asset*)>;

class AssetPicker : public EditorPlugin
{
private:
    bool m_visible = false;
    std::optional<AssetPickerCallback> m_callback;
    GFXEngine::Asset* m_selectedAsset = nullptr;

public:
    AssetPicker();
    void show(AssetPickerCallback callback);
    void hide();


    // EditorPlugin interface
public:
    void onRegister(WorldEditor &editor);
    void init(WorldEditor &editor, GFXEngine::Core::UIContext &context, GFXEngine::Graphics::Renderer &renderer);
    void update(WorldEditor &editor, GFXEngine::Core::UIContext &context, GFXEngine::InputManager &input, float deltaTime);
    void beforeRender(WorldEditor &editor, GFXEngine::Core::UIContext &context, GFXEngine::Graphics::Renderer &renderer, uint32_t imageIndex);
    void render(WorldEditor &editor, GFXEngine::Core::UIContext &context, GFXEngine::Graphics::Renderer &renderer, uint32_t imageIndex);
    void afterRender(WorldEditor &editor, GFXEngine::Core::UIContext &context, GFXEngine::Graphics::Renderer &renderer, uint32_t imageIndex);
    void handleInput(WorldEditor &editor, GLFWwindow *window, int key, int scancode, int action, int mods);
    void handleMouseInput(WorldEditor &editor, GLFWwindow *window, int button, int action, int mods);
    void handleMouseMove(WorldEditor &editor, GLFWwindow *window, double xpos, double ypos);
    void dispose(WorldEditor &editor, GFXEngine::Core::UIContext &context, GFXEngine::Graphics::Renderer &renderer);
};

} // namespace Plugins
} // namespace GFXEditor

#endif // ASSETPICKER_H
