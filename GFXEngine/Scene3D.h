#include "Scene.h"
#include <vector>
#include "Entity.h"
#include <span>
#include "EnviromentMap.h"
#include "DirectionalLight.h"

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
			void update(Graphics::Renderer& renderer, Graphics::Camera& camera, uint32_t imageIndex, float deltaTime) override;
			void render(Graphics::Renderer& renderer, Graphics::Camera& camera, uint32_t imageIndex) override;
			void destroy(Graphics::Renderer& renderer) override;
			void input(int key, int mods, int action) override;

			void serialize(const std::string& filename) const override;	
			void deserialize(const std::string& filename) override;

			void addEntity(std::unique_ptr<Entity> entity) {
				m_entities.push_back(std::move(entity));
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

			std::span<Entity*> findEntitiesByTag(const std::string& tag) {
				std::vector<Entity*> taggedEntities;
				for (auto& entity : m_entities) {
					if (entity->hasTag(tag)) {
						taggedEntities.push_back(entity.get());
					}
				}
				return taggedEntities;
			}

			void setEnviromentMap(Graphics::EnviromentMap& enviromentMap) {
				m_enviromentMap = &enviromentMap;
			}

		private:
			std::vector<std::unique_ptr<Entity>> m_entities;
			Graphics::EnviromentMap* m_enviromentMap = nullptr;
		};
	}
}
