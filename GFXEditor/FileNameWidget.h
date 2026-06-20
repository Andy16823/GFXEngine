#pragma once
#include "UIContext.h";
#include <functional>

namespace GFXEditor {

	using FileNameWidgetCallback = std::function<bool(const std::string&)>;

	class FileNameWidget
	{
	private:
		bool m_isOpen = false;
		std::string m_label;
		std::string m_currentFileName;
		FileNameWidgetCallback m_callback;

	private:
		//************************************
		// Method:    closeModal
		// FullName:  GFXEditor::FileNameWidget::closeModal
		// Access:    private 
		// Returns:   void
		// Qualifier:
		//************************************
		void closeModal();

	public:
		//************************************
		// Method:    FileNameWidget
		// FullName:  GFXEditor::FileNameWidget::FileNameWidget
		// Access:    public 
		// Returns:   
		// Qualifier:
		//************************************
		FileNameWidget() = default;
		
		//************************************
		// Method:    show
		// FullName:  GFXEditor::FileNameWidget::show
		// Access:    public 
		// Returns:   void
		// Qualifier:
		// Parameter: const std::string & label
		// Parameter: FileNameWidgetCallback callback
		//************************************
		void show(const std::string& label, FileNameWidgetCallback callback);
		
		//************************************
		// Method:    render
		// FullName:  GFXEditor::FileNameWidget::render
		// Access:    public 
		// Returns:   void
		// Qualifier:
		//************************************
		void render();
	};
}
