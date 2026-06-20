#pragma once
#include "EditorDialog.h"

namespace GFXEditor {
	class TextInputDialog : public EditorDialog
	{
	private:
		std::string m_label;
		std::string m_inputText;
	public:
		//************************************
		// Method:    TextInputDialog
		// FullName:  GFXEditor::TextInputDialog::TextInputDialog
		// Access:    public 
		// Returns:   
		// Qualifier: : m_label(label)
		// Parameter: const std::string & label
		//************************************
		TextInputDialog(const std::string& label) : m_label(label) {}
		
		//************************************
		// Method:    ~TextInputDialog
		// FullName:  GFXEditor::TextInputDialog::~TextInputDialog
		// Access:    virtual public 
		// Returns:   
		// Qualifier:
		//************************************
		virtual ~TextInputDialog() = default;

		//************************************
		// Method:    renderContent
		// FullName:  GFXEditor::TextInputDialog::renderContent
		// Access:    virtual public 
		// Returns:   GFXEditor::EditorDialogResult
		// Qualifier:
		//************************************
		virtual EditorDialogResult renderContent() override;
		
		//************************************
		// Method:    clearResults
		// FullName:  GFXEditor::TextInputDialog::clearResults
		// Access:    virtual public 
		// Returns:   void
		// Qualifier:
		//************************************
		virtual void clearResults() override { m_inputText.clear(); }

		//************************************
		// Method:    setInputText
		// FullName:  GFXEditor::TextInputDialog::setInputText
		// Access:    public 
		// Returns:   void
		// Qualifier:
		// Parameter: const std::string & text
		//************************************
		void setInputText(const std::string& text) { m_inputText = text; }
		
		//************************************
		// Method:    getInputText
		// FullName:  GFXEditor::TextInputDialog::getInputText
		// Access:    public 
		// Returns:   const std::string&
		// Qualifier: const
		//************************************
		const std::string& getInputText() const { return m_inputText; }
		
		//************************************
		// Method:    setLabel
		// FullName:  GFXEditor::TextInputDialog::setLabel
		// Access:    public 
		// Returns:   void
		// Qualifier:
		// Parameter: const std::string & label
		//************************************
		void setLabel(const std::string& label) { m_label = label; }
		
		//************************************
		// Method:    getLabel
		// FullName:  GFXEditor::TextInputDialog::getLabel
		// Access:    public 
		// Returns:   const std::string&
		// Qualifier: const
		//************************************
		const std::string& getLabel() const { return m_label; }
	};
}
