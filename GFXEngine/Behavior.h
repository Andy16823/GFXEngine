#pragma once
#include "Renderer.h"
#include "Camera.h"
#include "Scene.h"

namespace GFXEngine {
	namespace Core {

		/// <summary>
		/// PropertyType enum represents the type of a property that can be used in a behavior.
		/// </summary>
		enum class PropertyType {
			Float,
			Vector2,
			Vector3,
			Vector4,
			Color,
			Texture,
			Material,
			Mesh,
			Animation,
			Entity
		};

		/// <summary>
		/// PropertyInfo struct represents a property of a behavior.
		/// </summary>
		struct PropertyInfo {
			std::string name;
			PropertyType type;
			void* data;
		};

		/// <summary>
		/// Abstract base class for behaviors that can be attached to entities.
		/// </summary>
		class Behavior {
		protected:
			class Entity* m_entity;

		public:

			Behavior() = default;
			virtual ~Behavior() = default;
			Behavior(const Behavior&) = delete;
			Behavior& operator=(const Behavior&) = delete;
			Behavior(Behavior&&) = delete;
			Behavior& operator=(Behavior&&) = delete;

			void setEntity(class Entity* entity) { m_entity = entity; }
			virtual void init(Scene& scene, Graphics::Renderer& renderer) = 0;
			virtual void update(Scene& scene, float deltaTime) = 0;
			virtual void render(Scene& scene, Graphics::Renderer& renderer, Graphics::Camera& camera, uint32_t imageIndex) = 0;
			virtual void destroy(Scene& scene, Graphics::Renderer& renderer) = 0;

			virtual std::string getName() const = 0;
			virtual std::vector<PropertyInfo> getProperties() const = 0;

			Entity* getEntity() const { return m_entity; }
		};
	}
}