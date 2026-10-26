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

		using MeshMaterialPair = std::optional<std::pair<const Graphics::Mesh&, const Graphics::Material&>>;

		/// <summary>
		/// Entity class represents a game object in the scene. 
		/// It can have a transform, behaviors, and child entities. 
		/// It can be rendered and serialized.
		/// </summary>
		class Entity 
			: public GFXEngine::ISerializable, public GFXEngine::Graphics::IRenderable
		{

		private:
			std::vector<std::string> m_tags;
			std::vector<std::unique_ptr<Behavior>> m_behaviors;
			std::vector<std::unique_ptr<Entity>> m_childs;
			Math::AABB m_aabb;
			Scene* m_scene = nullptr;
			bool m_visible = true;
			GFXEngine::Math::Transform m_transform;
			Entity* m_parent = nullptr;

		public:
			enum PropertyComponentType
			{
				Transform,
				Name,
				Visibility
			};

		public:
			Entity();
			Entity(const std::string& name);
			virtual ~Entity() = default;
			Entity(const Entity&) = delete;
			Entity& operator=(const Entity&) = delete;
			Entity(Entity&&) = default;
			Entity& operator=(Entity&&) = default;

		public:
			std::string name;
			std::string uuid;

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

			virtual const glm::vec3& getPosition() const { 
				return m_transform.position; 
			}
			
			virtual const glm::quat& getRotation() const { 
				return m_transform.rotation; 
			}

			virtual glm::vec3 getEulerRotation() const { 
				return m_transform.getEulerRotation(); 
			}
			
			virtual const glm::vec3& getScale() const { 
				return m_transform.scale; 
			}

			virtual glm::mat4 getModelMatrix() const { 

				glm::mat4 modelMatrix = m_transform.getModelMatrix();
				if (this->hasParent()) {
					modelMatrix = this->getParent()->getModelMatrix() * modelMatrix;
				}
				return modelMatrix;
			}

			virtual glm::mat4 getLocalModelMatrix() const {
				return m_transform.getModelMatrix();
			}
			
			virtual const Math::Transform& getTransform() const { 
				return m_transform; 
			}

		public:

			void setScene(Scene* scene) { 
				m_scene = scene; 
				for (auto& child : m_childs) {
					child->setScene(scene);
				}
			}

			void clearScene() {
				m_scene = nullptr;
				for (const auto& child : m_childs) {
					child->clearScene();
				}
			}
			
			Scene* getScene() const { 
				return m_scene; 
			}

			bool isVisible() const { 
				return m_visible; 
			}
			
			void setVisible(bool visible) { 
				m_visible = visible; 
			}

			const std::string& getName() const { 
				return name; 
			}
			
			void setName(const std::string& name) { 
				this->name = name; 
			}

			const std::string& getUUID() const { 
				return uuid; 
			}

			bool hasTag(const std::string& tag) const {
				for (const auto& t : m_tags) {
					if (t == tag) return true;
				}
				return false;
			}
			
			void addTag(const std::string& tag) {
				if (!hasTag(tag)) m_tags.push_back(tag);
			}

		public:
			
			//************************************
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
				return nullptr;
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

		public:

			void setParent(Entity* entity) {
				m_parent = entity;
			}

			Entity* getParent() const {
				return m_parent;
			}

			bool hasParent() const {
				return m_parent != nullptr;
			}

			void clearParent() {
				this->clearScene();
				m_parent = nullptr;
			}

			bool hasChilds() const {
				return !m_childs.empty();
			}

			bool ownsChild(Entity* entity, bool recursive = false) const {
				for (const auto& other : m_childs) {
					if (other.get() == entity) {
						return true;
					}
					if (recursive) {
						if (other->ownsChild(entity, recursive)) {
							return true;
						}
					}
				}
				return false;
			}

			template<typename T>
			T* addChild(std::unique_ptr<T> entity) {
				static_assert(std::is_base_of<Entity, T>::value, "T must be a subclass of Entity");
				entity->setParent(this);

				if (m_scene != nullptr) {
					entity->setScene(m_scene);
				}

				m_childs.push_back(std::move(entity));
				return static_cast<T*>(m_childs.back().get());
			}

			template<typename T>
			T* findChild(const std::string& name) {
				for (const auto& entity : m_childs) {
					if (entity->getName() == name)
					{
						return dynamic_cast<T*>(entity.get());
					}
				}
				return nullptr;
			}

			template<typename Func>
			void foreachChild(Func&& func) {
				for (auto& entity : m_childs) {
					func(*entity);
				}
			}

			template<typename T>
			std::unique_ptr<T> detachChild(Entity* target)
			{
				// Cast target entity to T*
				auto* derived = dynamic_cast<T*>(target);
				if (!derived) {
					return nullptr;
				}

				// Find the unique_ptr from the target entity in the childs
				auto it = std::find_if(m_childs.begin(), m_childs.end(), 
					[target](const auto& entity) {
						return entity.get() == target;
					});

				// If we dont find an entity return nullptr
				if (it == m_childs.end()) {
					return nullptr;
				}

				// Clear the parent from the target
				(*it)->clearParent();

				// Release the entity from the unique_ptr and erase it from the vector
				it->release();
				m_childs.erase(it);

				// return it as an unique_ptr
				return std::unique_ptr<T>(derived);
			}

		public:

			virtual void init(Scene& scene, GFXEngine::Graphics::Renderer& renderer);
			virtual void update(Scene& scene, GFXEngine::Graphics::Camera& camera, float deltaTime);
			virtual void buildRenderTasks(GFXEngine::Graphics::RenderContext& context, GFXEngine::Graphics::RenderQueue& renderQueue) override;
			virtual void destroy(Scene& scene, GFXEngine::Graphics::Renderer& renderer);
			virtual void propertyChanged(PropertyComponentType componentType) {}
			virtual void getGraphicResources(GFXEngine::Graphics::GraphicResources& resources, uint32_t imageIndex) const {}
			virtual void getMeshMaterialGraphicResources(Graphics::GraphicResources& resources, uint32_t imageIndex, size_t meshIndex) const {}
			virtual size_t getMeshCount() const { return 0; }
			virtual MeshMaterialPair getMeshAndMaterial(size_t index) const { return MeshMaterialPair(); }
            virtual bool pick(const GFXEngine::Physics::Ray& ray, float& tdistance, bool pickMesh = false) const;

		public:
			
			virtual std::vector<PropertyInfo> getProperties();
			nlohmann::json serialize() const override;
			void deserialize(const nlohmann::json& data, GFXEngine::SerializationContext& context, GFXEngine::SerializationFlags flags = GFXEngine::SerializationFlags::None) override;
			void resolveReferences(GFXEngine::SerializationContext& context) override;
			void exportToPrefab(const std::filesystem::path& path) const;

		public:

			Math::AABB getAABB() const { 
				return m_aabb; 
			}

            Math::AABB getWorldAABB() const { 
				return m_aabb.applyTransform(this->getModelMatrix()); 
			}
			
			void setAABB(const Math::AABB& aabb) { 
				m_aabb = aabb; 
			}

		public:

			template<typename T>
			T* as() {
				static_assert(std::is_base_of_v<Entity, T>, "T must be a subclass of Entity");
				return dynamic_cast<T*>(this);
			}
		};
	}
}
