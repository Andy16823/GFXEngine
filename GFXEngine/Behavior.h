#pragma once
#include "Renderer.h"
#include "Camera.h"

namespace GFXEngine {
	namespace Core {

		/// <summary>
		/// Abstract base class for behaviors that can be attached to entities.
		/// </summary>
		class Behavior {
		protected:
			class Entity* m_entity;

		public:
			virtual ~Behavior() = default;
			void setEntity(class Entity* entity) { m_entity = entity; }
			virtual void init(Graphics::Renderer& renderer) = 0;
			virtual void update(float deltaTime) = 0;
			virtual void render(Graphics::Renderer& renderer, Graphics::Camera& camera, uint32_t imageIndex) = 0;
			virtual void destroy(Graphics::Renderer& renderer) = 0;

			Entity* getEntity() const { return m_entity; }
		};
	}
}