#pragma once
#include "Renderer.h"
#include "Camera.h"
#include "ISerializable.h"
#include <variant>

namespace GFXEngine {
	namespace Core {
		class Scene;

		/// <summary>
		/// PropertyType enum represents the type of a property that can be used in a behavior.
		/// </summary>
		enum class PropertyType {
			String,
			Int,
			Bool,
			Float,
			Vector2,
			Vector3,
			Vector4,
			Color,
			Entity
		};

		/// <summary>
		/// PropertyHint enum represents additional hints for how a property should be displayed or edited in an editor.
		/// </summary>
		enum class PropertyHint {
			None,
			Enum,
			Color,
			Multiline,
			File,
			Asset,
			Entity
		};

		/// <summary>
		/// EnumMetaData struct represents additional metadata for properties of type Enum, such as the list of options that should be displayed in an editor.
		/// </summary>
		struct EnumMetaData {
			std::vector<std::string> options;
		};

		/// <summary>
		/// PropertyMetaData is a variant type that can hold additional metadata for a property.
		/// </summary>
		using PropertyMetaData = std::variant<std::monostate, EnumMetaData>;

		/// <summary>
		/// PropertyInfo struct represents a property of a behavior.
		/// </summary>
		struct PropertyInfo {
			std::string name;
			PropertyType type;
			PropertyHint hint = PropertyHint::None;
			void* data;
			PropertyMetaData metaData;
		};

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