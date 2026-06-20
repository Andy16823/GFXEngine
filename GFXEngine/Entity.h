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

		class Entity : public GFXEngine::ISerializable, public GFXEngine::Graphics::IRenderable
		{
		private:
			std::vector<std::string> m_tags;
			std::vector<std::unique_ptr<Behavior>> m_behaviors;
			Math::AABB m_aabb;
			Scene* m_scene = nullptr;
			bool m_visible = true;
			GFXEngine::Math::Transform m_transform;

		public:
			enum PropertyComponentType
			{
				Transform,
				Name,
				Visibility
			};

		public:

			//************************************
			// Method:    Entity
			// FullName:  GFXEngine::Core::Entity::Entity
			// Access:    public 
			// Returns:   
			// Qualifier:
			//************************************
			Entity();
			
			//************************************
			// Method:    Entity
			// FullName:  GFXEngine::Core::Entity::Entity
			// Access:    public 
			// Returns:   
			// Qualifier:
			// Parameter: const std::string & name
			//************************************
			Entity(const std::string& name);
			
			//************************************
			// Method:    ~Entity
			// FullName:  GFXEngine::Core::Entity::~Entity
			// Access:    virtual public 
			// Returns:   
			// Qualifier:
			//************************************
			virtual ~Entity() = default;

			//************************************
			// Method:    Entity
			// FullName:  GFXEngine::Core::Entity::Entity
			// Access:    public 
			// Returns:   
			// Qualifier:
			// Parameter: const Entity &
			//************************************
			Entity(const Entity&) = delete;
			
			//************************************
			// Method:    operator=
			// FullName:  GFXEngine::Core::Entity::operator=
			// Access:    public 
			// Returns:   GFXEngine::Core::Entity&
			// Qualifier: = delete
			// Parameter: const Entity &
			//************************************
			Entity& operator=(const Entity&) = delete;
			
			//************************************
			// Method:    Entity
			// FullName:  GFXEngine::Core::Entity::Entity
			// Access:    public 
			// Returns:   
			// Qualifier:
			// Parameter: Entity & &
			//************************************
			Entity(Entity&&) = default;
			
			//************************************
			// Method:    operator=
			// FullName:  GFXEngine::Core::Entity::operator=
			// Access:    public 
			// Returns:   GFXEngine::Core::Entity&
			// Qualifier: = default
			// Parameter: Entity & &
			//************************************
			Entity& operator=(Entity&&) = default;

		public:
			std::string name;
			std::string uuid;

		public:
			
			//************************************
			// Method:    setPosition
			// FullName:  GFXEngine::Core::Entity::setPosition
			// Access:    virtual public 
			// Returns:   void
			// Qualifier:
			// Parameter: const glm::vec3 & position
			//************************************
			virtual void setPosition(const glm::vec3& position) {
				m_transform.position = position;
				this->propertyChanged(PropertyComponentType::Transform);
			}

			//************************************
			// Method:    setPosition
			// FullName:  GFXEngine::Core::Entity::setPosition
			// Access:    virtual public 
			// Returns:   void
			// Qualifier:
			// Parameter: float x
			// Parameter: float y
			// Parameter: float z
			//************************************
			virtual void setPosition(float x, float y, float z) {
				m_transform.position = glm::vec3(x, y, z);
				this->propertyChanged(PropertyComponentType::Transform);
			}

			//************************************
			// Method:    translate
			// FullName:  GFXEngine::Core::Entity::translate
			// Access:    virtual public 
			// Returns:   void
			// Qualifier:
			// Parameter: const glm::vec3 & translation
			//************************************
			virtual void translate(const glm::vec3& translation) {
				m_transform.translate(translation);
				this->propertyChanged(PropertyComponentType::Transform);
			}
			
			//************************************
			// Method:    translate
			// FullName:  GFXEngine::Core::Entity::translate
			// Access:    virtual public 
			// Returns:   void
			// Qualifier:
			// Parameter: float x
			// Parameter: float y
			// Parameter: float z
			//************************************
			virtual void translate(float x, float y, float z) {
				m_transform.translate(glm::vec3(x, y, z));
				this->propertyChanged(PropertyComponentType::Transform);
			}

			//************************************
			// Method:    forward
			// FullName:  GFXEngine::Core::Entity::forward
			// Access:    virtual public 
			// Returns:   void
			// Qualifier:
			// Parameter: float distance
			//************************************
			virtual void forward(float distance) {
				m_transform.forward(distance);
				this->propertyChanged(PropertyComponentType::Transform);
			}

			//************************************
			// Method:    right
			// FullName:  GFXEngine::Core::Entity::right
			// Access:    virtual public 
			// Returns:   void
			// Qualifier:
			// Parameter: float distance
			//************************************
			virtual void right(float distance) {
				m_transform.right(distance);
				this->propertyChanged(PropertyComponentType::Transform);
			}

			//************************************
			// Method:    setRotation
			// FullName:  GFXEngine::Core::Entity::setRotation
			// Access:    virtual public 
			// Returns:   void
			// Qualifier:
			// Parameter: const glm::quat & rotation
			//************************************
			virtual void setRotation(const glm::quat& rotation) {
				m_transform.rotation = rotation;
				this->propertyChanged(PropertyComponentType::Transform);
			}

			//************************************
			// Method:    setRotation
			// FullName:  GFXEngine::Core::Entity::setRotation
			// Access:    virtual public 
			// Returns:   void
			// Qualifier:
			// Parameter: const glm::vec3 & eulerRotation
			//************************************
			virtual void setRotation(const glm::vec3& eulerRotation) {
				//m_transform.rotation = glm::quat(eulerRotation);
				m_transform.setRotationFromEuler(eulerRotation);
				this->propertyChanged(PropertyComponentType::Transform);
			}
			
			//************************************
			// Method:    setRotation
			// FullName:  GFXEngine::Core::Entity::setRotation
			// Access:    virtual public 
			// Returns:   void
			// Qualifier:
			// Parameter: float pitch
			// Parameter: float yaw
			// Parameter: float roll
			//************************************
			virtual void setRotation(float pitch, float yaw, float roll) {
				//m_transform.rotation = glm::quat(glm::vec3(pitch, yaw, roll)); // TODO: Check if this is correct
				m_transform.setRotationFromEuler(glm::vec3(pitch, yaw, roll));
				this->propertyChanged(PropertyComponentType::Transform);
			}
			
			//************************************
			// Method:    rotateWorld
			// FullName:  GFXEngine::Core::Entity::rotateWorld
			// Access:    virtual public 
			// Returns:   void
			// Qualifier:
			// Parameter: float pitch
			// Parameter: float yaw
			// Parameter: float roll
			//************************************
			virtual void rotateWorld(float pitch, float yaw, float roll) {
				m_transform.rotateWorld(pitch, yaw, roll);
				this->propertyChanged(PropertyComponentType::Transform);
			}
			
			//************************************
			// Method:    rotateLocal
			// FullName:  GFXEngine::Core::Entity::rotateLocal
			// Access:    virtual public 
			// Returns:   void
			// Qualifier:
			// Parameter: float pitch
			// Parameter: float yaw
			// Parameter: float roll
			//************************************
			virtual void rotateLocal(float pitch, float yaw, float roll) {
				m_transform.rotateLocal(pitch, yaw, roll);
				this->propertyChanged(PropertyComponentType::Transform);
			}

			//************************************
			// Method:    setScale
			// FullName:  GFXEngine::Core::Entity::setScale
			// Access:    virtual public 
			// Returns:   void
			// Qualifier:
			// Parameter: const glm::vec3 & scale
			//************************************
			virtual void setScale(const glm::vec3& scale) {
				m_transform.scale = scale;
				this->propertyChanged(PropertyComponentType::Transform);
			}
			
			//************************************
			// Method:    setScale
			// FullName:  GFXEngine::Core::Entity::setScale
			// Access:    virtual public 
			// Returns:   void
			// Qualifier:
			// Parameter: float x
			// Parameter: float y
			// Parameter: float z
			//************************************
			virtual void setScale(float x, float y, float z) {
				m_transform.scale = glm::vec3(x, y, z);
				this->propertyChanged(PropertyComponentType::Transform);
			}
			
			//************************************
			// Method:    setScale
			// FullName:  GFXEngine::Core::Entity::setScale
			// Access:    virtual public 
			// Returns:   void
			// Qualifier:
			// Parameter: float uniformScale
			//************************************
			virtual void setScale(float uniformScale) {
				m_transform.scale = glm::vec3(uniformScale);
				this->propertyChanged(PropertyComponentType::Transform);
			}

			//************************************
			// Method:    setModelMatrix
			// FullName:  GFXEngine::Core::Entity::setModelMatrix
			// Access:    virtual public 
			// Returns:   void
			// Qualifier:
			// Parameter: const glm::mat4 & modelMatrix
			//************************************
			virtual void setModelMatrix(const glm::mat4& modelMatrix) {
				m_transform.setFromMatrix(modelMatrix);
				this->propertyChanged(PropertyComponentType::Transform);
			}
			
			//************************************
			// Method:    setTransform
			// FullName:  GFXEngine::Core::Entity::setTransform
			// Access:    virtual public 
			// Returns:   void
			// Qualifier:
			// Parameter: const Math::Transform & transform
			//************************************
			virtual void setTransform(const Math::Transform& transform) {
				m_transform = transform;
				this->propertyChanged(PropertyComponentType::Transform);
			}

			//************************************
			// Method:    getPosition
			// FullName:  GFXEngine::Core::Entity::getPosition
			// Access:    virtual public 
			// Returns:   const glm::vec3&
			// Qualifier: const
			//************************************
			virtual const glm::vec3& getPosition() const { return m_transform.position; }
			
			//************************************
			// Method:    getRotation
			// FullName:  GFXEngine::Core::Entity::getRotation
			// Access:    virtual public 
			// Returns:   const glm::quat&
			// Qualifier: const
			//************************************
			virtual const glm::quat& getRotation() const { return m_transform.rotation; }
			
			//************************************
			// Method:    getEulerRotation
			// FullName:  GFXEngine::Core::Entity::getEulerRotation
			// Access:    virtual public 
			// Returns:   glm::vec3
			// Qualifier: const
			//************************************
			virtual glm::vec3 getEulerRotation() const { return m_transform.getEulerRotation(); }
			
			//************************************
			// Method:    getScale
			// FullName:  GFXEngine::Core::Entity::getScale
			// Access:    virtual public 
			// Returns:   const glm::vec3&
			// Qualifier: const
			//************************************
			virtual const glm::vec3& getScale() const { return m_transform.scale; }

			//************************************
			// Method:    getModelMatrix
			// FullName:  GFXEngine::Core::Entity::getModelMatrix
			// Access:    virtual public 
			// Returns:   const glm::mat4&
			// Qualifier: const
			//************************************
			virtual const glm::mat4& getModelMatrix() const { return m_transform.getModelMatrix(); }
			
			//************************************
			// Method:    getTransform
			// FullName:  GFXEngine::Core::Entity::getTransform
			// Access:    virtual public 
			// Returns:   const GFXEngine::Math::Transform&
			// Qualifier: const
			//************************************
			virtual const Math::Transform& getTransform() const { return m_transform; }

		public:
			//************************************
			// Method:    setScene
			// FullName:  GFXEngine::Core::Entity::setScene
			// Access:    public 
			// Returns:   void
			// Qualifier:
			// Parameter: Scene * scene
			//************************************
			void setScene(Scene* scene) { m_scene = scene; }
			
			//************************************
			// Method:    getScene
			// FullName:  GFXEngine::Core::Entity::getScene
			// Access:    public 
			// Returns:   GFXEngine::Core::Scene*
			// Qualifier: const
			//************************************
			Scene* getScene() const { return m_scene; }

			//************************************
			// Method:    isVisible
			// FullName:  GFXEngine::Core::Entity::isVisible
			// Access:    public 
			// Returns:   bool
			// Qualifier: const
			//************************************
			bool isVisible() const { return m_visible; }
			
			//************************************
			// Method:    setVisible
			// FullName:  GFXEngine::Core::Entity::setVisible
			// Access:    public 
			// Returns:   void
			// Qualifier:
			// Parameter: bool visible
			//************************************
			void setVisible(bool visible) { m_visible = visible; }

			//************************************
			// Method:    getName
			// FullName:  GFXEngine::Core::Entity::getName
			// Access:    public 
			// Returns:   const std::string&
			// Qualifier: const
			//************************************
			const std::string& getName() const { return name; }
			
			//************************************
			// Method:    setName
			// FullName:  GFXEngine::Core::Entity::setName
			// Access:    public 
			// Returns:   void
			// Qualifier:
			// Parameter: const std::string & name
			//************************************
			void setName(const std::string& name) { this->name = name; }

			//************************************
			// Method:    getUUID
			// FullName:  GFXEngine::Core::Entity::getUUID
			// Access:    public 
			// Returns:   const std::string&
			// Qualifier: const
			//************************************
			const std::string& getUUID() const { return uuid; }

			//************************************
			// Method:    hasTag
			// FullName:  GFXEngine::Core::Entity::hasTag
			// Access:    public 
			// Returns:   bool
			// Qualifier: const
			// Parameter: const std::string & tag
			//************************************
			bool hasTag(const std::string& tag) const {
				for (const auto& t : m_tags) {
					if (t == tag) return true;
				}
				return false;
			}
			
			//************************************
			// Method:    addTag
			// FullName:  GFXEngine::Core::Entity::addTag
			// Access:    public 
			// Returns:   void
			// Qualifier:
			// Parameter: const std::string & tag
			//************************************
			void addTag(const std::string& tag) {
				if (!hasTag(tag)) m_tags.push_back(tag);
			}

		public:
			
			//************************************
			// Method:    addBehavior
			// FullName:  GFXEngine::Core::Entity::addBehavior
			// Access:    public 
			// Returns:   T*
			// Qualifier:
			// Parameter: std::unique_ptr<T> behavior
			//************************************
			template<typename T>
			T* addBehavior(std::unique_ptr<T> behavior) {
				static_assert(std::is_base_of<Behavior, T>::value, "T must be a subclass of Behavior");
				behavior->setEntity(this);
				m_behaviors.push_back(std::move(behavior));
				return static_cast<T*>(m_behaviors.back().get());
			}

			//************************************
			// Method:    getBehavior
			// FullName:  GFXEngine::Core::Entity::getBehavior
			// Access:    public 
			// Returns:   T*
			// Qualifier:
			//************************************
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

			//************************************
			// Method:    hasBehavior
			// FullName:  GFXEngine::Core::Entity::hasBehavior
			// Access:    public 
			// Returns:   bool
			// Qualifier: const
			//************************************
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

			//************************************
			// Method:    removeBehavior
			// FullName:  GFXEngine::Core::Entity::removeBehavior
			// Access:    public 
			// Returns:   void
			// Qualifier:
			// Parameter: const std::string & behaviorUUID
			//************************************
			void removeBehavior(const std::string& behaviorUUID) {
				m_behaviors.erase(std::remove_if(m_behaviors.begin(), m_behaviors.end(),
					[&](const std::unique_ptr<Behavior>& behavior) {
						return behavior->getUUID() == behaviorUUID;
					}), m_behaviors.end());
			}

			//************************************
			// Method:    removeBehavior
			// FullName:  GFXEngine::Core::Entity::removeBehavior
			// Access:    public 
			// Returns:   void
			// Qualifier:
			// Parameter: const std::string & behaviorUUID
			// Parameter: std::function<void
			// Parameter: Behavior * 
			// Parameter: > onDestroy
			//************************************
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

			//************************************
			// Method:    removeBehavior
			// FullName:  GFXEngine::Core::Entity::removeBehavior
			// Access:    public 
			// Returns:   void
			// Qualifier:
			// Parameter: Behavior * behaviorToRemove
			//************************************
			void removeBehavior(Behavior* behaviorToRemove) {
				m_behaviors.erase(std::remove_if(m_behaviors.begin(), m_behaviors.end(),
					[&](const std::unique_ptr<Behavior>& behavior) {
						return behavior.get() == behaviorToRemove;
					}), m_behaviors.end());
			}

			//************************************
			// Method:    removeBehavior
			// FullName:  GFXEngine::Core::Entity::removeBehavior
			// Access:    public 
			// Returns:   void
			// Qualifier:
			// Parameter: Behavior * behaviorToRemove
			// Parameter: std::function<void
			// Parameter: Behavior * 
			// Parameter: > onDestroy
			//************************************
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

			//************************************
			// Method:    foreachBehavior
			// FullName:  GFXEngine::Core::Entity::foreachBehavior
			// Access:    public 
			// Returns:   void
			// Qualifier:
			// Parameter: const std::function<void
			// Parameter: Behavior * 
			// Parameter: > & func
			// Parameter: bool reverse
			//************************************
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

			//************************************
			// Method:    init
			// FullName:  GFXEngine::Core::Entity::init
			// Access:    virtual public 
			// Returns:   void
			// Qualifier:
			// Parameter: Scene & scene
			// Parameter: GFXEngine::Graphics::Renderer & renderer
			//************************************
			virtual void init(Scene& scene, GFXEngine::Graphics::Renderer& renderer);
			
			//************************************
			// Method:    update
			// FullName:  GFXEngine::Core::Entity::update
			// Access:    virtual public 
			// Returns:   void
			// Qualifier:
			// Parameter: Scene & scene
			// Parameter: GFXEngine::Graphics::Camera & camera
			// Parameter: float deltaTime
			//************************************
			virtual void update(Scene& scene, GFXEngine::Graphics::Camera& camera, float deltaTime);
			
			//************************************
			// Method:    buildRenderTasks
			// FullName:  GFXEngine::Core::Entity::buildRenderTasks
			// Access:    virtual public 
			// Returns:   void
			// Qualifier:
			// Parameter: GFXEngine::Graphics::RenderContext & context
			// Parameter: GFXEngine::Graphics::RenderQueue & renderQueue
			//************************************
			virtual void buildRenderTasks(GFXEngine::Graphics::RenderContext& context, GFXEngine::Graphics::RenderQueue& renderQueue) override;
			
			//************************************
			// Method:    destroy
			// FullName:  GFXEngine::Core::Entity::destroy
			// Access:    virtual public 
			// Returns:   void
			// Qualifier:
			// Parameter: Scene & scene
			// Parameter: GFXEngine::Graphics::Renderer & renderer
			//************************************
			virtual void destroy(Scene& scene, GFXEngine::Graphics::Renderer& renderer);
			
			//************************************
			// Method:    propertyChanged
			// FullName:  GFXEngine::Core::Entity::propertyChanged
			// Access:    virtual public 
			// Returns:   void
			// Qualifier:
			// Parameter: PropertyComponentType componentType
			//************************************
			virtual void propertyChanged(PropertyComponentType componentType) {}

			//************************************
			// Method:    getGraphicResources
			// FullName:  GFXEngine::Core::Entity::getGraphicResources
			// Access:    virtual public 
			// Returns:   void
			// Qualifier: const
			// Parameter: GFXEngine::Graphics::GraphicResources & resources
			// Parameter: uint32_t imageIndex
			//************************************
			virtual void getGraphicResources(GFXEngine::Graphics::GraphicResources& resources, uint32_t imageIndex) const {}
			
			//************************************
			// Method:    getMeshMaterialGraphicResources
			// FullName:  GFXEngine::Core::Entity::getMeshMaterialGraphicResources
			// Access:    virtual public 
			// Returns:   void
			// Qualifier: const
			// Parameter: Graphics::GraphicResources & resources
			// Parameter: uint32_t imageIndex
			// Parameter: size_t meshIndex
			//************************************
			virtual void getMeshMaterialGraphicResources(Graphics::GraphicResources& resources, uint32_t imageIndex, size_t meshIndex) const {}

			//************************************
			// Method:    getMeshCount
			// FullName:  GFXEngine::Core::Entity::getMeshCount
			// Access:    virtual public 
			// Returns:   std::size_t
			// Qualifier: const
			//************************************
			virtual size_t getMeshCount() const = 0;
			
			//************************************
			// Method:    getMeshAndMaterial
			// FullName:  GFXEngine::Core::Entity::getMeshAndMaterial
			// Access:    virtual public 
			// Returns:   GFXEngine::Core::MeshMaterialPair
			// Qualifier: const
			// Parameter: size_t index
			//************************************
			virtual MeshMaterialPair getMeshAndMaterial(size_t index) const = 0;

		public:
			
			//************************************
			// Method:    getProperties
			// FullName:  GFXEngine::Core::Entity::getProperties
			// Access:    virtual public 
			// Returns:   std::vector<GFXEngine::Core::PropertyInfo>
			// Qualifier:
			//************************************
			virtual std::vector<PropertyInfo> getProperties();
			
			//************************************
			// Method:    serialize
			// FullName:  GFXEngine::Core::Entity::serialize
			// Access:    public 
			// Returns:   nlohmann::json
			// Qualifier: const 
			//************************************
			nlohmann::json serialize() const override;
			
			//************************************
			// Method:    deserialize
			// FullName:  GFXEngine::Core::Entity::deserialize
			// Access:    public 
			// Returns:   void
			// Qualifier:
			// Parameter: const nlohmann::json & data
			// Parameter: GFXEngine::SerializationContext & context
			// Parameter: GFXEngine::SerializationFlags flags
			//************************************
			void deserialize(const nlohmann::json& data, GFXEngine::SerializationContext& context, GFXEngine::SerializationFlags flags = GFXEngine::SerializationFlags::None) override;
			
			//************************************
			// Method:    resolveReferences
			// FullName:  GFXEngine::Core::Entity::resolveReferences
			// Access:    public 
			// Returns:   void
			// Qualifier:
			// Parameter: GFXEngine::SerializationContext & context
			//************************************
			void resolveReferences(GFXEngine::SerializationContext& context) override;
			
			//************************************
			// Method:    exportToPrefab
			// FullName:  GFXEngine::Core::Entity::exportToPrefab
			// Access:    public 
			// Returns:   void
			// Qualifier: const
			// Parameter: const std::filesystem::path & path
			//************************************
			void exportToPrefab(const std::filesystem::path& path) const;

		public:

			//************************************
			// Method:    getAABB
			// FullName:  GFXEngine::Core::Entity::getAABB
			// Access:    public 
			// Returns:   GFXEngine::Math::AABB
			// Qualifier: const
			//************************************
			Math::AABB getAABB() const { return m_aabb; }
			
			//************************************
			// Method:    getWorldAABB
			// FullName:  GFXEngine::Core::Entity::getWorldAABB
			// Access:    public 
			// Returns:   GFXEngine::Math::AABB
			// Qualifier: const
			//************************************
			Math::AABB getWorldAABB() const { return m_aabb.applyTransform(m_transform.getModelMatrix()); }
			
			//************************************
			// Method:    setAABB
			// FullName:  GFXEngine::Core::Entity::setAABB
			// Access:    public 
			// Returns:   void
			// Qualifier:
			// Parameter: const Math::AABB & aabb
			//************************************
			void setAABB(const Math::AABB& aabb) { m_aabb = aabb; }

		public:

			//************************************
			// Method:    as
			// FullName:  GFXEngine::Core::Entity::as
			// Access:    public 
			// Returns:   T*
			// Qualifier:
			//************************************
			template<typename T>
			T* as() {
				static_assert(std::is_base_of_v<Entity, T>, "T must be a subclass of Entity");
				return dynamic_cast<T*>(this);
			}
		};
	}
}
