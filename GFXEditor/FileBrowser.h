#ifndef FILEBROWSER_H
#define FILEBROWSER_H

#include "EditorPlugin.h"
#include <functional>
#include <filesystem>
#include <optional>

namespace GFXEditor {
namespace Plugins {

using FileBrowserCallback = std::function<bool(class FileBrowser&)>;

class FileBrowser : public EditorPlugin
{
private:
    bool m_isOpen = false;
    std::optional<FileBrowserCallback> m_callback;
    std::filesystem::path m_currentPath;
    std::string m_filename;

public:
    FileBrowser();

public:
    std::string getFileName() const { return m_filename; }
    void setFilename(const std::string& value) { m_filename = value; }
    void setPath(const std::filesystem::path& path) { m_currentPath = path; }
    std::filesystem::path getPath() const { return m_currentPath; }

public:
    void show(FileBrowserCallback callback);

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

#endif // FILEBROWSER_H
