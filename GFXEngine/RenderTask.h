#pragma once
#include "GraphicsPipeline.h"
#include "Material.h"
#include "Mesh.h"
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

		struct DescriptorSetBinding
		{
			VkDescriptorSet descriptorSet;
			uint32_t setIndex;
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
			const GFXEngine::Graphics::Material* material = nullptr;
			const LibGFX::Buffer* vertexBuffer = nullptr;
			const LibGFX::Buffer* indexBuffer = nullptr;
			glm::mat4 modelMatrix;
			uint32_t instanceCount = 1;
			uint32_t sortingKey = 0;
			uint32_t indexCount = 0;
		};

		/// <summary>
		/// RenderTaskBuilder provides a convenient interface for constructing RenderTask instances.
		/// </summary>
		class RenderTaskBuilder {
		private:
			RenderTask m_task;

		public:
			RenderTaskBuilder& setPipeline(GFXEngine::Graphics::GraphicsPipeline* pipeline);
			RenderTaskBuilder& setMaterial(const GFXEngine::Graphics::Material* material);
			RenderTaskBuilder& setVertexBuffer(const LibGFX::Buffer& vertexBuffer);
			RenderTaskBuilder& setIndexBuffer(const LibGFX::Buffer& indexBuffer);
			RenderTaskBuilder& setBuffers(const LibGFX::Buffer& vertexBuffer, const LibGFX::Buffer& indexBuffer);
			RenderTaskBuilder& setIndexCount(uint32_t indexCount);
			RenderTaskBuilder& setMesh(const GFXEngine::Graphics::Mesh* mesh);
			RenderTaskBuilder& setModelMatrix(const glm::mat4& modelMatrix);
			RenderTaskBuilder& addDescriptorSet(const VkDescriptorSet& descriptorSet, uint32_t setIndex);
			RenderTaskBuilder& addPushConstant(const void* data, size_t size, size_t offset = 0);
			RenderTask build();
			void reset();
		};
	}
}
