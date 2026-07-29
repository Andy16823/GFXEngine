#pragma once
#include "Entity.h"
#include "DataTypes.h"
#include "MeshAsset.h"
#include "MaterialAsset.h"

namespace GFXEngine {
	namespace Core {
		class Primitive : public Entity
		{
		private:
			EngineTypes::AssetReference m_meshReference;
			EngineTypes::AssetReference m_materialReference;
			Graphics::GraphicsPipeline* m_pipeline = nullptr;

		public:
			Primitive(Graphics::MeshAsset* mesh, Graphics::MaterialAsset* material, Graphics::GraphicsPipeline* pipeline) : m_pipeline(pipeline)
			{
				m_meshReference.set(mesh);
				m_materialReference.set(material);
			}

		public:
			void buildRenderTasks(GFXEngine::Graphics::RenderContext& context, GFXEngine::Graphics::RenderQueue& renderQueue) override;
			void getGraphicResources(GFXEngine::Graphics::GraphicResources& resources, uint32_t imageIndex) const override;
			void getMeshMaterialGraphicResources(Graphics::GraphicResources& resources, uint32_t imageIndex, size_t meshIndex) const override;
			size_t getMeshCount() const override;
			MeshMaterialPair getMeshAndMaterial(size_t index) const override;

		public:
			nlohmann::json serialize() const override;
			void deserialize(const nlohmann::json& data, GFXEngine::SerializationContext& context, GFXEngine::SerializationFlags flags = GFXEngine::SerializationFlags::None) override;
			void requireAsset(RequiredAssets& assets) override;
		};
	}
}
