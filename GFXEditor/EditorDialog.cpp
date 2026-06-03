#include "EditorDialog.h"
#include "imgui.h"

void GFXEditor::EditorDialog::showDialog(const std::string& title, EditorDialogCallback callback)
{
	m_title = title;
	m_callback = callback;
	m_isOpen = true;
	ImGui::OpenPopup(m_title.c_str());
}

void GFXEditor::EditorDialog::close()
{
	m_title.clear();
	m_callback = nullptr;
	m_isOpen = false;
}

void GFXEditor::EditorDialog::renderDialog()
{
	if (m_isOpen) {
		if (ImGui::BeginPopupModal(m_title.c_str(), nullptr, ImGuiWindowFlags_AlwaysAutoResize))
		{
			switch (this->renderContent())
			{
			case EditorDialogResult::OK:
				if (m_callback) {
					m_callback(*this);
				}
				this->close();
				break;
			case EditorDialogResult::Cancel:
				this->close();
				break;
			default:
				break;
			}
			ImGui::EndPopup();
		}
	}
	else {
		m_callback = nullptr;
		m_title.clear();
	}
}