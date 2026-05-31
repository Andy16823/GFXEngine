#pragma once

#include <algorithm>
#include <memory>
#include <stdexcept>
#include <utility>
#include <vector>
#include <string>
#include <filesystem>
#include <optional>

#include "Transform.h"
#include "Renderer.h"
#include "Camera.h"
#include "Behavior.h"
#include "Material.h"
#include "Mesh3D.h"
#include "Scene.h"
#include "AABB.h"
#include "ISerializable.h"
#include "PropertyInfo.h"
#include "IRenderable.h"

namespace GFXEngine {
	namespace Core {

		/// <summary>
		/// Mesh and Material pair type used for rendering. It is an optional type that can be empty if the mesh or material is not available.
		/// </summary>
		using MeshMaterialPair = std::optional<std::pair<const Graphics::Mesh&, const Graphics::Material&>>;

		/// <summary>
		/// Base class for every entity in the game.
		/// </summary>
		class Entity : public GFXEngine::ISerializable, public GFXEngine::Graphics::IRenderable
		{
		public:
			enum PropertyComponentType
			{
				Transform,
				Name,
				Visibility
			};

		/* ---------------------------------------------------------------------
		   Construction / Lifetime
		   --------------------------------------------------------------------- */
		public:
			Entity();
			Entity(const std::string& name);
			virtual ~Entity() = default;

			Entity(const Entity&) = delete;
			Entity& operator=(const Entity&) = delete;
			Entity(Entity&&) = default;
			Entity& operator=(Entity&&) = default;

		/* ---------------------------------------------------------------------
		   Public fields
		   --------------------------------------------------------------------- */
		public:
			std::string name;
			std::string uuid;

		/* ---------------------------------------------------------------------
		   Transform API
		   --------------------------------------------------------------------- */
		public:
			virtual void setPosition(const glm::vec3& position) {
				m_transform.position = position;
				this->propertyChanged(PropertyComponentType::Transform);
			}
			virtual void setPosition(float x, float y, float z) {
				m_transform.position = glm::vec3(x, y, z);
				this->propertyChanged(PropertyComponentType::Transform);
			}

			virtual void translate(const glm::vec3& translation) {
				m_transform.translate(translation);
				this->propertyChanged(PropertyComponentType::Transform);
			}
			virtual void translate(float x, float y, float z) {
				m_transform.translate(glm::vec3(x, y, z));
				this->propertyChanged(PropertyComponentType::Transform);
			}

			virtual void forward(float distance) {
				m_transform.forward(distance);
				this->propertyChanged(PropertyComponentType::Transform);
			}
			virtual void right(float distance) {
				m_transform.right(distance);
				this->propertyChanged(PropertyComponentType::Transform);
			}

			virtual void setRotation(const glm::quat& rotation) {
				m_transform.rotation = rotation;
				this->propertyChanged(PropertyComponentType::Transform);
			}
			virtual void setRotation(const glm::vec3& eulerRotation) {
				//m_transform.rotation = glm::quat(eulerRotation);
				m_transform.setRotationFromEuler(eulerRotation);
				this->propertyChanged(PropertyComponentType::Transform);
			}
			virtual void setRotation(float pitch, float yaw, float roll) {
				//m_transform.rotation = glm::quat(glm::vec3(pitch, yaw, roll)); // TODO: Check if this is correct
				m_transform.setRotationFromEuler(glm::vec3(pitch, yaw, roll));
				this->propertyChanged(PropertyComponentType::Transform);
			}
			virtual void rotateWorld(float pitch, float yaw, float roll) {
				m_transform.rotateWorld(pitch, yaw, roll);
				this->propertyChanged(PropertyComponentType::Transform);
			}
			virtual void rotateLocal(float pitch, float yaw, float roll) {
				m_transform.rotateLocal(pitch, yaw, roll);
				this->propertyChanged(PropertyComponentType::Transform);
			}

			virtual void setScale(const glm::vec3& scale) {
				m_transform.scale = scale;
				this->propertyChanged(PropertyComponentType::Transform);
			}
			virtual void setScale(float x, float y, float z) {
				m_transform.scale = glm::vec3(x, y, z);
				this->propertyChanged(PropertyComponentType::Transform);
			}
			virtual void setScale(float uniformScale) {
				m_transform.scale = glm::vec3(uniformScale);
				this->propertyChanged(PropertyComponentType::Transform);
			}

			virtual void setModelMatrix(const glm::mat4& modelMatrix) {
				m_transform.setFromMatrix(modelMatrix);
				this->propertyChanged(PropertyComponentType::Transform);
			}
			virtual void setTransform(const Math::Transform& transform) {
				m_transform = transform;
				this->propertyChanged(PropertyComponentType::Transform);
			}

			virtual const glm::vec3& getPosition() const { return m_transform.position; }
			virtual const glm::quat& getRotation() const { return m_transform.rotation; }
			virtual glm::vec3 getEulerRotation() const { return m_transform.getEulerRotation(); }
			virtual const glm::vec3& getScale() const { return m_transform.scale; }
			virtual const glm::mat4& getModelMatrix() const { return m_transform.getModelMatrix(); }
			virtual const Math::Transform& getTransform() const { return m_transform; }

		/* ---------------------------------------------------------------------
		   Scene / Visibility / Name / Tags
		   --------------------------------------------------------------------- */
		public:
			void setScene(Scene* scene) { m_scene = scene; }
			Scene* getScene() const { return m_scene; }

			bool isVisible() const { return m_visible; }
			void setVisible(bool visible) { m_visible = visible; }

			const std::string& getName() const { return name; }
			void setName(const std::string& name) { this->name = name; }

			const std::string& getUUID() const { return uuid; }

			bool hasTag(const std::string& tag) const {
				for (const auto& t : m_tags) {
					if (t == tag) return true;
				}
				return false;
			}
			void addTag(const std::string& tag) {
				if (!hasTag(tag)) m_tags.push_back(tag);
			}

		/* ---------------------------------------------------------------------
		   Behavior management
		   --------------------------------------------------------------------- */
		public:
			template<typename T>
			T* addBehavior(std::unique_ptr<T> behavior) {
				static_assert(std::is_base_of<Behavior, T>::value, "T must be a subclass of Behavior");
				behavior->setEntity(this);
				m_behaviors.push_back(std::move(behavior));
				return static_cast<T*>(m_behaviors.back().get());
			}

			template<typename T>
			T* getBehavior() {
				static_assert(std::is_base_of<Behavior, T>::value, "T must be a subclass of Behavior");
				for (auto& behavior : m_behaviors) {
					if (auto casted = dynamic_cast<T*>(behavior.get())) {
						return casted;
					}
				}
				nullptr;
			}

			template<typename T>
			bool hasBehavior() const {
				static_assert(std::is_base_of<Behavior, T>::value, "T must be a subclass of Behavior");
				for (const auto& behavior : m_behaviors) {
					if (dynamic_cast<T*>(behavior.get())) {
						return true;
					}
				}
				return false;
			}

			void removeBehavior(const std::string& behaviorUUID) {
				m_behaviors.erase(std::remove_if(m_behaviors.begin(), m_behaviors.end(),
					[&](const std::unique_ptr<Behavior>& behavior) {
						return behavior->getUUID() == behaviorUUID;
					}), m_behaviors.end());
			}

			void removeBehavior(const std::string& behaviorUUID, std::function<void(Behavior*)> onDestroy) {
				m_behaviors.erase(std::remove_if(m_behaviors.begin(), m_behaviors.end(),
					[&](const std::unique_ptr<Behavior>& behavior) {
						if (behavior->getUUID() == behaviorUUID) {
							onDestroy(behavior.get());
							return true;
						}
						return false;
					}), m_behaviors.end());
			}

			void removeBehavior(Behavior* behaviorToRemove) {
				m_behaviors.erase(std::remove_if(m_behaviors.begin(), m_behaviors.end(),
					[&](const std::unique_ptr<Behavior>& behavior) {
						return behavior.get() == behaviorToRemove;
					}), m_behaviors.end());
			}

			void removeBehavior(Behavior* behaviorToRemove, std::function<void(Behavior*)> onDestroy) {
				m_behaviors.erase(std::remove_if(m_behaviors.begin(), m_behaviors.end(),
					[&](const std::unique_ptr<Behavior>& behavior) {
						if (behavior.get() == behaviorToRemove) {
							onDestroy(behavior.get());
							return true;
						}
						return false;
					}), m_behaviors.end());
			}

			void foreachBehavior(const std::function<void(Behavior*)>& func, bool reverse = false) {
				if (reverse) {
					for (auto it = m_behaviors.rbegin(); it != m_behaviors.rend(); ++it) {
						func(it->get());
					}
				} else {
					for (auto& behavior : m_behaviors) {
						func(behavior.get());
					}
				}
			}

		/* ---------------------------------------------------------------------
		   Rendering / Graphics interface
		   --------------------------------------------------------------------- */
		public:
			virtual void init(Scene& scene, GFXEngine::Graphics::Renderer& renderer);
			virtual void update(Scene& scene, GFXEngine::Graphics::Camera& camera, float deltaTime);
			virtual void buildRenderTasks(GFXEngine::Graphics::RenderContext& context, GFXEngine::Graphics::RenderQueue& renderQueue) override;
			virtual void destroy(Scene& scene, GFXEngine::Graphics::Renderer& renderer);
			virtual void propertyChanged(PropertyComponentType componentType) {}

			virtual void getGraphicResources(GFXEngine::Graphics::GraphicResources& resources, uint32_t imageIndex) const {}
			virtual void getMeshMaterialGraphicResources(Graphics::GraphicResources& resources, uint32_t imageIndex, size_t meshIndex) const {}

			virtual size_t getMeshCount() const = 0;
			virtual MeshMaterialPair getMeshAndMaterial(size_t index) const = 0;

		/* ---------------------------------------------------------------------
		   Serialization / Editor integration
		   --------------------------------------------------------------------- */
		public:
			virtual std::vector<PropertyInfo> getProperties();
			nlohmann::json serialize() const override;
			void deserialize(const nlohmann::json& data, GFXEngine::SerializationContext& context, GFXEngine::SerializationFlags flags = GFXEngine::SerializationFlags::None) override;
			void resolveReferences(GFXEngine::SerializationContext& context) override;
			void exportToPrefab(const std::filesystem::path& path) const;

		/* ---------------------------------------------------------------------
		   AABB helpers
		   --------------------------------------------------------------------- */
		public:
			Math::AABB getAABB() const { return m_aabb; }
			Math::AABB getWorldAABB() const { return m_aabb.applyTransform(m_transform.getModelMatrix()); }
			void setAABB(const Math::AABB& aabb) { m_aabb = aabb; }

		/* ---------------------------------------------------------------------
		   Type-safe cast
		   --------------------------------------------------------------------- */
		public:
			template<typename T>
			T* as() {
				static_assert(std::is_base_of_v<Entity, T>, "T must be a subclass of Entity");
				return dynamic_cast<T*>(this);
			}

		/* ---------------------------------------------------------------------
		   Private members
		   --------------------------------------------------------------------- */
		private:
			std::vector<std::string> m_tags;
			std::vector<std::unique_ptr<Behavior>> m_behaviors;
			Math::AABB m_aabb;
			Scene* m_scene = nullptr;
			bool m_visible = true;
			GFXEngine::Math::Transform m_transform;
		};
	}
}
