#pragma once
#include "DataTypes.h"
#include "Renderer.h"
#include "Buffer.h"
#include <vector>

namespace GFXEngine {
	namespace Graphics {
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
		};
	}
}