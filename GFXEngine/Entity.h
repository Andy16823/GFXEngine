#pragma once
#include "Transform.h"
#include "Renderer.h"
#include "Camera3D.h"

namespace GFXEngine {
	namespace Core {
		class Entity
		{
		private:

		public:
			GFXEngine::Math::Transform transform;

			Entity() = default;
			virtual ~Entity() = default;

			virtual void init(GFXEngine::Graphics::Renderer& renderer) = 0;
			virtual void update(float deltaTime) = 0;
			virtual void render(GFXEngine::Graphics::Renderer& renderer, GFXEngine::Graphics::Camera3D& camera, uint32_t imageIndex) = 0;
			virtual void destroy(GFXEngine::Graphics::Renderer& renderer) = 0;
		};
	}
}
