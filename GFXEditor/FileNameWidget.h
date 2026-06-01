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

	public:
		FileNameWidget() = default;
		void show(const std::string& label, FileNameWidgetCallback callback);
		void render();
	};
}
