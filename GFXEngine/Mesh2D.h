#pragma once
#include "Mesh.h"
#include "Buffer.h"
#include "EngineDefinitions.h"

namespace GFXEngine {
	namespace Graphics {

		class Mesh2D : public Mesh
		{
		private:
			LibGFX::Buffer m_vertexBuffer;
			LibGFX::Buffer m_indexBuffer;

			std::vector<GFXEngine::EngineTypes::Vertex2D> m_vertices;
			std::vector<uint32_t> m_indices;

		public:
			//************************************
			// Method:    init
			// FullName:  GFXEngine::Graphics::Mesh2D::init
			// Access:    public 
			// Returns:   void
			// Qualifier:
			// Parameter: Renderer & renderer
			//************************************
			void init(Renderer& renderer) override;
			
			//************************************
			// Method:    destroy
			// FullName:  GFXEngine::Graphics::Mesh2D::destroy
			// Access:    public 
			// Returns:   void
			// Qualifier:
			// Parameter: Renderer & renderer
			//************************************
			void destroy(Renderer& renderer) override;
			
			//************************************
			// Method:    computeAABB
			// FullName:  GFXEngine::Graphics::Mesh2D::computeAABB
			// Access:    public 
			// Returns:   GFXEngine::Math::AABB
			// Qualifier: const 
			//************************************
			Math::AABB computeAABB() const override;

			//************************************
			// Method:    setVertices
			// FullName:  GFXEngine::Graphics::Mesh2D::setVertices
			// Access:    public 
			// Returns:   void
			// Qualifier:
			// Parameter: std::vector<GFXEngine::EngineTypes::Vertex2D> vertices
			//************************************
			void setVertices(std::vector<GFXEngine::EngineTypes::Vertex2D> vertices) { m_vertices = std::move(vertices); }
			
			//************************************
			// Method:    setIndices
			// FullName:  GFXEngine::Graphics::Mesh2D::setIndices
			// Access:    public 
			// Returns:   void
			// Qualifier:
			// Parameter: std::vector<uint32_t> indices
			//************************************
			void setIndices(std::vector<uint32_t> indices) { m_indices = std::move(indices); }

			//************************************
			// Method:    getVertexBuffer
			// FullName:  GFXEngine::Graphics::Mesh2D::getVertexBuffer
			// Access:    public 
			// Returns:   const LibGFX::Buffer&
			// Qualifier: const 
			//************************************
			const LibGFX::Buffer& getVertexBuffer() const override;
			
			//************************************
			// Method:    getIndexBuffer
			// FullName:  GFXEngine::Graphics::Mesh2D::getIndexBuffer
			// Access:    public 
			// Returns:   const LibGFX::Buffer&
			// Qualifier: const 
			//************************************
			const LibGFX::Buffer& getIndexBuffer() const override;
			
			//************************************
			// Method:    getIndexCount
			// FullName:  GFXEngine::Graphics::Mesh2D::getIndexCount
			// Access:    public 
			// Returns:   std::size_t
			// Qualifier: const 
			//************************************
			size_t getIndexCount() const override;

			//************************************
			// Method:    getVertexComponent
			// FullName:  GFXEngine::Graphics::Mesh2D::getVertexComponent
			// Access:    public 
			// Returns:   GFXEngine::EngineTypes::VertexComponentView
			// Qualifier: const 
			// Parameter: GFXEngine::EngineTypes::VertexComponent component
			//************************************
			GFXEngine::EngineTypes::VertexComponentView getVertexComponent(GFXEngine::EngineTypes::VertexComponent component) const override;
			
			//************************************
			// Method:    getVertexPointer
			// FullName:  GFXEngine::Graphics::Mesh2D::getVertexPointer
			// Access:    public 
			// Returns:   GFXEngine::Graphics::MeshVertexPointer
			// Qualifier: const 
			//************************************
			MeshVertexPointer getVertexPointer() const override;
			
			//************************************
			// Method:    getIndices
			// FullName:  GFXEngine::Graphics::Mesh2D::getIndices
			// Access:    public 
			// Returns:   std::span<const uint32_t>
			// Qualifier: const 
			//************************************
			std::span<const uint32_t> getIndices() const override;
		};
	}
}