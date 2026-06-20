#include "FileNameWidget.h"
#include "imgui.h"
#include <misc/cpp/imgui_stdlib.h>

void GFXEditor::FileNameWidget::closeModal()
{
	m_isOpen = false;
	m_callback = nullptr;
	m_currentFileName.clear();
	ImGui::CloseCurrentPopup();
}

void GFXEditor::FileNameWidget::show(const std::string& label, FileNameWidgetCallback callback)
{
	m_label = label;
	m_currentFileName.clear();
	m_isOpen = true;
	m_callback = std::move(callback);
}

void GFXEditor::FileNameWidget::render()
{
	if (m_isOpen) {
		ImGui::OpenPopup(m_label.c_str());
		if (ImGui::BeginPopupModal(m_label.c_str(), nullptr, ImGuiWindowFlags_AlwaysAutoResize))
		{
			ImGui::InputText("File Name", &m_currentFileName);
			if (ImGui::Button("OK"))
			{
				if (m_callback(m_currentFileName))
				{
					closeModal();
				}
			}
			ImGui::SameLine();
			if (ImGui::Button("Cancel"))
			{
				closeModal();
			}
			ImGui::EndPopup();
		}
	}
	else {
		if (m_callback) 
		{
			m_callback = nullptr;
		}
		if (!m_currentFileName.empty()) 
		{
			m_currentFileName.clear();
		}
	}
}
