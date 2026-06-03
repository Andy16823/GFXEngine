#pragma once
#include "EditorDialog.h"

namespace GFXEditor {
	class TextInputDialog : public EditorDialog
	{
	private:
		std::string m_label;
		std::string m_inputText;
	public:
		TextInputDialog(const std::string& label) : m_label(label) {}
		virtual ~TextInputDialog() = default;

		virtual EditorDialogResult renderContent() override;

		void setInputText(const std::string& text) { m_inputText = text; }
		const std::string& getInputText() const { return m_inputText; }
		void setLabel(const std::string& label) { m_label = label; }
		const std::string& getLabel() const { return m_label; }
	};
}
