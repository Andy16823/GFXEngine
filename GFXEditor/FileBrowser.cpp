#include "FileBrowser.h"
#include <imgui.h>
#include <misc/cpp/imgui_stdlib.h>

namespace GFXEditor {
namespace Plugins {

FileBrowser::FileBrowser() {

}

void FileBrowser::hide()
{
    m_callback.reset();
    m_visible = false;
}

void FileBrowser::show(FileBrowserCallback callback, FileBrowserOperation operation /*= FileBrowserOperation::FILE_BROWSER_OP_SAVE*/)
{
    m_callback = std::move(callback);
    m_visible = true;
    m_fileBrowserOp = operation;
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
    if(m_visible) {
        ImGui::Begin("File Dialog");

        std::vector<std::filesystem::path> dirs;
        std::vector<std::filesystem::path> files;
        for (const auto& entry : std::filesystem::directory_iterator(m_currentPath)) {
            if (entry.is_directory() && this->hasFilter(FileBrowserFilter::FILE_BROWSER_FILTER_DIR))
            {
                dirs.push_back(entry.path());

            }
            else if (entry.is_regular_file() && this->hasFilter(FileBrowserFilter::FILE_BROWSER_FILTER_FILES)) {
                files.push_back(entry.path());
            }
        }

        ImGui::BeginListBox("Files");
        for(const auto path : dirs) {
            if (ImGui::Selectable(("/" + path.filename().string()).c_str())) {
                m_currentPath = path;
            }
        }

        for(const auto path : files) {
            if (ImGui::Selectable(path.filename().string().c_str())) {
                std::string extension = path.extension().string();
                m_filename = path.filename();
            }
        }
        ImGui::EndListBox();

        ImGui::InputText("Filename", &m_filename);

        switch(m_fileBrowserOp) {
            case FileBrowserOperation::FILE_BROWSER_OP_SAVE:
                if(ImGui::Button("Save")) {
                    if (m_callback && (*m_callback)(*this)) {
                        this->hide();
                    }
                }
                break;
            case FileBrowserOperation::FILE_BROWSER_OP_LOAD:
                if(ImGui::Button("Open")) {
                    if (m_callback && (*m_callback)(*this)) {
                        this->hide();
                    }
                }
                break;
            default:
                break;
        }

        ImGui::SameLine();

        if(ImGui::Button("Cancel")) {
            this->hide();
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
