#pragma once
#include "Renderer.h"
#include "Camera.h"
#include "ISerializable.h"
#include <variant>
#include "PropertyInfo.h"

namespace GFXEngine {
	namespace Core {
		class Scene;

		/// <summary>
		/// Abstract base class for behaviors that can be attached to entities.
		/// </summary>
		class Behavior : public GFXEngine::ISerializable {
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
			virtual nlohmann::json serialize() const override = 0;
			virtual void deserialize(const nlohmann::json& data, GFXEngine::SerializationContext& context) override = 0;

			Entity* getEntity() const { return m_entity; }
		};
	}
}