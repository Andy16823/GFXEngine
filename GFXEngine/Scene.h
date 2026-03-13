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
			virtual void init(GFXEngine::Graphics::Renderer& renderer) = 0;
			virtual void update(GFXEngine::Graphics::Renderer& renderer, GFXEngine::Graphics::Camera& camera, uint32_t imageIndex, float deltaTime) = 0;
			virtual void render(GFXEngine::Graphics::Renderer& renderer, GFXEngine::Graphics::Camera& camera, uint32_t imageIndex) = 0;
			virtual void destroy(GFXEngine::Graphics::Renderer& renderer) = 0;
			virtual void input(int key, int mods, int action) = 0;
		};
	}
}
