#pragma once
#include "Behavior.h"
#include "Buffer.h"
#include "IRenderable.h"
#include "PositionMesh.h"

namespace GFXEngine {
	namespace Core {
		class DebugBhv 
			: public Behavior, public GFXEngine::Graphics::IRenderable
		{
		private:
			std::unique_ptr<Graphics::PositionMesh> m_debugMesh;
			uint32_t m_indexCount;
			bool m_isEnabled = true;

		public:

			//************************************
			// Method:    init
			// FullName:  GFXEngine::Core::DebugBhv::init
			// Access:    public 
			// Returns:   void
			// Qualifier:
			// Parameter: Scene & scene
			// Parameter: GFXEngine::Graphics::Renderer & renderer
			//************************************
			void init(Scene& scene, GFXEngine::Graphics::Renderer& renderer) override;
			
			//************************************
			// Method:    update
			// FullName:  GFXEngine::Core::DebugBhv::update
			// Access:    public 
			// Returns:   void
			// Qualifier:
			// Parameter: Scene & scene
			// Parameter: GFXEngine::Graphics::Camera & camera
			// Parameter: float deltaTime
			//************************************
			void update(Scene& scene, GFXEngine::Graphics::Camera& camera, float deltaTime) override;
			
			//************************************
			// Method:    buildRenderTasks
			// FullName:  GFXEngine::Core::DebugBhv::buildRenderTasks
			// Access:    public 
			// Returns:   void
			// Qualifier:
			// Parameter: GFXEngine::Graphics::RenderContext & context
			// Parameter: GFXEngine::Graphics::RenderQueue & renderQueue
			//************************************
			void buildRenderTasks(GFXEngine::Graphics::RenderContext& context, GFXEngine::Graphics::RenderQueue& renderQueue) override;
			
			//************************************
			// Method:    destroy
			// FullName:  GFXEngine::Core::DebugBhv::destroy
			// Access:    public 
			// Returns:   void
			// Qualifier:
			// Parameter: Scene & scene
			// Parameter: GFXEngine::Graphics::Renderer & renderer
			//************************************
			void destroy(Scene& scene, GFXEngine::Graphics::Renderer& renderer) override;

			//************************************
			// Method:    serialize
			// FullName:  GFXEngine::Core::DebugBhv::serialize
			// Access:    public 
			// Returns:   nlohmann::json
			// Qualifier: const 
			//************************************
			nlohmann::json serialize() const override;
			
			//************************************
			// Method:    deserialize
			// FullName:  GFXEngine::Core::DebugBhv::deserialize
			// Access:    public 
			// Returns:   void
			// Qualifier:
			// Parameter: const nlohmann::json & data
			// Parameter: GFXEngine::SerializationContext & context
			// Parameter: GFXEngine::SerializationFlags flags
			//************************************
			void deserialize(const nlohmann::json& data, GFXEngine::SerializationContext& context, GFXEngine::SerializationFlags flags = GFXEngine::SerializationFlags::None) override;

			//************************************
			// Method:    getName
			// FullName:  GFXEngine::Core::DebugBhv::getName
			// Access:    public 
			// Returns:   std::string
			// Qualifier: const 
			//************************************
			std::string getName() const override { return "DebugBhv"; }
			
			//************************************
			// Method:    getProperties
			// FullName:  GFXEngine::Core::DebugBhv::getProperties
			// Access:    public 
			// Returns:   std::vector<GFXEngine::Core::PropertyInfo>
			// Qualifier:
			//************************************
			std::vector<PropertyInfo> getProperties() override;
		};
	}
}
