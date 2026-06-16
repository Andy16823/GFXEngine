#pragma once
#include "Entity.h"
#include "MeshModel.h"
#include "Asset.h"

namespace GFXEngine {
	namespace Core {

		/// <summary>
		/// Model entity that represents a 3D mesh model in the scene.
		/// </summary>
		class Model : public Entity
		{
		private:
			GFXEngine::AssetHandle<Graphics::MeshModel> m_meshModelRef;

		public:
			Model() = default;
			Model(GFXEngine::AssetHandle<Graphics::MeshModel> meshModelRef);

			void init(Scene& scene, GFXEngine::Graphics::Renderer& renderer) override;
			void buildRenderTasks(GFXEngine::Graphics::RenderContext& context, GFXEngine::Graphics::RenderQueue& renderQueue) override;

			std::vector<PropertyInfo> getProperties() override;
			nlohmann::json serialize() const override;
			void deserialize(const nlohmann::json& data, GFXEngine::SerializationContext& context, GFXEngine::SerializationFlags flags = GFXEngine::SerializationFlags::None) override;

			void getGraphicResources(GFXEngine::Graphics::GraphicResources& resources, uint32_t imageIndex) const override;
			void getMeshMaterialGraphicResources(Graphics::GraphicResources& resources, uint32_t imageIndex, size_t meshIndex) const override;

			size_t getMeshCount() const override;
			MeshMaterialPair getMeshAndMaterial(size_t index) const override;
		};
	}
}