#pragma once
#include "Entity.h"
#include "DataTypes.h"
#include "MeshAsset.h"
#include "MaterialAsset.h"
#include "Asset.h"

#include <optional>

namespace GFXEngine {
	namespace Core {

		/// <summary>
		/// Primitive is a type of Entity that represents a basic geometric shape or object in the scene. 
		/// It is associated with a mesh and a material, which define its appearance and rendering properties. 
		/// The Primitive class provides functionality to manage its properties, 
		/// build render tasks, and handle serialization and deserialization.
		/// </summary>
		class Primitive 
			: public Entity
		{
		private:
			std::optional<GFXEngine::AssetHandle> m_meshReference = std::nullopt;
			std::optional<GFXEngine::AssetHandle> m_materialReference = std::nullopt;
			std::optional<unsigned int> m_pipelineId = std::nullopt;

		public:
			Primitive() = default;
			Primitive(GFXEngine::AssetHandle mesh, GFXEngine::AssetHandle material, unsigned int pipeline) 
				: m_meshReference(mesh), m_materialReference(material), m_pipelineId(pipeline) {}

		public:
			virtual std::vector<PropertyInfo> getProperties() override;
			void buildRenderTasks(GFXEngine::Graphics::RenderContext& context, GFXEngine::Graphics::RenderQueue& renderQueue) override;
			void getGraphicResources(GFXEngine::Graphics::GraphicResources& resources, uint32_t imageIndex) const override;
			void getMeshMaterialGraphicResources(Graphics::GraphicResources& resources, uint32_t imageIndex, size_t meshIndex) const override;
			size_t getMeshCount() const override;
			MeshMaterialPair getMeshAndMaterial(size_t index) const override;

		public:
			nlohmann::json serialize() const override;
			void deserialize(const nlohmann::json& data, GFXEngine::SerializationContext& context, GFXEngine::SerializationFlags flags = GFXEngine::SerializationFlags::None) override;
		};
	}
}
