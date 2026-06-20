#pragma once
#include "Entity.h"
#include "MeshModel.h"
#include "DataTypes.h"

namespace GFXEngine {
	namespace Core {

		class Model : public Entity
		{
		private:
			EngineTypes::AssetReference m_meshModelRef;

		public:
			
			//************************************
			// Method:    Model
			// FullName:  GFXEngine::Core::Model::Model
			// Access:    public 
			// Returns:   
			// Qualifier:
			//************************************
			Model() = default;
			
			//************************************
			// Method:    Model
			// FullName:  GFXEngine::Core::Model::Model
			// Access:    public 
			// Returns:   
			// Qualifier:
			// Parameter: Graphics::MeshModel * meshModel
			//************************************
			Model(Graphics::MeshModel* meshModel);

			//************************************
			// Method:    init
			// FullName:  GFXEngine::Core::Model::init
			// Access:    public 
			// Returns:   void
			// Qualifier:
			// Parameter: Scene & scene
			// Parameter: GFXEngine::Graphics::Renderer & renderer
			//************************************
			void init(Scene& scene, GFXEngine::Graphics::Renderer& renderer) override;
			
			//************************************
			// Method:    buildRenderTasks
			// FullName:  GFXEngine::Core::Model::buildRenderTasks
			// Access:    public 
			// Returns:   void
			// Qualifier:
			// Parameter: GFXEngine::Graphics::RenderContext & context
			// Parameter: GFXEngine::Graphics::RenderQueue & renderQueue
			//************************************
			void buildRenderTasks(GFXEngine::Graphics::RenderContext& context, GFXEngine::Graphics::RenderQueue& renderQueue) override;

			//************************************
			// Method:    getProperties
			// FullName:  GFXEngine::Core::Model::getProperties
			// Access:    public 
			// Returns:   std::vector<GFXEngine::Core::PropertyInfo>
			// Qualifier:
			//************************************
			std::vector<PropertyInfo> getProperties() override;
			
			//************************************
			// Method:    serialize
			// FullName:  GFXEngine::Core::Model::serialize
			// Access:    public 
			// Returns:   nlohmann::json
			// Qualifier: const 
			//************************************
			nlohmann::json serialize() const override;
			
			//************************************
			// Method:    deserialize
			// FullName:  GFXEngine::Core::Model::deserialize
			// Access:    public 
			// Returns:   void
			// Qualifier:
			// Parameter: const nlohmann::json & data
			// Parameter: GFXEngine::SerializationContext & context
			// Parameter: GFXEngine::SerializationFlags flags
			//************************************
			void deserialize(const nlohmann::json& data, GFXEngine::SerializationContext& context, GFXEngine::SerializationFlags flags = GFXEngine::SerializationFlags::None) override;

			//************************************
			// Method:    getGraphicResources
			// FullName:  GFXEngine::Core::Model::getGraphicResources
			// Access:    public 
			// Returns:   void
			// Qualifier: const 
			// Parameter: GFXEngine::Graphics::GraphicResources & resources
			// Parameter: uint32_t imageIndex
			//************************************
			void getGraphicResources(GFXEngine::Graphics::GraphicResources& resources, uint32_t imageIndex) const override;
			
			//************************************
			// Method:    getMeshMaterialGraphicResources
			// FullName:  GFXEngine::Core::Model::getMeshMaterialGraphicResources
			// Access:    public 
			// Returns:   void
			// Qualifier: const 
			// Parameter: Graphics::GraphicResources & resources
			// Parameter: uint32_t imageIndex
			// Parameter: size_t meshIndex
			//************************************
			void getMeshMaterialGraphicResources(Graphics::GraphicResources& resources, uint32_t imageIndex, size_t meshIndex) const override;

			//************************************
			// Method:    getMeshCount
			// FullName:  GFXEngine::Core::Model::getMeshCount
			// Access:    public 
			// Returns:   std::size_t
			// Qualifier: const 
			//************************************
			size_t getMeshCount() const override;

			//************************************
			// Method:    getMeshAndMaterial
			// FullName:  GFXEngine::Core::Model::getMeshAndMaterial
			// Access:    public 
			// Returns:   GFXEngine::Core::MeshMaterialPair
			// Qualifier: const 
			// Parameter: size_t index
			//************************************
			MeshMaterialPair getMeshAndMaterial(size_t index) const override;

			//************************************
			// Method:    getMeshModel
			// FullName:  GFXEngine::Core::Model::getMeshModel
			// Access:    public 
			// Returns:   const GFXEngine::Graphics::MeshModel*
			// Qualifier: const
			//************************************
			const Graphics::MeshModel* getMeshModel() const { return m_meshModelRef.get<Graphics::MeshModel>(); }
		};
	}
}