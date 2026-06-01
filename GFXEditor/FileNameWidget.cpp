#include "FileNameWidget.h"
#include "imgui.h"
#include <misc/cpp/imgui_stdlib.h>

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
		if (ImGui::BeginPopupModal(m_label.c_str(), &m_isOpen, ImGuiWindowFlags_AlwaysAutoResize))
		{
			ImGui::InputText("File Name", &m_currentFileName);
			if (ImGui::Button("OK"))
			{
				if (m_callback(m_currentFileName))
				{
					m_callback = nullptr;
					ImGui::CloseCurrentPopup();
				}
			}
			ImGui::SameLine();
			if (ImGui::Button("Cancel"))
			{
				m_callback = nullptr;
				ImGui::CloseCurrentPopup();
			}
			ImGui::EndPopup();
		}
	}
}
