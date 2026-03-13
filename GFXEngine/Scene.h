#pragma once
#include "Renderer.h"
#include "Camera.h"

namespace GFXEngine {
	namespace Core {
		class Scene
		{
		public:
			Scene() = default;
			virtual ~Scene() = default;
			virtual void onInit(GFXEngine::Graphics::Renderer& renderer) = 0;
			virtual void onUpdate(GFXEngine::Graphics::Renderer& renderer, GFXEngine::Graphics::Camera& camera, uint32_t imageIndex, float deltaTime) = 0;
			virtual void onRender(GFXEngine::Graphics::Renderer& renderer, GFXEngine::Graphics::Camera& camera, uint32_t imageIndex) = 0;
			virtual void onDestroy(GFXEngine::Graphics::Renderer& renderer) = 0;
			virtual void onInput(int key, int mods, int action) = 0;
		};
	}
}
