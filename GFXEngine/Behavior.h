#pragma once
#include "Renderer.h"
#include "Camera.h"

namespace GFXEngine {
	namespace Core {

		// Forward declaration of Entity to avoid circular dependency with Behavior
		class Entity;

		class Behavior {
		protected:
			Entity* m_entity;

		public:
			virtual ~Behavior() = default;
			void setEntity(Entity* entity) { m_entity = entity; }
			virtual void init(Graphics::Renderer& renderer) = 0;
			virtual void update(float deltaTime) = 0;
			virtual void render(Graphics::Renderer& renderer, Graphics::Camera& camera, uint32_t imageIndex) = 0;
			virtual void destroy(Graphics::Renderer& renderer) = 0;
		};
	}
}