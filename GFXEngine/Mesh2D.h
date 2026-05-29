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
			void init(Renderer& renderer) override;
			void destroy(Renderer& renderer) override;
			Math::AABB computeAABB() const override;

			void setVertices(std::vector<GFXEngine::EngineTypes::Vertex2D> vertices) { m_vertices = std::move(vertices); }
			void setIndices(std::vector<uint32_t> indices) { m_indices = std::move(indices); }

			const LibGFX::Buffer& getVertexBuffer() const override;
			const LibGFX::Buffer& getIndexBuffer() const override;
			size_t getIndexCount() const override;

			GFXEngine::EngineTypes::VertexComponentView getVertexComponent(GFXEngine::EngineTypes::VertexComponent component) const override;
			MeshVertexPointer getVertexPointer() const override;
			std::span<const uint32_t> getIndices() const override;
		};
	}
}