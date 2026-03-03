#pragma once
#include "Transform.h"
#include "Renderer.h"
#include "Camera.h"
#include "Behavior.h"
#include <vector>
#include <memory>
#include <stdexcept>
#include <utility>
#include "Material.h"
#include "Mesh.h"
#include "Pipeline.h"

namespace GFXEngine {
	namespace Core {

		/// <summary>
		/// Basic entity class that can have multiple behaviors attached to it. 
		/// Each behavior can define its own logic for initialization, updating, 
		/// rendering, and destruction. The entity itself holds a transform 
		/// for position, rotation, and scale, and a visibility flag. 
		/// Behaviors can be added and retrieved using template functions that ensure type safety.
		/// </summary>
		class Entity
		{
		private:
			std::vector<std::unique_ptr<Behavior>> m_behaviors;
			bool m_visible = true;

		public:
			GFXEngine::Math::Transform transform;

			Entity() = default;
			virtual ~Entity() = default;

			Entity(const Entity&) = delete; // Disable copy semantics
			Entity& operator=(const Entity&) = delete; // Disable copy semantics
			Entity(Entity&&) = default; // Allow move semantics
			Entity& operator=(Entity&&) = default; // Allow move semantics

			virtual void init(GFXEngine::Graphics::Renderer& renderer);
			virtual void update(float deltaTime);
			virtual void render(GFXEngine::Graphics::Renderer& renderer, GFXEngine::Graphics::Camera& camera, uint32_t imageIndex);
			virtual void destroy(GFXEngine::Graphics::Renderer& renderer);

			virtual size_t getMeshCount() const = 0;
			virtual std::pair<const Graphics::Mesh&, const Graphics::Material&> getMeshAndMaterial(size_t index) const = 0;

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
				throw std::runtime_error("Behavior not found");
			}

			bool isVisible() const { return m_visible; }
			void setVisible(bool visible) { m_visible = visible; }
		};
	}
}
