#pragma once
#include "Renderer.h"
#include "Camera.h"
#include "Scene.h"

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
			virtual void init(Scene& scene, Graphics::Renderer& renderer) = 0;
			virtual void update(Scene& scene, float deltaTime) = 0;
			virtual void render(Scene& scene, Graphics::Renderer& renderer, Graphics::Camera& camera, uint32_t imageIndex) = 0;
			virtual void destroy(Scene& scene, Graphics::Renderer& renderer) = 0;

			Entity* getEntity() const { return m_entity; }
		};
	}
}