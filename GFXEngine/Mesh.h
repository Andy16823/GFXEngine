#pragma once
#include "DataTypes.h"
#include "Renderer.h"
#include "Buffer.h"
#include <vector>

namespace GFXEngine {
	namespace Graphics {

		/// <summary>
		/// Mesh class that encapsulates vertex and index data, along with Vulkan buffers for rendering. 
		/// It provides methods to initialize the mesh, draw it using a renderer, and clean up resources when done.
		/// </summary>
		class Mesh {
		private:
			std::vector<EngineTypes::Vertex3D> m_vertices;
			std::vector<uint32_t> m_indices;
			LibGFX::Buffer m_vertexBuffer;
			LibGFX::Buffer m_indexBuffer;

		public:
			Mesh() = default;
			virtual ~Mesh() = default;

			Mesh(const Mesh&) = delete; // Disable copy semantics
			Mesh& operator=(const Mesh&) = delete; // Disable copy semantics
			Mesh(Mesh&&) = default; // Allow move semantics
			Mesh& operator=(Mesh&&) = default; // Allow move semantics

			void init(Renderer& renderer);
			void draw(Renderer& renderer, uint32_t imageIndex) const;
			void destroy(Renderer& renderer);

			void setVertices(std::vector<EngineTypes::Vertex3D> vertices) { m_vertices = std::move(vertices); }
			void setIndices(std::vector<uint32_t> indices) { m_indices = std::move(indices); }

			const LibGFX::Buffer& getVertexBuffer() const { return m_vertexBuffer; }
			const LibGFX::Buffer& getIndexBuffer() const { return m_indexBuffer; }
			size_t getIndexCount() const { return m_indices.size(); }
		};
	}
}