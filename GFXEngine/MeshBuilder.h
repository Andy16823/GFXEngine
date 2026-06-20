#pragma once
#include "DataTypes.h"
#include "Mesh3D.h"
#include "PositionMesh.h"
#include "Mesh2D.h"

namespace GFXEngine
{
	namespace Core
	{
		class MeshBuilder
		{
		private:
			std::vector<EngineTypes::Vertex3D> vertices;
			std::vector<uint32_t> indices;

		public:
			//************************************
			// Method:    addVertex
			// FullName:  GFXEngine::Core::MeshBuilder::addVertex
			// Access:    public 
			// Returns:   void
			// Qualifier:
			// Parameter: const EngineTypes::Vertex3D & vertex
			//************************************
			void addVertex(const EngineTypes::Vertex3D& vertex);
			
			//************************************
			// Method:    addVertex
			// FullName:  GFXEngine::Core::MeshBuilder::addVertex
			// Access:    public 
			// Returns:   void
			// Qualifier:
			// Parameter: const glm::vec3 & pos
			// Parameter: const glm::vec3 & color
			//************************************
			void addVertex(const glm::vec3& pos, const glm::vec3& color);
			
			//************************************
			// Method:    addVertex
			// FullName:  GFXEngine::Core::MeshBuilder::addVertex
			// Access:    public 
			// Returns:   void
			// Qualifier:
			// Parameter: const glm::vec3 & pos
			// Parameter: const glm::vec3 & color
			// Parameter: const glm::vec2 & texCoord
			//************************************
			void addVertex(const glm::vec3& pos, const glm::vec3& color, const glm::vec2& texCoord);
			
			//************************************
			// Method:    addVertex
			// FullName:  GFXEngine::Core::MeshBuilder::addVertex
			// Access:    public 
			// Returns:   void
			// Qualifier:
			// Parameter: const glm::vec3 & pos
			// Parameter: const glm::vec3 & color
			// Parameter: const glm::vec2 & texCoord
			// Parameter: const glm::vec3 & normal
			//************************************
			void addVertex(const glm::vec3& pos, const glm::vec3& color, const glm::vec2& texCoord, const glm::vec3& normal);
			
			//************************************
			// Method:    addVertex
			// FullName:  GFXEngine::Core::MeshBuilder::addVertex
			// Access:    public 
			// Returns:   void
			// Qualifier:
			// Parameter: const glm::vec3 & pos
			// Parameter: const glm::vec3 & color
			// Parameter: const glm::vec2 & texCoord
			// Parameter: const glm::vec3 & normal
			// Parameter: const glm::vec4 & tangent
			//************************************
			void addVertex(const glm::vec3& pos, const glm::vec3& color, const glm::vec2& texCoord, const glm::vec3& normal, const glm::vec4& tangent);
			
			//************************************
			// Method:    addTriangle
			// FullName:  GFXEngine::Core::MeshBuilder::addTriangle
			// Access:    public 
			// Returns:   void
			// Qualifier:
			// Parameter: uint32_t index1
			// Parameter: uint32_t index2
			// Parameter: uint32_t index3
			//************************************
			void addTriangle(uint32_t index1, uint32_t index2, uint32_t index3);
			
			//************************************
			// Method:    addQuad
			// FullName:  GFXEngine::Core::MeshBuilder::addQuad
			// Access:    public 
			// Returns:   void
			// Qualifier:
			// Parameter: uint32_t index1
			// Parameter: uint32_t index2
			// Parameter: uint32_t index3
			// Parameter: uint32_t index4
			//************************************
			void addQuad(uint32_t index1, uint32_t index2, uint32_t index3, uint32_t index4);
			
			//************************************
			// Method:    getCurrentVertexIndex
			// FullName:  GFXEngine::Core::MeshBuilder::getCurrentVertexIndex
			// Access:    public 
			// Returns:   uint32_t
			// Qualifier: const
			//************************************
			uint32_t getCurrentVertexIndex() const { return static_cast<uint32_t>(vertices.size()); }
			
			//************************************
			// Method:    buildMesh3D
			// FullName:  GFXEngine::Core::MeshBuilder::buildMesh3D
			// Access:    public 
			// Returns:   GFXEngine::Graphics::Mesh3D
			// Qualifier: const
			//************************************
			GFXEngine::Graphics::Mesh3D buildMesh3D() const;
			
			//************************************
			// Method:    buildPositionMesh
			// FullName:  GFXEngine::Core::MeshBuilder::buildPositionMesh
			// Access:    public 
			// Returns:   GFXEngine::Graphics::PositionMesh
			// Qualifier: const
			//************************************
			GFXEngine::Graphics::PositionMesh buildPositionMesh() const;
			
			//************************************
			// Method:    buildMesh2D
			// FullName:  GFXEngine::Core::MeshBuilder::buildMesh2D
			// Access:    public 
			// Returns:   GFXEngine::Graphics::Mesh2D
			// Qualifier: const
			//************************************
			GFXEngine::Graphics::Mesh2D buildMesh2D() const;
		};
	}
}