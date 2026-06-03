#include "TextInputDialog.h"
#include "imgui.h"
#include <misc/cpp/imgui_stdlib.h>

GFXEditor::EditorDialogResult GFXEditor::TextInputDialog::renderContent()
{
	ImGui::Text("%s", m_label.c_str());
	ImGui::InputText("Input", &m_inputText);
	if (ImGui::Button("OK"))
	{
		return EditorDialogResult::OK;
	}
	ImGui::SameLine();
	if (ImGui::Button("Cancel"))
	{
		return EditorDialogResult::Cancel;
	}
	return EditorDialogResult::None;
}