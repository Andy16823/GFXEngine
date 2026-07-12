#pragma once
#include <functional>
#include <string>

namespace GFXEditor {

	class EditorDialog;
	using EditorDialogCallback = std::function<void(EditorDialog&)>;

	enum class EditorDialogResult
	{
		None,
		OK,
		Cancel
	};

	class EditorDialog
	{
	private:
		std::string m_title;
		bool m_isOpen = false;
		EditorDialogCallback m_callback = nullptr;

	public:
		EditorDialog() = default;
		virtual ~EditorDialog() = default;

		//************************************
		// Method:    renderDialog
		// FullName:  GFXEditor::EditorDialog::renderDialog
		// Access:    public 
		// Returns:   void
		// Qualifier:
		//************************************
		void renderDialog();

		//************************************
		// Method:    renderContent
		// FullName:  GFXEditor::EditorDialog::renderContent
		// Access:    virtual public 
		// Returns:   GFXEditor::EditorDialogResult
		// Qualifier:
		//************************************
		virtual EditorDialogResult renderContent() = 0;

		//************************************
		// Method:    clearResults
		// FullName:  GFXEditor::EditorDialog::clearResults
		// Access:    virtual public 
		// Returns:   void
		// Qualifier:
		//************************************
		virtual void clearResults() = 0;

		//************************************
		// Method:    showDialog
		// FullName:  GFXEditor::EditorDialog::showDialog
		// Access:    public 
		// Returns:   void
		// Qualifier:
		// Parameter: const std::string & title
		// Parameter: EditorDialogCallback callback
		//************************************
		void showDialog(const std::string& title, EditorDialogCallback callback);

		//************************************
		// Method:    close
		// FullName:  GFXEditor::EditorDialog::close
		// Access:    public 
		// Returns:   void
		// Qualifier:
		//************************************
		void close();

		//************************************
		// Method:    isOpen
		// FullName:  GFXEditor::EditorDialog::isOpen
		// Access:    public 
		// Returns:   bool
		// Qualifier: const
		//************************************
		bool isOpen() const { return m_isOpen; }
	};
}