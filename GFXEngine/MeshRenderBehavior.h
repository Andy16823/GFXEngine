#pragma once
#include "Behavior.h"
#include "IRenderable.h"
#include "DataTypes.h"
#include "MeshAsset.h"
#include "MaterialAsset.h"

namespace GFXEngine {
	namespace Core {
		class MeshRenderBehavior : public Behavior, public Graphics::IRenderable
		{
		private:
			EngineTypes::AssetReference m_meshRef;
			EngineTypes::AssetReference m_materialRef;
			Graphics::GraphicsPipeline* m_pipeline = nullptr;

		public:
			MeshRenderBehavior(Graphics::MeshAsset* mesh, Graphics::MaterialAsset* material, Graphics::GraphicsPipeline* pipeline)
				: m_pipeline(pipeline) 
			{
				m_materialRef.set(material);
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