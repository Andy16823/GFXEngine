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

		enum class RenderLayer {
			Opaque,
			Skybox,
			Transparent,
		};

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

		class RenderTaskBuilder {
		private:
			bool m_hasModelMatrix = false;
			RenderTask m_task;

		public:
			//************************************
			// Method:    hasModelMatrix
			// FullName:  GFXEngine::Graphics::RenderTaskBuilder::hasModelMatrix
			// Access:    public 
			// Returns:   bool
			// Qualifier: const
			//************************************
			bool hasModelMatrix() const
			{
				return m_hasModelMatrix;
			}

			//************************************
			// Method:    getModelMatrix
			// FullName:  GFXEngine::Graphics::RenderTaskBuilder::getModelMatrix
			// Access:    public 
			// Returns:   glm::mat4
			// Qualifier: const
			//************************************
			glm::mat4 getModelMatrix() const 
			{ 
				return m_task.modelMatrix; 
			}

			//************************************
			// Method:    setPipeline
			// FullName:  GFXEngine::Graphics::RenderTaskBuilder::setPipeline
			// Access:    public 
			// Returns:   GFXEngine::Graphics::RenderTaskBuilder&
			// Qualifier:
			// Parameter: GFXEngine::Graphics::GraphicsPipeline * pipeline
			//************************************
			RenderTaskBuilder& setPipeline(GFXEngine::Graphics::GraphicsPipeline* pipeline);
			
			//************************************
			// Method:    setVertexBuffer
			// FullName:  GFXEngine::Graphics::RenderTaskBuilder::setVertexBuffer
			// Access:    public 
			// Returns:   GFXEngine::Graphics::RenderTaskBuilder&
			// Qualifier:
			// Parameter: const LibGFX::Buffer & vertexBuffer
			//************************************
			RenderTaskBuilder& setVertexBuffer(const LibGFX::Buffer& vertexBuffer);
			
			//************************************
			// Method:    setIndexBuffer
			// FullName:  GFXEngine::Graphics::RenderTaskBuilder::setIndexBuffer
			// Access:    public 
			// Returns:   GFXEngine::Graphics::RenderTaskBuilder&
			// Qualifier:
			// Parameter: const LibGFX::Buffer & indexBuffer
			//************************************
			RenderTaskBuilder& setIndexBuffer(const LibGFX::Buffer& indexBuffer);
			
			//************************************
			// Method:    setBuffers
			// FullName:  GFXEngine::Graphics::RenderTaskBuilder::setBuffers
			// Access:    public 
			// Returns:   GFXEngine::Graphics::RenderTaskBuilder&
			// Qualifier:
			// Parameter: const LibGFX::Buffer & vertexBuffer
			// Parameter: const LibGFX::Buffer & indexBuffer
			//************************************
			RenderTaskBuilder& setBuffers(const LibGFX::Buffer& vertexBuffer, const LibGFX::Buffer& indexBuffer);
			
			//************************************
			// Method:    setIndexCount
			// FullName:  GFXEngine::Graphics::RenderTaskBuilder::setIndexCount
			// Access:    public 
			// Returns:   GFXEngine::Graphics::RenderTaskBuilder&
			// Qualifier:
			// Parameter: uint32_t indexCount
			//************************************
			RenderTaskBuilder& setIndexCount(uint32_t indexCount);
			
			//************************************
			// Method:    setMesh
			// FullName:  GFXEngine::Graphics::RenderTaskBuilder::setMesh
			// Access:    public 
			// Returns:   GFXEngine::Graphics::RenderTaskBuilder&
			// Qualifier:
			// Parameter: const GFXEngine::Graphics::Mesh * mesh
			//************************************
			RenderTaskBuilder& setMesh(const GFXEngine::Graphics::Mesh* mesh);
			
			//************************************
			// Method:    setModelMatrix
			// FullName:  GFXEngine::Graphics::RenderTaskBuilder::setModelMatrix
			// Access:    public 
			// Returns:   GFXEngine::Graphics::RenderTaskBuilder&
			// Qualifier:
			// Parameter: const glm::mat4 & modelMatrix
			//************************************
			RenderTaskBuilder& setModelMatrix(const glm::mat4& modelMatrix);
			//************************************
			// Method:    addDescriptorSet
			// FullName:  GFXEngine::Graphics::RenderTaskBuilder::addDescriptorSet
			// Access:    public 
			// Returns:   GFXEngine::Graphics::RenderTaskBuilder&
			// Qualifier:
			// Parameter: const VkDescriptorSet & descriptorSet
			// Parameter: uint32_t setIndex
			//************************************
			RenderTaskBuilder& addDescriptorSet(const VkDescriptorSet& descriptorSet, uint32_t setIndex);
			
			//************************************
			// Method:    addPushConstant
			// FullName:  GFXEngine::Graphics::RenderTaskBuilder::addPushConstant
			// Access:    public 
			// Returns:   GFXEngine::Graphics::RenderTaskBuilder&
			// Qualifier:
			// Parameter: const void * data
			// Parameter: size_t size
			// Parameter: size_t offset
			//************************************
			RenderTaskBuilder& addPushConstant(const void* data, size_t size, size_t offset = 0);
			
			//************************************
			// Method:    setInstanceCount
			// FullName:  GFXEngine::Graphics::RenderTaskBuilder::setInstanceCount
			// Access:    public 
			// Returns:   GFXEngine::Graphics::RenderTaskBuilder&
			// Qualifier:
			// Parameter: uint32_t instanceCount
			//************************************
			RenderTaskBuilder& setInstanceCount(uint32_t instanceCount);
			
			//************************************
			// Method:    setRenderLayer
			// FullName:  GFXEngine::Graphics::RenderTaskBuilder::setRenderLayer
			// Access:    public 
			// Returns:   GFXEngine::Graphics::RenderTaskBuilder&
			// Qualifier:
			// Parameter: RenderLayer layer
			//************************************
			RenderTaskBuilder& setRenderLayer(RenderLayer layer);
			
			//************************************
			// Method:    build
			// FullName:  GFXEngine::Graphics::RenderTaskBuilder::build
			// Access:    public 
			// Returns:   GFXEngine::Graphics::RenderTask
			// Qualifier:
			//************************************
			RenderTask build();
			
			//************************************
			// Method:    reset
			// FullName:  GFXEngine::Graphics::RenderTaskBuilder::reset
			// Access:    public 
			// Returns:   void
			// Qualifier:
			//************************************
			void reset();
		};
	}
}
