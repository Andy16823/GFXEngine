#pragma once
#include "Entity.h"
#include "MeshModel.h"
#include "InstancedGeometryPipeline.h"
#include "Buffer.h"
#include <vector>
#include "DataTypes.h"

namespace GFXEngine {
	namespace Core {
		class InstancedModel : public Entity
		{
		public:
			InstancedModel(const Graphics::MeshModel& meshModel, const Graphics::InstancedGeometryPipeline& pipeline, size_t instanceCount) 
				: m_meshModel(meshModel), m_pipeline(pipeline), m_instanceCount(instanceCount) {
			}

			void render(Scene& scene, GFXEngine::Graphics::Renderer& renderer, GFXEngine::Graphics::Camera& camera, uint32_t imageIndex) override;
			void init(Scene& scene, GFXEngine::Graphics::Renderer& renderer) override;
			void destroy(Scene& scene, GFXEngine::Graphics::Renderer& renderer) override;
			void updateInstance(Graphics::Renderer& renderer, const EngineTypes::InstanceData& instanceData, size_t index);
			void updateInstanceRange(Graphics::Renderer& renderer, const std::span<const EngineTypes::InstanceData>& instanceData, size_t startIndex);

			size_t getMeshCount() const override;
			std::pair<const Graphics::Mesh&, const Graphics::Material&> getMeshAndMaterial(size_t index) const override;
		private:
			const Graphics::MeshModel& m_meshModel;
			const Graphics::InstancedGeometryPipeline& m_pipeline;
			size_t m_instanceCount = 0;

			VkDescriptorSet m_instanceDataDescriptorSet = VK_NULL_HANDLE;
			LibGFX::Buffer m_instanceDataBuffer;
			void* m_mappedInstanceData = nullptr;

			std::vector<EngineTypes::InstanceData> bakeInstanceData() const;
		};
	}
}
