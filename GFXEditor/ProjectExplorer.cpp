#include "ProjectExplorer.h"
#include "WorldEditor.h"
#include "Utils.h"
#include "Asset.h"

#include <iostream>

void GFXEditor::Plugins::ProjectExplorer::onRegister(WorldEditor& editor)
{
	std::cout << "Registered Project Explorer Plugin with initial path: " << m_currentExplorerPath << std::endl;
}

void GFXEditor::Plugins::ProjectExplorer::init(GFXEditor::WorldEditor& editor, GFXEngine::Core::UIContext& context, GFXEngine::Graphics::Renderer& renderer)
{

}

void GFXEditor::Plugins::ProjectExplorer::update(GFXEditor::WorldEditor& editor, GFXEngine::Core::UIContext& context, GFXEngine::InputManager& input, float deltaTime)
{
	
}

void GFXEditor::Plugins::ProjectExplorer::beforeRender(GFXEditor::WorldEditor& editor, GFXEngine::Core::UIContext& context, GFXEngine::Graphics::Renderer& renderer, uint32_t imageIndex)
{
	
}

void GFXEditor::Plugins::ProjectExplorer::render(GFXEditor::WorldEditor& editor, GFXEngine::Core::UIContext& context, GFXEngine::Graphics::Renderer& renderer, uint32_t imageIndex)
{
	auto fileDialog = editor.getCreateFileDialog();
	auto assetManager = editor.getAssetManager();

	ImGui::Begin("Project Explorer");

	if (ImGui::BeginPopupContextWindow())
	{
		if (ImGui::MenuItem("Go to Parent Directory", nullptr, false, m_currentExplorerPath.has_parent_path()))
		{
			m_currentExplorerPath = m_currentExplorerPath.parent_path();
		}

		ImGui::Separator();

		if (ImGui::MenuItem("Create Directory"))
		{
			if (!fileDialog->isOpen())
			{
				fileDialog->showDialog("Create New Directory", [&](EditorDialog& dialog) {
					std::string dirName = static_cast<TextInputDialog&>(dialog).getInputText();
					std::filesystem::path newDirPath = m_currentExplorerPath / dirName;
					GFXEngine::Utils::createDirectory(newDirPath.string());
					});
			}
		}

		if (ImGui::MenuItem("Show in Explorer"))
		{
			// TODO: Windows-specific implementation, need to add support for other platforms
			std::string command = "explorer.exe /select,\"" + m_currentExplorerPath.string() + "\"";
			system(command.c_str());
		}

		ImGui::Separator();

		if (ImGui::MenuItem("Create File")) {
			if (!fileDialog->isOpen())
			{
				fileDialog->showDialog("Create New File", [&](EditorDialog& dialog) {
					std::string fileName = static_cast<TextInputDialog&>(dialog).getInputText();
					std::filesystem::path filePath = m_currentExplorerPath / fileName;
					GFXEngine::Utils::createFile(filePath.string());
					});
			}
		}

		if (ImGui::MenuItem("Create Environment"))
		{
			if (!fileDialog->isOpen())
			{
				fileDialog->showDialog("Create New Environment", [&](EditorDialog& dialog) {
					std::string fileName = static_cast<TextInputDialog&>(dialog).getInputText();
					std::filesystem::path filePath = m_currentExplorerPath / (fileName + ".env");
					nlohmann::json environment;
					environment["faces"] = std::vector<std::string>{
						"right.png",
						"left.png",
						"top.png",
						"bottom.png",
						"front.png",
						"back.png"
					};
					GFXEngine::Utils::saveJsonToFile(environment, filePath.string());
					});
			}
		}

		ImGui::Separator();

		if (ImGui::MenuItem("Import Asset"))
		{
			if (!m_selectedFilePath.empty())
			{
				auto asset = assetManager->loadFromFile(m_selectedFilePath);
				if (auto graphicsAsset = asset->as<GFXEngine::GraphicsAsset>()) {
					graphicsAsset->init(renderer);
					std::cout << "Loaded asset: " << asset->getName() << std::endl;
				}
			}
		}

		ImGui::EndPopup();
	}

	// Go to parent directory option
	std::string labelId = GFXEngine::Core::UIContext::createLabelID("...", GFXEngine::Utils::generateUUID());
	if (ImGui::Selectable(labelId.c_str()))
	{
		m_currentExplorerPath = m_currentExplorerPath.parent_path();
	}

	// Entries in the current directory
	for (const auto& entry : std::filesystem::directory_iterator(m_currentExplorerPath)) {
		if (entry.is_directory())
		{
			if (ImGui::Selectable((entry.path().filename().string() + "/").c_str())) {
				m_currentExplorerPath = entry.path();
			}
		}
		else if (entry.is_regular_file()) {
			if (ImGui::Selectable(entry.path().filename().string().c_str())) {
				std::string extension = entry.path().extension().string();
				std::cout << "Selected file: " << entry.path() << std::endl;
				m_selectedFilePath = entry.path();
			}
		}
	}

	ImGui::End();
}

void GFXEditor::Plugins::ProjectExplorer::afterRender(GFXEditor::WorldEditor& editor, GFXEngine::Core::UIContext& context, GFXEngine::Graphics::Renderer& renderer, uint32_t imageIndex)
{
	
}

void GFXEditor::Plugins::ProjectExplorer::handleInput(GFXEditor::WorldEditor& editor, GLFWwindow* window, int key, int mods, int action)
{
	
}

void GFXEditor::Plugins::ProjectExplorer::handleMouseInput(GFXEditor::WorldEditor& editor, GLFWwindow* window, int button, int mods, int action)
{
	
}

void GFXEditor::Plugins::ProjectExplorer::handleMouseMove(GFXEditor::WorldEditor& editor, GLFWwindow* window, double xpos, double ypos)
{
	
}

void GFXEditor::Plugins::ProjectExplorer::dispose(GFXEditor::WorldEditor& editor, GFXEngine::Core::UIContext& context, GFXEngine::Graphics::Renderer& renderer)
{
	
}

void GFXEditor::Plugins::ProjectExplorer::dockspace(GFXEditor::WorldEditor& editor, GFXEngine::Core::UIContext& context)
{
	ImGui::DockBuilderDockWindow("Project Explorer", editor.getBottomDockID());
}
