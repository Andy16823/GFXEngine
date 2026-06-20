#pragma once
#include "Renderer.h"
#include "Camera.h"
#include "ISerializable.h"
#include "PropertyInfo.h"
#include <filesystem>

namespace GFXEngine {
	namespace Core {

		class Scene : public GFXEngine::ISerializable
		{
		public:
			//************************************
			// Method:    Scene
			// FullName:  GFXEngine::Core::Scene::Scene
			// Access:    public 
			// Returns:   
			// Qualifier:
			//************************************
			Scene() = default;
			
			//************************************
			// Method:    ~Scene
			// FullName:  GFXEngine::Core::Scene::~Scene
			// Access:    virtual public 
			// Returns:   
			// Qualifier:
			//************************************
			virtual ~Scene() = default;
		public:
			//************************************
			// Method:    init
			// FullName:  GFXEngine::Core::Scene::init
			// Access:    virtual public 
			// Returns:   void
			// Qualifier:
			// Parameter: GFXEngine::Graphics::Renderer & renderer
			//************************************
			virtual void init(GFXEngine::Graphics::Renderer& renderer) = 0;
			
			//************************************
			// Method:    update
			// FullName:  GFXEngine::Core::Scene::update
			// Access:    virtual public 
			// Returns:   void
			// Qualifier:
			// Parameter: GFXEngine::Graphics::Camera & camera
			// Parameter: float deltaTime
			//************************************
			virtual void update(GFXEngine::Graphics::Camera& camera, float deltaTime) = 0;
			
			//************************************
			// Method:    beforeRender
			// FullName:  GFXEngine::Core::Scene::beforeRender
			// Access:    virtual public 
			// Returns:   void
			// Qualifier:
			// Parameter: GFXEngine::Graphics::Renderer & renderer
			// Parameter: GFXEngine::Graphics::Camera & camera
			// Parameter: uint32_t imageIndex
			//************************************
			virtual void beforeRender(GFXEngine::Graphics::Renderer& renderer, GFXEngine::Graphics::Camera& camera, uint32_t imageIndex) = 0;
			
			//************************************
			// Method:    render
			// FullName:  GFXEngine::Core::Scene::render
			// Access:    virtual public 
			// Returns:   void
			// Qualifier:
			// Parameter: GFXEngine::Graphics::Renderer & renderer
			// Parameter: GFXEngine::Graphics::Camera & camera
			// Parameter: uint32_t imageIndex
			//************************************
			virtual void render(GFXEngine::Graphics::Renderer& renderer, GFXEngine::Graphics::Camera& camera, uint32_t imageIndex) = 0;
			
			//************************************
			// Method:    afterRender
			// FullName:  GFXEngine::Core::Scene::afterRender
			// Access:    virtual public 
			// Returns:   void
			// Qualifier:
			// Parameter: GFXEngine::Graphics::Renderer & renderer
			// Parameter: GFXEngine::Graphics::Camera & camera
			// Parameter: uint32_t imageIndex
			//************************************
			virtual void afterRender(GFXEngine::Graphics::Renderer& renderer, GFXEngine::Graphics::Camera& camera, uint32_t imageIndex) = 0;
			
			//************************************
			// Method:    destroy
			// FullName:  GFXEngine::Core::Scene::destroy
			// Access:    virtual public 
			// Returns:   void
			// Qualifier:
			// Parameter: GFXEngine::Graphics::Renderer & renderer
			//************************************
			virtual void destroy(GFXEngine::Graphics::Renderer& renderer) = 0;
			
			//************************************
			// Method:    input
			// FullName:  GFXEngine::Core::Scene::input
			// Access:    virtual public 
			// Returns:   void
			// Qualifier:
			// Parameter: int key
			// Parameter: int mods
			// Parameter: int action
			//************************************
			virtual void input(int key, int mods, int action) = 0;

			//************************************
			// Method:    getProperties
			// FullName:  GFXEngine::Core::Scene::getProperties
			// Access:    virtual public 
			// Returns:   std::vector<GFXEngine::Core::PropertyInfo>
			// Qualifier:
			//************************************
			virtual std::vector<PropertyInfo> getProperties() = 0;
			
			//************************************
			// Method:    serialize
			// FullName:  GFXEngine::Core::Scene::serialize
			// Access:    virtual public 
			// Returns:   nlohmann::json
			// Qualifier: const 
			//************************************
			virtual nlohmann::json serialize() const override = 0;
			
			//************************************
			// Method:    deserialize
			// FullName:  GFXEngine::Core::Scene::deserialize
			// Access:    virtual public 
			// Returns:   void
			// Qualifier:
			// Parameter: const nlohmann::json & data
			// Parameter: GFXEngine::SerializationContext & context
			// Parameter: GFXEngine::SerializationFlags flags
			//************************************
			virtual void deserialize(const nlohmann::json& data, GFXEngine::SerializationContext& context, GFXEngine::SerializationFlags flags = GFXEngine::SerializationFlags::None) override = 0;
			
			//************************************
			// Method:    getGraphicResources
			// FullName:  GFXEngine::Core::Scene::getGraphicResources
			// Access:    virtual public 
			// Returns:   void
			// Qualifier: const
			// Parameter: GFXEngine::Graphics::GraphicResources & resources
			// Parameter: uint32_t imageIndex
			//************************************
			virtual void getGraphicResources(GFXEngine::Graphics::GraphicResources& resources, uint32_t imageIndex) const = 0;

			//************************************
			// Method:    instantiatePrefab
			// FullName:  GFXEngine::Core::Scene::instantiatePrefab
			// Access:    virtual public 
			// Returns:   class Entity*
			// Qualifier:
			// Parameter: const std::filesystem::path & path
			// Parameter: GFXEngine::SerializationContext & context
			//************************************
			virtual class Entity* instantiatePrefab(const std::filesystem::path& path, GFXEngine::SerializationContext& context) = 0;

			//************************************
			// Method:    as
			// FullName:  GFXEngine::Core::Scene::as
			// Access:    public 
			// Returns:   T*
			// Qualifier:
			//************************************
			template<typename T>
			T* as() {
				static_assert(std::is_base_of_v<Scene, T>, "T must be a subclass of Scene");
				return dynamic_cast<T*>(this);
			}
		};
	}
}
