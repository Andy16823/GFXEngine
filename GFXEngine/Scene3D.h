#pragma once
#include "Scene.h"
#include <vector>
#include "Entity.h"
#include <span>
#include "EnvironmentMap.h"
#include "DirectionalLight.h"
#include "Fog.h"
#include "DataTypes.h"
#include "RenderQueue.h"
#include <execution>

namespace GFXEngine {
	namespace Core {

		class Scene3D : public Scene
		{
		private:
			std::vector<std::unique_ptr<Entity>> m_entities;
			EngineTypes::AssetReference m_environmentMapRef;
			GFXEngine::Graphics::RenderQueue m_renderQueue;
			bool m_useParallelRendering = false;

			//************************************
			// Method:    renderSerial
			// FullName:  GFXEngine::Core::Scene3D::renderSerial
			// Access:    private 
			// Returns:   void
			// Qualifier:
			// Parameter: GFXEngine::Graphics::RenderContext & context
			//************************************
			void renderSerial(GFXEngine::Graphics::RenderContext& context);

			//************************************
			// Method:    renderParallel
			// FullName:  GFXEngine::Core::Scene3D::renderParallel
			// Access:    private 
			// Returns:   void
			// Qualifier:
			// Parameter: GFXEngine::Graphics::RenderContext & context
			//************************************
			void renderParallel(GFXEngine::Graphics::RenderContext& context);
			
			//************************************
			// Method:    renderEnvMap
			// FullName:  GFXEngine::Core::Scene3D::renderEnvMap
			// Access:    private 
			// Returns:   void
			// Qualifier:
			// Parameter: GFXEngine::Graphics::RenderContext & context
			// Parameter: const GFXEngine::Graphics::EnvironmentMap & envMap
			//************************************
			void renderEnvMap(GFXEngine::Graphics::RenderContext& context, const GFXEngine::Graphics::EnvironmentMap& envMap);
		public:
			Graphics::DirectionalLight directionalLight;
			Graphics::Fog fog;

		public:
			//************************************
			// Method:    Scene3D
			// FullName:  GFXEngine::Core::Scene3D::Scene3D
			// Access:    public 
			// Returns:   
			// Qualifier:
			//************************************
			Scene3D() = default;
			
			//************************************
			// Method:    ~Scene3D
			// FullName:  GFXEngine::Core::Scene3D::~Scene3D
			// Access:    virtual public 
			// Returns:   
			// Qualifier:
			//************************************
			virtual ~Scene3D() = default;
			
			//************************************
			// Method:    Scene3D
			// FullName:  GFXEngine::Core::Scene3D::Scene3D
			// Access:    public 
			// Returns:   
			// Qualifier: noexcept
			// Parameter: Scene3D & &
			//************************************
			Scene3D(Scene3D&&) noexcept = default;
			
			//************************************
			// Method:    operator=
			// FullName:  GFXEngine::Core::Scene3D::operator=
			// Access:    public 
			// Returns:   GFXEngine::Core::Scene3D&
			// Qualifier: noexcept = default
			// Parameter: Scene3D & &
			//************************************
			Scene3D& operator=(Scene3D&&) noexcept = default;
			
			//************************************
			// Method:    Scene3D
			// FullName:  GFXEngine::Core::Scene3D::Scene3D
			// Access:    public 
			// Returns:   
			// Qualifier:
			// Parameter: const Scene3D &
			//************************************
			Scene3D(const Scene3D&) = delete;
			
			//************************************
			// Method:    operator=
			// FullName:  GFXEngine::Core::Scene3D::operator=
			// Access:    public 
			// Returns:   GFXEngine::Core::Scene3D&
			// Qualifier: = delete
			// Parameter: const Scene3D &
			//************************************
			Scene3D& operator=(const Scene3D&) = delete;

		public:

			//************************************
			// Method:    init
			// FullName:  GFXEngine::Core::Scene3D::init
			// Access:    public 
			// Returns:   void
			// Qualifier:
			// Parameter: Graphics::Renderer & renderer
			//************************************
			void init(Graphics::Renderer& renderer) override;

			//************************************
			// Method:    update
			// FullName:  GFXEngine::Core::Scene3D::update
			// Access:    public 
			// Returns:   void
			// Qualifier:
			// Parameter: Graphics::Camera & camera
			// Parameter: float deltaTime
			//************************************
			void update(Graphics::Camera& camera, float deltaTime) override;

			//************************************
			// Method:    beforeRender
			// FullName:  GFXEngine::Core::Scene3D::beforeRender
			// Access:    public 
			// Returns:   void
			// Qualifier:
			// Parameter: Graphics::Renderer & renderer
			// Parameter: Graphics::Camera & camera
			// Parameter: uint32_t imageIndex
			//************************************
			void beforeRender(Graphics::Renderer& renderer, Graphics::Camera& camera, uint32_t imageIndex) override;

			//************************************
			// Method:    render
			// FullName:  GFXEngine::Core::Scene3D::render
			// Access:    public 
			// Returns:   void
			// Qualifier:
			// Parameter: Graphics::Renderer & renderer
			// Parameter: Graphics::Camera & camera
			// Parameter: uint32_t imageIndex
			//************************************
			void render(Graphics::Renderer& renderer, Graphics::Camera& camera, uint32_t imageIndex) override;

			//************************************
			// Method:    afterRender
			// FullName:  GFXEngine::Core::Scene3D::afterRender
			// Access:    public 
			// Returns:   void
			// Qualifier:
			// Parameter: Graphics::Renderer & renderer
			// Parameter: Graphics::Camera & camera
			// Parameter: uint32_t imageIndex
			//************************************
			void afterRender(Graphics::Renderer& renderer, Graphics::Camera& camera, uint32_t imageIndex) override;
			
			//************************************
			// Method:    destroy
			// FullName:  GFXEngine::Core::Scene3D::destroy
			// Access:    public 
			// Returns:   void
			// Qualifier:
			// Parameter: Graphics::Renderer & renderer
			//************************************
			void destroy(Graphics::Renderer& renderer) override;
			
			//************************************
			// Method:    input
			// FullName:  GFXEngine::Core::Scene3D::input
			// Access:    public 
			// Returns:   void
			// Qualifier:
			// Parameter: int key
			// Parameter: int mods
			// Parameter: int action
			//************************************
			void input(int key, int mods, int action) override;
			
			//************************************
			// Method:    deserialize
			// FullName:  GFXEngine::Core::Scene3D::deserialize
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
			// FullName:  GFXEngine::Core::Scene3D::resolveReferences
			// Access:    public 
			// Returns:   void
			// Qualifier:
			// Parameter: GFXEngine::SerializationContext & context
			//************************************
			void resolveReferences(GFXEngine::SerializationContext& context) override;

			//************************************
			// Method:    serialize
			// FullName:  GFXEngine::Core::Scene3D::serialize
			// Access:    public 
			// Returns:   nlohmann::json
			// Qualifier: const 
			//************************************
			nlohmann::json serialize() const override;
			
			//************************************
			// Method:    getGraphicResources
			// FullName:  GFXEngine::Core::Scene3D::getGraphicResources
			// Access:    public 
			// Returns:   void
			// Qualifier: const 
			// Parameter: Graphics::GraphicResources & resources
			// Parameter: uint32_t imageIndex
			//************************************
			void getGraphicResources(Graphics::GraphicResources& resources, uint32_t imageIndex) const override;

			//************************************
			// Method:    getProperties
			// FullName:  GFXEngine::Core::Scene3D::getProperties
			// Access:    public 
			// Returns:   std::vector<GFXEngine::Core::PropertyInfo>
			// Qualifier:
			//************************************
			std::vector<PropertyInfo> getProperties() override;
			
			//************************************
			// Method:    instantiatePrefab
			// FullName:  GFXEngine::Core::Scene3D::instantiatePrefab
			// Access:    public 
			// Returns:   GFXEngine::Core::Entity*
			// Qualifier:
			// Parameter: const std::filesystem::path & path
			// Parameter: GFXEngine::SerializationContext & context
			//************************************
			Entity* instantiatePrefab(const std::filesystem::path& path, GFXEngine::SerializationContext& context) override;

			//************************************
			// Method:    isUsingParallelRendering
			// FullName:  GFXEngine::Core::Scene3D::isUsingParallelRendering
			// Access:    public 
			// Returns:   bool
			// Qualifier: const
			//************************************
			bool isUsingParallelRendering() const { return m_useParallelRendering; }
			
			//************************************
			// Method:    setUseParallelRendering
			// FullName:  GFXEngine::Core::Scene3D::setUseParallelRendering
			// Access:    public 
			// Returns:   void
			// Qualifier:
			// Parameter: bool useParallel
			//************************************
			void setUseParallelRendering(bool useParallel) { m_useParallelRendering = useParallel; }

			//************************************
			// Method:    addEntity
			// FullName:  GFXEngine::Core::Scene3D::addEntity
			// Access:    public 
			// Returns:   T*
			// Qualifier:
			// Parameter: std::unique_ptr<T> entity
			//************************************
			template<typename T>
			T* addEntity(std::unique_ptr<T> entity) {
				static_assert(std::is_base_of<Entity, T>::value, "T must be derived from Entity");
				entity->setScene(this);
				T* entityPtr = entity.get();
				m_entities.push_back(std::move(entity));
				return entityPtr;
			}

			//************************************
			// Method:    getEntities
			// FullName:  GFXEngine::Core::Scene3D::getEntities
			// Access:    public 
			// Returns:   std::vector<GFXEngine::Core::Entity*>
			// Qualifier:
			//************************************
			std::vector<Entity*> getEntities() {
				std::vector<Entity*> entityPointers;
				for (auto& entity : m_entities) {
					entityPointers.push_back(entity.get());
				}
				return entityPointers;
			}

			//************************************
			// Method:    forEachEntity
			// FullName:  GFXEngine::Core::Scene3D::forEachEntity
			// Access:    public 
			// Returns:   void
			// Qualifier:
			// Parameter: const std::function<void
			// Parameter: Entity & 
			// Parameter: > & func
			//************************************
			void forEachEntity(const std::function<void(Entity&)>& func) {
				for (auto& entity : m_entities) {
					func(*entity);
				}
			}

			//************************************
			// Method:    forEachEntityPar
			// FullName:  GFXEngine::Core::Scene3D::forEachEntityPar
			// Access:    public 
			// Returns:   void
			// Qualifier:
			// Parameter: Func & & func
			//************************************
			template<typename Func>
			void forEachEntityPar(Func&& func)
			{
				std::for_each(std::execution::par, m_entities.begin(), m_entities.end(), [&](const std::unique_ptr<Entity>& entity) {
					thread_local int threadIndex = -1;
					if (threadIndex == -1) {
						static std::atomic<int> counter(0);
						threadIndex = counter++;
					}
					func(*entity, threadIndex);
					});
			}

			//************************************
			// Method:    forEachEntityOfType
			// FullName:  GFXEngine::Core::Scene3D::forEachEntityOfType
			// Access:    public 
			// Returns:   void
			// Qualifier:
			// Parameter: const std::function<void
			// Parameter: T & 
			// Parameter: > & func
			//************************************
			template<typename T>
			void forEachEntityOfType(const std::function<void(T&)>& func) {
				for (auto& entity : m_entities) {
					if (auto casted = dynamic_cast<T*>(entity.get())) {
						func(*casted);
					}
				}
			}
			
			//************************************
			// Method:    collectEntities
			// FullName:  GFXEngine::Core::Scene3D::collectEntities
			// Access:    public 
			// Returns:   std::vector<GFXEngine::Core::Entity*>
			// Qualifier:
			// Parameter: const std::function<bool
			// Parameter: Entity & 
			// Parameter: > & predicate
			//************************************
			std::vector<Entity*> collectEntities(const std::function<bool(Entity&)>& predicate) {
				std::vector<Entity*> collectedEntities;
				for (auto& entity : m_entities) {
					if (predicate(*entity)) {
						collectedEntities.push_back(entity.get());
					}
				}
				return collectedEntities;
			}

			//************************************
			// Method:    getEntity
			// FullName:  GFXEngine::Core::Scene3D::getEntity
			// Access:    public 
			// Returns:   GFXEngine::Core::Entity*
			// Qualifier:
			// Parameter: size_t index
			//************************************
			Entity* getEntity(size_t index) {
				if (index >= m_entities.size()) {
					throw std::out_of_range("Entity index out of range");
				}
				return m_entities[index].get();
			}

			//************************************
			// Method:    findEntityByName
			// FullName:  GFXEngine::Core::Scene3D::findEntityByName
			// Access:    public 
			// Returns:   GFXEngine::Core::Entity*
			// Qualifier:
			// Parameter: const std::string & name
			//************************************
			Entity* findEntityByName(const std::string& name) {
				for (auto& entity : m_entities) {
					if (entity->getName() == name) {
						return entity.get();
					}
				}
				return nullptr;
			}

			//************************************
			// Method:    findEntityByUUID
			// FullName:  GFXEngine::Core::Scene3D::findEntityByUUID
			// Access:    public 
			// Returns:   GFXEngine::Core::Entity*
			// Qualifier:
			// Parameter: const std::string & uuid
			//************************************
			Entity* findEntityByUUID(const std::string& uuid) {
				for (auto& entity : m_entities) {
					if (entity->getUUID() == uuid) {
						return entity.get();
					}
				}
				return nullptr;
			}

			//************************************
			// Method:    findEntitiesByTag
			// FullName:  GFXEngine::Core::Scene3D::findEntitiesByTag
			// Access:    public 
			// Returns:   std::vector<GFXEngine::Core::Entity*>
			// Qualifier:
			// Parameter: const std::string & tag
			//************************************
			std::vector<Entity*> findEntitiesByTag(const std::string& tag) {
				std::vector<Entity*> taggedEntities;
				for (auto& entity : m_entities) {
					if (entity->hasTag(tag)) {
						taggedEntities.push_back(entity.get());
					}
				}
				return taggedEntities;
			}

			//************************************
			// Method:    clearEntities
			// FullName:  GFXEngine::Core::Scene3D::clearEntities
			// Access:    public 
			// Returns:   void
			// Qualifier:
			//************************************
			void clearEntities() {
				m_entities.clear();
			}

			//************************************
			// Method:    setEnvironmentMap
			// FullName:  GFXEngine::Core::Scene3D::setEnvironmentMap
			// Access:    public 
			// Returns:   void
			// Qualifier:
			// Parameter: Graphics::EnvironmentMap * environmentMap
			//************************************
			void setEnvironmentMap(Graphics::EnvironmentMap* environmentMap) {
				m_environmentMapRef.set(environmentMap);
			}
		};
	}
}
