#pragma once
#include <functional>


namespace GFXEditor {

	using PostRenderActionCallback = std::function<void()>;

	struct PostRenderAction {
		PostRenderActionCallback callback;
	};
}