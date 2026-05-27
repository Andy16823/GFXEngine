#include "Scene.h"
#include <vector>
#include "Entity.h"
#include <span>
#include "EnviromentMap.h"
#include "DirectionalLight.h"
#include "DataTypes.h"
#include "RenderQueue.h"
#include <execution>

#pragma once
namespace GFXEngine {
	namespace Core {

		/// <summary>
		/// Default 3D scene implementation that manages a collection of entities.
		/// </summary>
		class Scene3D : public Scene
		{
		public:
			Graphics::DirectionalLight directionalLight;

			Scene3D() = default;
			virtual ~Scene3D() = default;

			void init(Graphics::Renderer& renderer) override;
			void update(Graphics::Camera& camera, float deltaTime) override;
			void beforeRender(Graphics::Renderer& renderer, Graphics::Camera& camera, uint32_t imageIndex) override;
			void render(Graphics::Renderer& renderer, Graphics::Camera& camera, uint32_t imageIndex) override;
			void afterRender(Graphics::Renderer& renderer, Graphics::Camera& camera, uint32_t imageIndex) override;
			void destroy(Graphics::Renderer& renderer) override;
			void input(int key, int mods, int action) override;

			std::vector<PropertyInfo> getProperties() override;
			nlohmann::json serialize() const override;
			void deserialize(const nlohmann::json& data, GFXEngine::SerializationContext& context, GFXEngine::SerializationFlags flags = GFXEngine::SerializationFlags::None) override;

			Entity* instantiatePrefab(const std::filesystem::path& path, GFXEngine::SerializationContext& context) override;

			template<typename T>
			T* addEntity(std::unique_ptr<T> entity) {
				static_assert(std::is_base_of<Entity, T>::value, "T must be derived from Entity");
				entity->setScene(this);
				T* entityPtr = entity.get();
				m_entities.push_back(std::move(entity));
				return entityPtr;
			}

			std::vector<Entity*> getEntities() {
				std::vector<Entity*> entityPointers;
				for (auto& entity : m_entities) {
					entityPointers.push_back(entity.get());
				}
				return entityPointers;
			}

			void forEachEntity(const std::function<void(Entity&)>& func) {
				for (auto& entity : m_entities) {
					func(*entity);
				}
			}

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

			template<typename T>
			void forEachEntityOfType(const std::function<void(T&)>& func) {
				for (auto& entity : m_entities) {
					if (auto casted = dynamic_cast<T*>(entity.get())) {
						func(*casted);
					}
				}
			}
			
			std::vector<Entity*> collectEntities(const std::function<bool(Entity&)>& predicate) {
				std::vector<Entity*> collectedEntities;
				for (auto& entity : m_entities) {
					if (predicate(*entity)) {
						collectedEntities.push_back(entity.get());
					}
				}
				return collectedEntities;
			}

			Entity* getEntity(size_t index) {
				if (index >= m_entities.size()) {
					throw std::out_of_range("Entity index out of range");
				}
				return m_entities[index].get();
			}

			Entity* findEntityByName(const std::string& name) {
				for (auto& entity : m_entities) {
					if (entity->getName() == name) {
						return entity.get();
					}
				}
				return nullptr;
			}

			Entity* findEntityByUUID(const std::string& uuid) {
				for (auto& entity : m_entities) {
					if (entity->getUUID() == uuid) {
						return entity.get();
					}
				}
				return nullptr;
			}

			std::span<Entity*> findEntitiesByTag(const std::string& tag) {
				std::vector<Entity*> taggedEntities;
				for (auto& entity : m_entities) {
					if (entity->hasTag(tag)) {
						taggedEntities.push_back(entity.get());
					}
				}
				return taggedEntities;
			}

			void clearEntities() {
				m_entities.clear();
			}

			void setEnviromentMap(Graphics::EnviromentMap* enviromentMap) {
				m_enviromentMapRef.set(enviromentMap);
			}

		private:
			std::vector<std::unique_ptr<Entity>> m_entities;
			EngineTypes::AssetReference m_enviromentMapRef;
			GFXEngine::Graphics::RenderQueue m_renderQueue;
		};
	}
}
