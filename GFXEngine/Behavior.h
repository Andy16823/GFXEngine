#pragma once
#include "Renderer.h"
#include "Camera.h"
#include "ISerializable.h"
#include <variant>
#include "PropertyInfo.h"
#include "Utils.h"

namespace GFXEngine {
	namespace Core {
		class Scene;

		/// <summary>
		/// Abstract base class for behaviors that can be attached to entities.
		/// </summary>
		class Behavior : public GFXEngine::ISerializable {
		protected:
			class Entity* m_entity = nullptr;
			std::string m_uuid;

		public:

			Behavior() : m_uuid(Utils::generateUUID()) {}
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
			virtual std::vector<PropertyInfo> getProperties() = 0;

			virtual nlohmann::json serialize() const override {
				nlohmann::json data;
				data["uuid"] = m_uuid;
				return data;
			}

			virtual void deserialize(const nlohmann::json& data, GFXEngine::SerializationContext& context) override {
				if (!data.is_null()) {
					m_uuid = data.value("uuid", Utils::generateUUID());
				}
			}

			Entity* getEntity() const { return m_entity; }
			const std::string& getUUID() const { return m_uuid; }
		};
	}
}