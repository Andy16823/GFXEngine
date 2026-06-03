#pragma once
#include <functional>
#include <string>

namespace GFXEditor {

	class EditorDialog;
	using EditorDialogCallback = std::function<void(EditorDialog&)>;

	/// <summary>
	/// Dialog result enum to indicate the result of a dialog submission, such as whether the user clicked OK or Cancel.
	/// </summary>
	enum class EditorDialogResult
	{
		None,
		OK,
		Cancel
	};

	/// <summary>
	/// EditorDialog is an abstract base class for creating modal dialogs in the editor. 
	/// It manages the dialog's open/close state, title, and callback function that will be called when the dialog is submitted.
	/// </summary>
	class EditorDialog
	{
	private:
		std::string m_title;
		bool m_isOpen = false;
		EditorDialogCallback m_callback = nullptr;

	public:
		EditorDialog() = default;
		virtual ~EditorDialog() = default;

		/// <summary>
		/// Renders the dialog using ImGui. 
		/// This function should be called every frame in the editor's render loop.
		/// </summary>
		void renderDialog();

		/// <summary>
		/// Renders the content of the dialog. 
		/// This function should be implemented by derived classes to define the dialog's UI.
		/// </summary>
		/// <returns>The result of the dialog submission.</returns>
		virtual EditorDialogResult renderContent() = 0;

		/// <summary>
		/// Shows the dialog with the specified title and callback function.
		/// </summary>
		/// <param name="title"></param>
		/// <param name="callback"></param>
		void showDialog(const std::string& title, EditorDialogCallback callback);

		/// <summary>
		/// Closes the dialog and resets its state. 
		/// This should be called when the dialog is submitted or cancelled.
		/// </summary>
		void close();

		/// <summary>
		/// Returns whether the dialog is currently open.
		/// </summary>
		/// <returns>True if the dialog is open, false otherwise.</returns>
		bool isOpen() const { return m_isOpen; }
	};
}