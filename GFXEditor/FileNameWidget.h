#pragma once
#include "UIContext.h";
#include <functional>

namespace GFXEditor {

	using FileNameWidgetCallback = std::function<bool(const std::string&)>;

	class FileNameWidget
	{
	private:
		FileNameWidgetCallback m_callback;
		std::string m_currentFileName;
		std::string m_label;
	public:
		FileNameWidget(const std::string& label, FileNameWidgetCallback callback) : m_label(label), m_callback(callback) {}
		void render();
	};
}
