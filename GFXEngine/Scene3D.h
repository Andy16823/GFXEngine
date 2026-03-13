#include "Scene.h"
#include <vector>
#include "Entity.h"

#pragma once
namespace GFXEngine {
	namespace Core {
		class Scene3D : public Scene
		{
		public:
			Scene3D() = default;
			virtual ~Scene3D() = default;
			void init(Graphics::Renderer& renderer) override;
			void update(Graphics::Renderer& renderer, Graphics::Camera& camera, uint32_t imageIndex, float deltaTime) override;
			void render(Graphics::Renderer& renderer, Graphics::Camera& camera, uint32_t imageIndex) override;
			void destroy(Graphics::Renderer& renderer) override;
			void input(int key, int mods, int action) override;

			void addEntity(std::unique_ptr<Entity> entity) {
				m_entities.push_back(std::move(entity));
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

		private:
			std::vector<std::unique_ptr<Entity>> m_entities;
		};
	}
}
