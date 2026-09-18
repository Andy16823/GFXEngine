#include "FileBrowser.h"
#include <imgui.h>
#include <misc/cpp/imgui_stdlib.h>

namespace GFXEditor {
namespace Plugins {

FileBrowser::FileBrowser() {

}

void FileBrowser::show(FileBrowserCallback callback)
{
    m_callback = std::move(callback);
    m_isOpen = true;
}

void FileBrowser::onRegister(WorldEditor &editor)
{

}

void FileBrowser::init(WorldEditor &editor, GFXEngine::Core::UIContext &context, GFXEngine::Graphics::Renderer &renderer)
{

}

void FileBrowser::update(WorldEditor &editor, GFXEngine::Core::UIContext &context, GFXEngine::InputManager &input, float deltaTime)
{

}

void FileBrowser::beforeRender(WorldEditor &editor, GFXEngine::Core::UIContext &context, GFXEngine::Graphics::Renderer &renderer, uint32_t imageIndex)
{

}

void FileBrowser::render(WorldEditor &editor, GFXEngine::Core::UIContext &context, GFXEngine::Graphics::Renderer &renderer, uint32_t imageIndex)
{
    if(m_isOpen) {
        ImGui::Begin("File Dialog");
        ImGui::InputText("Filename", &m_filename);

        // List Directory and files
        ImGui::BeginListBox("Files");
        for (const auto& entry : std::filesystem::directory_iterator(m_currentPath)) {
            if (entry.is_directory() && this->hasFilter(FileBrowserFilter::FILE_BROWSER_FILTER_DIR))
            {
                if (ImGui::Selectable(("/" + entry.path().filename().string()).c_str())) {
                    m_currentPath = entry.path();
                }
            }
            else if (entry.is_regular_file() && this->hasFilter(FileBrowserFilter::FILE_BROWSER_FILTER_FILES)) {
                if (ImGui::Selectable(entry.path().filename().string().c_str())) {
                    std::string extension = entry.path().extension().string();
                    m_filename = entry.path().filename();
                }
            }
        }
        ImGui::EndListBox();

        if(ImGui::Button("Save")) {
            if (m_callback && (*m_callback)(*this)) {
                m_isOpen = false;
                m_callback.reset();
            }
        }

        if(ImGui::Button("Cancle")) {
            m_callback.reset();
            m_isOpen = false;
        }

        ImGui::End();
    }
}

void FileBrowser::afterRender(WorldEditor &editor, GFXEngine::Core::UIContext &context, GFXEngine::Graphics::Renderer &renderer, uint32_t imageIndex)
{

}

void FileBrowser::handleInput(WorldEditor &editor, GLFWwindow *window, int key, int scancode, int action, int mods)
{

}

void FileBrowser::handleMouseInput(WorldEditor &editor, GLFWwindow *window, int button, int action, int mods)
{

}

void FileBrowser::handleMouseMove(WorldEditor &editor, GLFWwindow *window, double xpos, double ypos)
{

}

void FileBrowser::dispose(WorldEditor &editor, GFXEngine::Core::UIContext &context, GFXEngine::Graphics::Renderer &renderer)
{

}

} // namespace Plugins
} // namespace GFXEditor
