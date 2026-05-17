#pragma once
#include "Renderer.h"
#include "Camera.h"
#include "ISerializable.h"
#include <filesystem>

namespace GFXEngine {
	namespace Core {

		struct RenderInjections {
			std::function<void(class Scene&, GFXEngine::Graphics::Renderer&, GFXEngine::Graphics::Camera&, uint32_t)> beforeRender;
			std::function<void(class Scene&, class Entity&, GFXEngine::Graphics::Renderer&, GFXEngine::Graphics::Camera&, uint32_t)> onEntityRender;
			std::function<void(class Scene&, GFXEngine::Graphics::Renderer&, GFXEngine::Graphics::Camera&, uint32_t)> beforeEnvironment;
			std::function<void(class Scene&, GFXEngine::Graphics::Renderer&, GFXEngine::Graphics::Camera&, uint32_t)> afterEnvironment;
			std::function<void(class Scene&, GFXEngine::Graphics::Renderer&, GFXEngine::Graphics::Camera&, uint32_t)> afterRender;
		};


		class Scene : public GFXEngine::ISerializable
		{
		public:
			Scene() = default;
			virtual ~Scene() = default;
			virtual void init(GFXEngine::Graphics::Renderer& renderer) = 0;
			virtual void update(GFXEngine::Graphics::Renderer& renderer, GFXEngine::Graphics::Camera& camera, uint32_t imageIndex, float deltaTime) = 0;
			virtual void render(GFXEngine::Graphics::Renderer& renderer, GFXEngine::Graphics::Camera& camera, uint32_t imageIndex, const RenderInjections* injections = nullptr) = 0;
			virtual void destroy(GFXEngine::Graphics::Renderer& renderer) = 0;
			virtual void input(int key, int mods, int action) = 0;

			virtual nlohmann::json serialize() const override = 0;
			virtual void deserialize(const nlohmann::json& data, GFXEngine::SerializationContext& context, GFXEngine::SerializationFlags flags = GFXEngine::SerializationFlags::None) override = 0;

			virtual class Entity* instantiatePrefab(const std::filesystem::path& path, GFXEngine::SerializationContext& context) = 0;

			template<typename T>
			T* as() {
				static_assert(std::is_base_of_v<Scene, T>, "T must be a subclass of Scene");
				return dynamic_cast<T*>(this);
			}
		};
	}
}
