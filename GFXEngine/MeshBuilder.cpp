#include "MeshBuilder.h"

using namespace GFXEngine;
using namespace GFXEngine::Core;
using namespace GFXEngine::EngineTypes;
using namespace GFXEngine::Graphics;

void GFXEngine::Core::MeshBuilder::addVertex(const EngineTypes::Vertex3D& vertex)
{
	vertices.push_back(vertex);
}

GFXEngine::Graphics::PositionMesh MeshBuilder::buildPositionMesh() const
{
	PositionMesh mesh;
	std::vector<EngineTypes::PositionVertex> positionVertices;
	positionVertices.reserve(vertices.size());
	for (const auto& vertex : vertices) {
		positionVertices.push_back({ vertex.pos });
	}
	mesh.setVertices(std::move(positionVertices));
	mesh.setIndices(indices);
	return mesh;
}

GFXEngine::Graphics::Mesh3D MeshBuilder::buildMesh3D() const
{
	Mesh3D mesh;
	mesh.setVertices(vertices);
	mesh.setIndices(indices);
	return mesh;	
}

void MeshBuilder::addQuad(uint32_t index1, uint32_t index2, uint32_t index3, uint32_t index4)
{
	indices.push_back(index1);
	indices.push_back(index2);
	indices.push_back(index3);
	indices.push_back(index1);
	indices.push_back(index3);
	indices.push_back(index4);
}

void MeshBuilder::addTriangle(uint32_t index1, uint32_t index2, uint32_t index3)
{
	indices.push_back(index1);
	indices.push_back(index2);
	indices.push_back(index3);
}

void MeshBuilder::addVertex(const glm::vec3& pos, const glm::vec3& color, const glm::vec2& texCoord, const glm::vec3& normal, const glm::vec4& tangent)
{
	Vertex3D vertex;
	vertex.pos = pos;
	vertex.color = color;
	vertex.texCoord = texCoord;
	vertex.normal = normal;
	vertex.tangent = tangent;
	vertices.push_back(vertex);
}

void MeshBuilder::addVertex(const glm::vec3& pos, const glm::vec3& color, const glm::vec2& texCoord, const glm::vec3& normal)
{
	Vertex3D vertex;
	vertex.pos = pos;
	vertex.color = color;
	vertex.texCoord = texCoord;
	vertex.normal = normal;
	vertex.tangent = glm::vec4(0.0f);
	vertices.push_back(vertex);
}

void MeshBuilder::addVertex(const glm::vec3& pos, const glm::vec3& color, const glm::vec2& texCoord)
{
	Vertex3D vertex;
	vertex.pos = pos;
	vertex.color = color;
	vertex.texCoord = texCoord;
	vertex.normal = glm::vec3(0.0f);
	vertex.tangent = glm::vec4(0.0f);
	vertices.push_back(vertex);
}

void MeshBuilder::addVertex(const glm::vec3& pos, const glm::vec3& color)
{
	Vertex3D vertex;
	vertex.pos = pos;
	vertex.color = color;
	vertex.texCoord = glm::vec2(0.0f);
	vertex.normal = glm::vec3(0.0f);
	vertex.tangent = glm::vec4(0.0f);
	vertices.push_back(vertex);
}