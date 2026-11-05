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
#include <algorithm>
#include "Raycast.h"
#include "Asset.h"

namespace GFXEngine {
	namespace Core {

		class Scene3D : public Scene
		{
		private:
			std::vector<std::unique_ptr<Entity>> m_entities;
			std::optional<GFXEngine::AssetHandle> m_environmentMapRef = std::nullopt;
			GFXEngine::Graphics::RenderQueue m_renderQueue;

			bool m_useParallelRendering = false;
			void renderSerial(GFXEngine::Graphics::RenderContext& context);
			void renderParallel(GFXEngine::Graphics::RenderContext& context);
			void renderEnvMap(GFXEngine::Graphics::RenderContext& context, const GFXEngine::Graphics::EnvironmentMap& envMap);

		public:
			Graphics::DirectionalLight directionalLight;
			Graphics::Fog fog;

		public:
			
			Scene3D() = default;
			virtual ~Scene3D() = default;
			Scene3D(Scene3D&&) noexcept = default;
			Scene3D& operator=(Scene3D&&) noexcept = default;
			Scene3D(const Scene3D&) = delete;
			Scene3D& operator=(const Scene3D&) = delete;

		public:
			void init(Graphics::Renderer& renderer) override;
			void update(Graphics::Camera& camera, float deltaTime) override;
			void beforeRender(Graphics::Renderer& renderer, Graphics::Camera& camera, uint32_t imageIndex) override;
			void render(Graphics::Renderer& renderer, Graphics::Camera& camera, Graphics::FrameContext& frameContext, uint32_t imageIndex) override;
			void afterRender(Graphics::Renderer& renderer, Graphics::Camera& camera, uint32_t imageIndex) override;
			void destroy(Graphics::Renderer& renderer) override;
			void input(int key, int mods, int action) override;
			void deserialize(const nlohmann::json& data, GFXEngine::SerializationContext& context, GFXEngine::SerializationFlags flags = GFXEngine::SerializationFlags::None) override;
			void resolveReferences(GFXEngine::SerializationContext& context) override;
			nlohmann::json serialize() const override;
			void getGraphicResources(Graphics::GraphicResources& resources, uint32_t imageIndex) const override;
			std::vector<PropertyInfo> getProperties() override;
			void loadFromFile(const std::string& path, GFXEngine::Core::Game& game) override;
			Entity* instantiatePrefab(const std::filesystem::path& path, GFXEngine::SerializationContext& context) override;
			bool ownsEntity(Entity* entity, bool recursive = false) const override;
			bool isUsingParallelRendering() const { return m_useParallelRendering; }
			void setUseParallelRendering(bool useParallel) { m_useParallelRendering = useParallel; }
			
			template<typename T>
			T* addEntity(std::unique_ptr<T> entity) {
				static_assert(std::is_base_of<Entity, T>::value, "T must be derived from Entity");
				entity->setScene(this);
				T* entityPtr = entity.get();
				m_entities.push_back(std::move(entity));
				return entityPtr;
			}

			template<typename T>
			std::unique_ptr<T> detachEntity(Entity* target) {
				auto* derived = dynamic_cast<T*>(target);
				if (!derived) {
					return nullptr;
				}

				auto it = std::find_if(m_entities.begin(), m_entities.end(), [target](const auto& entity) {
					return entity.get() == target;
					});

				if (it == m_entities.end()) {
					return nullptr;
				}

				(*it)->clearScene();

				it->release();
				m_entities.erase(it);

				return std::unique_ptr<T>(derived);
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

			std::vector<Entity*> findEntitiesByTag(const std::string& tag) {
				std::vector<Entity*> taggedEntities;
				for (auto& entity : m_entities) {
					if (entity->hasTag(tag)) {
						taggedEntities.push_back(entity.get());
					}
				}
				return taggedEntities;
			}

            Entity* pickEntity(const GFXEngine::Physics::Ray& ray, bool pickMesh = false, const EntityFilter& filter = nullptr) override;

			void clearEntities() {
				m_entities.clear();
			}

			void setEnvironmentMap(GFXEngine::AssetHandle environmentMap) {
				m_environmentMapRef = environmentMap;
			}
		};
	}
}
