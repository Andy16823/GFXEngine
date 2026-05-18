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
#include <vector>
#include "Scene.h"
#include "AABB.h"
#include "ISerializable.h"
#include <filesystem>

namespace GFXEngine {
	namespace Core {

		/// <summary>
		/// Base class for every entity in the game.
		/// </summary>
		class Entity : public GFXEngine::ISerializable
		{

		public:
			std::string name;
			std::string uuid;
			GFXEngine::Math::Transform transform;

			Entity();
			virtual ~Entity() = default;

			Entity(const Entity&) = delete; // Disable copy semantics
			Entity& operator=(const Entity&) = delete; // Disable copy semantics
			Entity(Entity&&) = default; // Allow move semantics
			Entity& operator=(Entity&&) = default; // Allow move semantics

			virtual void init(Scene& scene, GFXEngine::Graphics::Renderer& renderer);
			virtual void update(Scene& scene, GFXEngine::Graphics::Renderer& renderer, float deltaTime);
			virtual void render(Scene& scene, GFXEngine::Graphics::Renderer& renderer, GFXEngine::Graphics::Camera& camera, uint32_t imageIndex);
			virtual void destroy(Scene& scene, GFXEngine::Graphics::Renderer& renderer);

			nlohmann::json serialize() const override;
			void deserialize(const nlohmann::json& data, GFXEngine::SerializationContext& context, GFXEngine::SerializationFlags flags = GFXEngine::SerializationFlags::None) override;

			void exportToPrefab(const std::filesystem::path& path) const;

			virtual size_t getMeshCount() const = 0;
			virtual std::pair<const Graphics::Mesh&, const Graphics::Material&> getMeshAndMaterial(size_t index) const = 0;

			Math::AABB getAABB() const { return m_aabb; }
			Math::AABB getWorldAABB() const { return m_aabb.applyTransform(transform.getModelMatrix()); }
			void setAABB(const Math::AABB& aabb) { m_aabb = aabb; }

			template<typename T>
			T* as() {
				static_assert(std::is_base_of_v<Entity, T>, "T must be a subclass of Entity");
				return dynamic_cast<T*>(this);
			}

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

			void setScene(Scene* scene) {
				m_scene = scene;
			}

			Scene* getScene() const {
				return m_scene;
			}

			const std::string& getUUID() const {
				return uuid;
			}

			bool hasTag(const std::string& tag) const {
				for (const auto& t : m_tags) {
					if (t == tag) {
						return true;
					}
				}
				return false;
			}

			void addTag(const std::string& tag) {
				if (!hasTag(tag)) {
					m_tags.push_back(tag);
				}
			}

		private:
			std::vector<std::string> m_tags;
			std::vector<std::unique_ptr<Behavior>> m_behaviors;
			Math::AABB m_aabb;
			Scene* m_scene = nullptr;
			bool m_visible = true;
		};
	}
}
