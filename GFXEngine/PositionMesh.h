#pragma once
#include "Mesh.h"

namespace GFXEngine {
	namespace Graphics {

		class PositionMesh : public Mesh
		{
		private:
			std::vector<GFXEngine::EngineTypes::PositionVertex> m_vertices;
			std::vector<uint32_t> m_indices;
			LibGFX::Buffer m_vertexBuffer;
			LibGFX::Buffer m_indexBuffer;

		public:
			//************************************
			// Method:    init
			// FullName:  GFXEngine::Graphics::PositionMesh::init
			// Access:    public 
			// Returns:   void
			// Qualifier:
			// Parameter: Renderer & renderer
			//************************************
			void init(Renderer& renderer) override;
			
			//************************************
			// Method:    destroy
			// FullName:  GFXEngine::Graphics::PositionMesh::destroy
			// Access:    public 
			// Returns:   void
			// Qualifier:
			// Parameter: Renderer & renderer
			//************************************
			void destroy(Renderer& renderer) override;

			//************************************
			// Method:    setVertices
			// FullName:  GFXEngine::Graphics::PositionMesh::setVertices
			// Access:    public 
			// Returns:   void
			// Qualifier:
			// Parameter: std::vector<GFXEngine::EngineTypes::PositionVertex> vertices
			//************************************
			void setVertices(std::vector<GFXEngine::EngineTypes::PositionVertex> vertices) { m_vertices = std::move(vertices); }
			
			//************************************
			// Method:    setIndices
			// FullName:  GFXEngine::Graphics::PositionMesh::setIndices
			// Access:    public 
			// Returns:   void
			// Qualifier:
			// Parameter: std::vector<uint32_t> indices
			//************************************
			void setIndices(std::vector<uint32_t> indices) { m_indices = std::move(indices); }
			
			//************************************
			// Method:    computeAABB
			// FullName:  GFXEngine::Graphics::PositionMesh::computeAABB
			// Access:    public 
			// Returns:   GFXEngine::Math::AABB
			// Qualifier: const 
			//************************************
			Math::AABB computeAABB() const override;

			//************************************
			// Method:    getVertexComponent
			// FullName:  GFXEngine::Graphics::PositionMesh::getVertexComponent
			// Access:    public 
			// Returns:   GFXEngine::EngineTypes::VertexComponentView
			// Qualifier: const 
			// Parameter: GFXEngine::EngineTypes::VertexComponent component
			//************************************
			GFXEngine::EngineTypes::VertexComponentView getVertexComponent(GFXEngine::EngineTypes::VertexComponent component) const override;
			
			//************************************
			// Method:    getVertexPointer
			// FullName:  GFXEngine::Graphics::PositionMesh::getVertexPointer
			// Access:    public 
			// Returns:   GFXEngine::Graphics::MeshVertexPointer
			// Qualifier: const 
			//************************************
			MeshVertexPointer getVertexPointer() const override;
			
			//************************************
			// Method:    getIndices
			// FullName:  GFXEngine::Graphics::PositionMesh::getIndices
			// Access:    public 
			// Returns:   std::span<const uint32_t>
			// Qualifier: const 
			//************************************
			std::span<const uint32_t> getIndices() const override;

			//************************************
			// Method:    getVertexBuffer
			// FullName:  GFXEngine::Graphics::PositionMesh::getVertexBuffer
			// Access:    public 
			// Returns:   const LibGFX::Buffer&
			// Qualifier: const 
			//************************************
			const LibGFX::Buffer& getVertexBuffer() const override;
			
			//************************************
			// Method:    getIndexBuffer
			// FullName:  GFXEngine::Graphics::PositionMesh::getIndexBuffer
			// Access:    public 
			// Returns:   const LibGFX::Buffer&
			// Qualifier: const 
			//************************************
			const LibGFX::Buffer& getIndexBuffer() const override;
			
			//************************************
			// Method:    getIndexCount
			// FullName:  GFXEngine::Graphics::PositionMesh::getIndexCount
			// Access:    public 
			// Returns:   std::size_t
			// Qualifier: const 
			//************************************
			size_t getIndexCount() const override;
		};
	}
}
