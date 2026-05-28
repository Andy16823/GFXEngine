#pragma once
#include "GraphicsPipeline.h"
#include "Mesh3D.h"
#include "glm/glm.hpp"
#include "Buffer.h"
#include <vector>

namespace GFXEngine
{
	namespace Graphics
	{
		/// <summary>
		/// Push constant data structure to hold information about the data to be pushed, 
		/// its size, and offset within the push constant range.
		/// </summary>
		struct PushConstant 
		{
			std::vector<uint8_t> data;
			size_t size;
			size_t offset;
		};

		/// <summary>
		/// Structure to represent a descriptor set binding, which includes the descriptor set 
		/// handle and the set index it should be bound to in the pipeline layout.
		/// </summary>
		struct DescriptorSetBinding
		{
			VkDescriptorSet descriptorSet;
			uint32_t setIndex;
		};

		/// <summary>
		/// RenderLayer enum defines the different layers in which render tasks can be categorized.
		/// </summary>
		enum class RenderLayer {
			Opaque,
			Skybox,
			Transparent,
		};

		/// <summary>
		/// RenderTask encapsulates all the necessary information to execute a draw call, 
		/// including the graphics pipeline, material, mesh, model matrix, descriptor sets, and push constants.
		/// </summary>
		struct RenderTask
		{
			std::vector<DescriptorSetBinding> descriptorSets;
			std::vector<PushConstant> pushConstants;

			GFXEngine::Graphics::GraphicsPipeline* pipeline = nullptr;
			const LibGFX::Buffer* vertexBuffer = nullptr;
			const LibGFX::Buffer* indexBuffer = nullptr;
			glm::mat4 modelMatrix;
			uint32_t instanceCount = 1;
			uint32_t sortingKey = 0;
			uint32_t indexCount = 0;
			RenderLayer layer = RenderLayer::Opaque;
		};

		/// <summary>
		/// RenderTaskBuilder provides a convenient interface for constructing RenderTask instances.
		/// </summary>
		class RenderTaskBuilder {
		private:
			RenderTask m_task;

		public:
			RenderTaskBuilder& setPipeline(GFXEngine::Graphics::GraphicsPipeline* pipeline);
			RenderTaskBuilder& setVertexBuffer(const LibGFX::Buffer& vertexBuffer);
			RenderTaskBuilder& setIndexBuffer(const LibGFX::Buffer& indexBuffer);
			RenderTaskBuilder& setBuffers(const LibGFX::Buffer& vertexBuffer, const LibGFX::Buffer& indexBuffer);
			RenderTaskBuilder& setIndexCount(uint32_t indexCount);
			RenderTaskBuilder& setMesh(const GFXEngine::Graphics::Mesh3D* mesh);
			RenderTaskBuilder& setModelMatrix(const glm::mat4& modelMatrix);
			RenderTaskBuilder& addDescriptorSet(const VkDescriptorSet& descriptorSet, uint32_t setIndex);
			RenderTaskBuilder& addPushConstant(const void* data, size_t size, size_t offset = 0);
			RenderTaskBuilder& setInstanceCount(uint32_t instanceCount);
			RenderTaskBuilder& setRenderLayer(RenderLayer layer);
			RenderTask build();
			void reset();
		};
	}
}
