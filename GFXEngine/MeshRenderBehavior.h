#pragma once
#include "Behavior.h"
#include "IRenderable.h"
#include "DataTypes.h"
#include "MeshAsset.h"

namespace GFXEngine {
	namespace Core {
		class MeshRenderBehavior : public Behavior, public Graphics::IRenderable
		{
		private:
			EngineTypes::AssetReference m_meshRef;
			Graphics::Material* m_material = nullptr;
			Graphics::GraphicsPipeline* m_pipeline = nullptr;

		public:
			MeshRenderBehavior(Graphics::MeshAsset* mesh, Graphics::Material* material, Graphics::GraphicsPipeline* pipeline)
				: m_material(material), m_pipeline(pipeline) 
			{
				m_meshRef.set(mesh);
			}

		public:
			// Geerbt über Behavior
			void init(Scene& scene, Graphics::Renderer& renderer) override;
			void update(Scene& scene, Graphics::Camera& camera, float deltaTime) override;
			void destroy(Scene& scene, Graphics::Renderer& renderer) override;
			std::string getName() const override;
			std::vector<PropertyInfo> getProperties() override;

		public:
			// Geerbt über IRenderable
			void buildRenderTasks(Graphics::RenderContext& context, Graphics::RenderQueue& renderQueue) override;
		};
	}
}