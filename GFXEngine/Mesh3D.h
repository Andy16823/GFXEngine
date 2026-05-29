#pragma once
#include "DataTypes.h"
#include "Renderer.h"
#include "Mesh.h"
#include "Buffer.h"
#include <vector>
#include "AABB.h"

namespace GFXEngine {
	namespace Graphics {

		/// <summary>
		/// Mesh class that encapsulates vertex and index data, along with Vulkan buffers for rendering. 
		/// It provides methods to initialize the mesh, draw it using a renderer, and clean up resources when done.
		/// TODO: Add mesh matrix;
		/// </summary>
		class Mesh3D : public Mesh{
		private:
			std::vector<EngineTypes::Vertex3D> m_vertices;
			std::vector<uint32_t> m_indices;
			LibGFX::Buffer m_vertexBuffer;
			LibGFX::Buffer m_indexBuffer;

		public:
			Mesh3D() = default;

			Mesh3D(const Mesh3D&) = delete; // Disable copy semantics
			Mesh3D& operator=(const Mesh3D&) = delete; // Disable copy semantics
			Mesh3D(Mesh3D&&) = default; // Allow move semantics
			Mesh3D& operator=(Mesh3D&&) = default; // Allow move semantics

			void init(Renderer& renderer) override;
			void destroy(Renderer& renderer) override;

			void setVertices(std::vector<EngineTypes::Vertex3D> vertices) { m_vertices = std::move(vertices); }
			void setIndices(std::vector<uint32_t> indices) { m_indices = std::move(indices); }
			Math::AABB computeAABB() const override;

			MeshVertexPointer getVertexPointer() const override;
			std::span<const uint32_t> getIndices() const override { return m_indices; }
			const LibGFX::Buffer& getVertexBuffer() const override { return m_vertexBuffer; }
			const LibGFX::Buffer& getIndexBuffer() const override { return m_indexBuffer; }
			size_t getIndexCount() const override { return m_indices.size(); }
		};
	}
}