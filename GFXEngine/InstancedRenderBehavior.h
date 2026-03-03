#pragma once
#include "Behavior.h"
#include "InstancedGeometryPipeline.h"
#include "Buffer.h"
#include "DataTypes.h"

namespace GFXEngine {
	namespace Core {
		/// <summary>
		/// Instanced render behavior that does nothing.
		/// </summary>
		class InstancedRenderBehavior : public Behavior {
		public:
			InstancedRenderBehavior(const Graphics::InstancedGeometryPipeline& pipeline, size_t instanceCount) 
				: m_pipeline(pipeline), m_instanceCount(instanceCount) {}

			void init(Graphics::Renderer& renderer) override;
			void update(float deltaTime) override;
			void render(Graphics::Renderer& renderer, Graphics::Camera& camera, uint32_t imageIndex) override;
			void destroy(Graphics::Renderer& renderer) override;

			void updateInstanceData(Graphics::Renderer& renderer, const EngineTypes::InstanceData& instanceData, size_t index);

		private:
			const Graphics::InstancedGeometryPipeline& m_pipeline;
			size_t m_instanceCount;
			LibGFX::Buffer m_instanceDataBuffer;
			VkDescriptorSet m_instanceDataDescriptorSet;

			std::vector<EngineTypes::InstanceData> bakeInstanceData() const;
		};
	}
}
