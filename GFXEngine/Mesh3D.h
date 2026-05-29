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
		/// Mesh3D is a concrete implementation of the Mesh interface, representing a 3D mesh with vertices containing position, color, texture coordinates, normals, and tangents. 
		/// It manages its own vertex and index buffers and provides functionality to compute its axis-aligned bounding box (AABB) and access vertex components.
		/// </summary>
		class Mesh3D : public Mesh{
		private:
			std::vector<EngineTypes::Vertex3D> m_vertices;
			std::vector<uint32_t> m_indices;
			LibGFX::Buffer m_vertexBuffer;
			LibGFX::Buffer m_indexBuffer;

		public:
			// Rule of five:
			Mesh3D() = default;
			Mesh3D(const Mesh3D&) = delete; // Disable copy semantics
			Mesh3D& operator=(const Mesh3D&) = delete; // Disable copy semantics
			Mesh3D(Mesh3D&&) = default; // Allow move semantics
			Mesh3D& operator=(Mesh3D&&) = default; // Allow move semantics

			// Lifecycle management
			void init(Renderer& renderer) override;
			void destroy(Renderer& renderer) override;

			// Getters and setters
			void setVertices(std::vector<EngineTypes::Vertex3D> vertices) { m_vertices = std::move(vertices); }
			void setIndices(std::vector<uint32_t> indices) { m_indices = std::move(indices); }
			Math::AABB computeAABB() const override;

			// Data access
			GFXEngine::EngineTypes::VertexComponentView getVertexComponent(GFXEngine::EngineTypes::VertexComponent component) const override;
			MeshVertexPointer getVertexPointer() const override;
			std::span<const uint32_t> getIndices() const override { return m_indices; }

			// Renderer access
			const LibGFX::Buffer& getVertexBuffer() const override { return m_vertexBuffer; }
			const LibGFX::Buffer& getIndexBuffer() const override { return m_indexBuffer; }
			size_t getIndexCount() const override { return m_indices.size(); }
		};
	}
}