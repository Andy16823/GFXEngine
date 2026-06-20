#pragma once
#include "Entity.h"
#include "MeshModel.h"
#include "Buffer.h"
#include <vector>
#include "DataTypes.h"
#include "AABB.h"

namespace GFXEngine {
	namespace Core {

		class InstanceHandle;

		class InstancedModel : public Entity
		{
		private:
			std::vector<EngineTypes::InstanceData> m_instanceData;
			EngineTypes::AssetReference m_meshModelRef;
			bool m_isDirty = true;

			VkDescriptorSet m_instanceDataDescriptorSet = VK_NULL_HANDLE;
			LibGFX::Buffer m_instanceDataBuffer;
			void* m_mappedInstanceData = nullptr;

		public:
			//************************************
			// Method:    InstancedModel
			// FullName:  GFXEngine::Core::InstancedModel::InstancedModel
			// Access:    public 
			// Returns:   
			// Qualifier:
			//************************************
			InstancedModel() = default;
			
			//************************************
			// Method:    InstancedModel
			// FullName:  GFXEngine::Core::InstancedModel::InstancedModel
			// Access:    public 
			// Returns:   
			// Qualifier:
			// Parameter: Graphics::MeshModel * meshModel
			// Parameter: size_t instanceCount
			//************************************
			InstancedModel(Graphics::MeshModel* meshModel, size_t instanceCount);

			//************************************
			// Method:    init
			// FullName:  GFXEngine::Core::InstancedModel::init
			// Access:    public 
			// Returns:   void
			// Qualifier:
			// Parameter: Scene & scene
			// Parameter: GFXEngine::Graphics::Renderer & renderer
			//************************************
			void init(Scene& scene, GFXEngine::Graphics::Renderer& renderer) override;
			
			//************************************
			// Method:    buildRenderTasks
			// FullName:  GFXEngine::Core::InstancedModel::buildRenderTasks
			// Access:    public 
			// Returns:   void
			// Qualifier:
			// Parameter: GFXEngine::Graphics::RenderContext & context
			// Parameter: GFXEngine::Graphics::RenderQueue & renderQueue
			//************************************
			void buildRenderTasks(GFXEngine::Graphics::RenderContext& context, GFXEngine::Graphics::RenderQueue& renderQueue) override;
			
			//************************************
			// Method:    destroy
			// FullName:  GFXEngine::Core::InstancedModel::destroy
			// Access:    public 
			// Returns:   void
			// Qualifier:
			// Parameter: Scene & scene
			// Parameter: GFXEngine::Graphics::Renderer & renderer
			//************************************
			void destroy(Scene& scene, GFXEngine::Graphics::Renderer& renderer) override;
			
			//************************************
			// Method:    updateInstance
			// FullName:  GFXEngine::Core::InstancedModel::updateInstance
			// Access:    public 
			// Returns:   void
			// Qualifier:
			// Parameter: const EngineTypes::InstanceData & instanceData
			// Parameter: size_t index
			//************************************
			void updateInstance(const EngineTypes::InstanceData& instanceData, size_t index);
			
			//************************************
			// Method:    updateInstanceRange
			// FullName:  GFXEngine::Core::InstancedModel::updateInstanceRange
			// Access:    public 
			// Returns:   void
			// Qualifier:
			// Parameter: const std::span<const EngineTypes::InstanceData> & instanceData
			// Parameter: size_t startIndex
			//************************************
			void updateInstanceRange(const std::span<const EngineTypes::InstanceData>& instanceData, size_t startIndex);
			
			//************************************
			// Method:    instantiate
			// FullName:  GFXEngine::Core::InstancedModel::instantiate
			// Access:    public 
			// Returns:   std::unique_ptr<GFXEngine::Core::InstanceHandle>
			// Qualifier:
			// Parameter: const std::string & name
			//************************************
			std::unique_ptr<InstanceHandle> instantiate(const std::string& name);
			
			//************************************
			// Method:    instantiate
			// FullName:  GFXEngine::Core::InstancedModel::instantiate
			// Access:    public 
			// Returns:   std::unique_ptr<GFXEngine::Core::InstanceHandle>
			// Qualifier:
			// Parameter: const std::string & name
			// Parameter: size_t instanceIndex
			//************************************
			std::unique_ptr<InstanceHandle> instantiate(const std::string& name, size_t instanceIndex);

			//************************************
			// Method:    getProperties
			// FullName:  GFXEngine::Core::InstancedModel::getProperties
			// Access:    public 
			// Returns:   std::vector<GFXEngine::Core::PropertyInfo>
			// Qualifier:
			//************************************
			std::vector<PropertyInfo> getProperties() override;
			
			//************************************
			// Method:    serialize
			// FullName:  GFXEngine::Core::InstancedModel::serialize
			// Access:    public 
			// Returns:   nlohmann::json
			// Qualifier: const 
			//************************************
			nlohmann::json serialize() const override;
			
			//************************************
			// Method:    deserialize
			// FullName:  GFXEngine::Core::InstancedModel::deserialize
			// Access:    public 
			// Returns:   void
			// Qualifier:
			// Parameter: const nlohmann::json & data
			// Parameter: GFXEngine::SerializationContext & context
			// Parameter: GFXEngine::SerializationFlags flags
			//************************************
			void deserialize(const nlohmann::json& data, GFXEngine::SerializationContext& context, GFXEngine::SerializationFlags flags = GFXEngine::SerializationFlags::None) override;
			
			//************************************
			// Method:    getMeshCount
			// FullName:  GFXEngine::Core::InstancedModel::getMeshCount
			// Access:    public 
			// Returns:   std::size_t
			// Qualifier: const 
			//************************************
			size_t getMeshCount() const override;
			
			//************************************
			// Method:    getMeshAndMaterial
			// FullName:  GFXEngine::Core::InstancedModel::getMeshAndMaterial
			// Access:    public 
			// Returns:   GFXEngine::Core::MeshMaterialPair
			// Qualifier: const 
			// Parameter: size_t index
			//************************************
			MeshMaterialPair getMeshAndMaterial(size_t index) const override;
			
			//************************************
			// Method:    getGraphicResources
			// FullName:  GFXEngine::Core::InstancedModel::getGraphicResources
			// Access:    public 
			// Returns:   void
			// Qualifier: const 
			// Parameter: GFXEngine::Graphics::GraphicResources & resources
			// Parameter: uint32_t imageIndex
			//************************************
			void getGraphicResources(GFXEngine::Graphics::GraphicResources& resources, uint32_t imageIndex) const override;
			
			//************************************
			// Method:    getMeshMaterialGraphicResources
			// FullName:  GFXEngine::Core::InstancedModel::getMeshMaterialGraphicResources
			// Access:    public 
			// Returns:   void
			// Qualifier: const 
			// Parameter: Graphics::GraphicResources & resources
			// Parameter: uint32_t imageIndex
			// Parameter: size_t meshIndex
			//************************************
			void getMeshMaterialGraphicResources(Graphics::GraphicResources& resources, uint32_t imageIndex, size_t meshIndex) const override;

			//************************************
			// Method:    getInstanceCount
			// FullName:  GFXEngine::Core::InstancedModel::getInstanceCount
			// Access:    public 
			// Returns:   std::size_t
			// Qualifier: const
			//************************************
			size_t getInstanceCount() const { return m_instanceData.size(); }
			
			//************************************
			// Method:    computeInstanceAABB
			// FullName:  GFXEngine::Core::InstancedModel::computeInstanceAABB
			// Access:    public 
			// Returns:   GFXEngine::Math::AABB
			// Qualifier: const
			// Parameter: size_t instanceIndex
			//************************************
			GFXEngine::Math::AABB computeInstanceAABB(size_t instanceIndex) const;
			
			//************************************
			// Method:    isInstanceVisible
			// FullName:  GFXEngine::Core::InstancedModel::isInstanceVisible
			// Access:    public 
			// Returns:   bool
			// Qualifier: const
			// Parameter: size_t instanceIndex
			//************************************
			bool isInstanceVisible(size_t instanceIndex) const;
			
			//************************************
			// Method:    hideInstance
			// FullName:  GFXEngine::Core::InstancedModel::hideInstance
			// Access:    public 
			// Returns:   void
			// Qualifier:
			// Parameter: size_t instanceIndex
			//************************************
			void hideInstance(size_t instanceIndex);
			
			//************************************
			// Method:    showInstance
			// FullName:  GFXEngine::Core::InstancedModel::showInstance
			// Access:    public 
			// Returns:   void
			// Qualifier:
			// Parameter: size_t instanceIndex
			//************************************
			void showInstance(size_t instanceIndex);
			
			//************************************
			// Method:    setInstanceModelMatrix
			// FullName:  GFXEngine::Core::InstancedModel::setInstanceModelMatrix
			// Access:    public 
			// Returns:   void
			// Qualifier:
			// Parameter: size_t instanceIndex
			// Parameter: const glm::mat4 & modelMatrix
			//************************************
			void setInstanceModelMatrix(size_t instanceIndex, const glm::mat4& modelMatrix);
			
			//************************************
			// Method:    findNextFreeInstance
			// FullName:  GFXEngine::Core::InstancedModel::findNextFreeInstance
			// Access:    public 
			// Returns:   std::size_t
			// Qualifier: const
			//************************************
			size_t findNextFreeInstance() const;
			
			//************************************
			// Method:    getInstanceModelMatrix
			// FullName:  GFXEngine::Core::InstancedModel::getInstanceModelMatrix
			// Access:    public 
			// Returns:   glm::mat4
			// Qualifier: const
			// Parameter: size_t instanceIndex
			//************************************
			glm::mat4 getInstanceModelMatrix(size_t instanceIndex) const;
		};
	}
}
