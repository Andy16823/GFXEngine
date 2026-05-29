#pragma once
#include "DataTypes.h"
#include "Mesh3D.h"
#include "PositionMesh.h"
#include "Mesh2D.h"

namespace GFXEngine
{
	namespace Core
	{
		/// <summary>
		/// MeshBuilder is a utility class for constructing Mesh objects by allowing the user to add vertices and indices incrementally.
		/// </summary>
		class MeshBuilder
		{
		private:
			std::vector<EngineTypes::Vertex3D> vertices;
			std::vector<uint32_t> indices;

		public:
			void addVertex(const EngineTypes::Vertex3D& vertex);
			void addVertex(const glm::vec3& pos, const glm::vec3& color);
			void addVertex(const glm::vec3& pos, const glm::vec3& color, const glm::vec2& texCoord);
			void addVertex(const glm::vec3& pos, const glm::vec3& color, const glm::vec2& texCoord, const glm::vec3& normal);
			void addVertex(const glm::vec3& pos, const glm::vec3& color, const glm::vec2& texCoord, const glm::vec3& normal, const glm::vec4& tangent);
			void addTriangle(uint32_t index1, uint32_t index2, uint32_t index3);
			void addQuad(uint32_t index1, uint32_t index2, uint32_t index3, uint32_t index4);
			uint32_t getCurrentVertexIndex() const { return static_cast<uint32_t>(vertices.size()); }
			GFXEngine::Graphics::Mesh3D buildMesh3D() const;
			GFXEngine::Graphics::PositionMesh buildPositionMesh() const;
			GFXEngine::Graphics::Mesh2D buildMesh2D() const;
		};
	}
}