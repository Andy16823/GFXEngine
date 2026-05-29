#pragma once
#include "Mesh.h"

namespace GFXEngine {
	namespace Graphics {

		/// <summary>
		/// PositionMesh is a simple implementation of the Mesh interface that represents a mesh consisting solely of vertex positions.
		/// </summary>
		class PositionMesh : public Mesh
		{
		private:
			std::vector<GFXEngine::EngineTypes::PositionVertex> m_vertices;
			std::vector<uint32_t> m_indices;
			LibGFX::Buffer m_vertexBuffer;
			LibGFX::Buffer m_indexBuffer;

		public:
			// Lifecycle management
			void init(Renderer& renderer) override;
			void destroy(Renderer& renderer) override;

			// Getters and setters
			void setVertices(std::vector<GFXEngine::EngineTypes::PositionVertex> vertices) { m_vertices = std::move(vertices); }
			void setIndices(std::vector<uint32_t> indices) { m_indices = std::move(indices); }
			Math::AABB computeAABB() const override;

			// Data access
			GFXEngine::EngineTypes::VertexComponentView getVertexComponent(GFXEngine::EngineTypes::VertexComponent component) const override;
			MeshVertexPointer getVertexPointer() const override;
			std::span<const uint32_t> getIndices() const override;

			// Renderer access
			const LibGFX::Buffer& getVertexBuffer() const override;
			const LibGFX::Buffer& getIndexBuffer() const override;
			size_t getIndexCount() const override;
		};
	}
}
