#pragma once
#include "DataTypes.h"
#include "Renderer.h"
#include "Mesh.h"
#include "Buffer.h"
#include <vector>
#include "AABB.h"

namespace GFXEngine {
	namespace Graphics {

		class Mesh3D : public Mesh{
		private:
			std::vector<EngineTypes::Vertex3D> m_vertices;
			std::vector<uint32_t> m_indices;
			LibGFX::Buffer m_vertexBuffer;
			LibGFX::Buffer m_indexBuffer;

		public:
			//************************************
			// Method:    Mesh3D
			// FullName:  GFXEngine::Graphics::Mesh3D::Mesh3D
			// Access:    public 
			// Returns:   
			// Qualifier:
			//************************************
			Mesh3D() = default;
			
			//************************************
			// Method:    Mesh3D
			// FullName:  GFXEngine::Graphics::Mesh3D::Mesh3D
			// Access:    public 
			// Returns:   
			// Qualifier:
			// Parameter: const Mesh3D &
			//************************************
			Mesh3D(const Mesh3D&) = delete;
			
			//************************************
			// Method:    operator=
			// FullName:  GFXEngine::Graphics::Mesh3D::operator=
			// Access:    public 
			// Returns:   GFXEngine::Graphics::Mesh3D&
			// Qualifier: = delete
			// Parameter: const Mesh3D &
			//************************************
			Mesh3D& operator=(const Mesh3D&) = delete;
			
			//************************************
			// Method:    Mesh3D
			// FullName:  GFXEngine::Graphics::Mesh3D::Mesh3D
			// Access:    public 
			// Returns:   
			// Qualifier:
			// Parameter: Mesh3D & &
			//************************************
			Mesh3D(Mesh3D&&) = default;
			
			//************************************
			// Method:    operator=
			// FullName:  GFXEngine::Graphics::Mesh3D::operator=
			// Access:    public 
			// Returns:   GFXEngine::Graphics::Mesh3D&
			// Qualifier: = default
			// Parameter: Mesh3D & &
			//************************************
			Mesh3D& operator=(Mesh3D&&) = default;

			//************************************
			// Method:    init
			// FullName:  GFXEngine::Graphics::Mesh3D::init
			// Access:    public 
			// Returns:   void
			// Qualifier:
			// Parameter: Renderer & renderer
			//************************************
			void init(Renderer& renderer) override;
			
			//************************************
			// Method:    destroy
			// FullName:  GFXEngine::Graphics::Mesh3D::destroy
			// Access:    public 
			// Returns:   void
			// Qualifier:
			// Parameter: Renderer & renderer
			//************************************
			void destroy(Renderer& renderer) override;

			//************************************
			// Method:    setVertices
			// FullName:  GFXEngine::Graphics::Mesh3D::setVertices
			// Access:    public 
			// Returns:   void
			// Qualifier:
			// Parameter: std::vector<EngineTypes::Vertex3D> vertices
			//************************************
			void setVertices(std::vector<EngineTypes::Vertex3D> vertices) { m_vertices = std::move(vertices); }
			
			//************************************
			// Method:    setIndices
			// FullName:  GFXEngine::Graphics::Mesh3D::setIndices
			// Access:    public 
			// Returns:   void
			// Qualifier:
			// Parameter: std::vector<uint32_t> indices
			//************************************
			void setIndices(std::vector<uint32_t> indices) { m_indices = std::move(indices); }
			
			//************************************
			// Method:    computeAABB
			// FullName:  GFXEngine::Graphics::Mesh3D::computeAABB
			// Access:    public 
			// Returns:   GFXEngine::Math::AABB
			// Qualifier: const 
			//************************************
			Math::AABB computeAABB() const override;

			//************************************
			// Method:    getVertexComponent
			// FullName:  GFXEngine::Graphics::Mesh3D::getVertexComponent
			// Access:    public 
			// Returns:   GFXEngine::EngineTypes::VertexComponentView
			// Qualifier: const 
			// Parameter: GFXEngine::EngineTypes::VertexComponent component
			//************************************
			GFXEngine::EngineTypes::VertexComponentView getVertexComponent(GFXEngine::EngineTypes::VertexComponent component) const override;
			
			//************************************
			// Method:    getVertexPointer
			// FullName:  GFXEngine::Graphics::Mesh3D::getVertexPointer
			// Access:    public 
			// Returns:   GFXEngine::Graphics::MeshVertexPointer
			// Qualifier: const 
			//************************************
			MeshVertexPointer getVertexPointer() const override;
			
			//************************************
			// Method:    getIndices
			// FullName:  GFXEngine::Graphics::Mesh3D::getIndices
			// Access:    public 
			// Returns:   std::span<const uint32_t>
			// Qualifier: const 
			//************************************
			std::span<const uint32_t> getIndices() const override { return m_indices; }

			//************************************
			// Method:    getVertexBuffer
			// FullName:  GFXEngine::Graphics::Mesh3D::getVertexBuffer
			// Access:    public 
			// Returns:   const LibGFX::Buffer&
			// Qualifier: const 
			//************************************
			const LibGFX::Buffer& getVertexBuffer() const override { return m_vertexBuffer; }
			
			//************************************
			// Method:    getIndexBuffer
			// FullName:  GFXEngine::Graphics::Mesh3D::getIndexBuffer
			// Access:    public 
			// Returns:   const LibGFX::Buffer&
			// Qualifier: const 
			//************************************
			const LibGFX::Buffer& getIndexBuffer() const override { return m_indexBuffer; }
			
			//************************************
			// Method:    getIndexCount
			// FullName:  GFXEngine::Graphics::Mesh3D::getIndexCount
			// Access:    public 
			// Returns:   std::size_t
			// Qualifier: const 
			//************************************
			size_t getIndexCount() const override { return m_indices.size(); }
		};
	}
}