#include "FileNameWidget.h"
#include "imgui.h"
#include <misc/cpp/imgui_stdlib.h>

void GFXEditor::FileNameWidget::render()
{
	ImGui::OpenPopup(m_label.c_str());
	if (ImGui::BeginPopupModal(m_label.c_str(), nullptr, ImGuiWindowFlags_AlwaysAutoResize))
	{
		ImGui::InputText("File Name", &m_currentFileName);
		if (ImGui::Button("OK"))
		{
			if (m_callback(m_currentFileName))
			{
				ImGui::CloseCurrentPopup();
			}
		}
		ImGui::SameLine();
		if (ImGui::Button("Cancel"))
		{
			ImGui::CloseCurrentPopup();
		}
		ImGui::EndPopup();
	}
}