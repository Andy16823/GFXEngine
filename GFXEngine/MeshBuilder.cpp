#include "MeshBuilder.h"
#include <cmath>
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>
#include <stdexcept>

using namespace GFXEngine;
using namespace GFXEngine::Core;
using namespace GFXEngine::EngineTypes;
using namespace GFXEngine::Graphics;

void GFXEngine::Core::MeshBuilder::addVertex(const EngineTypes::Vertex3D& vertex)
{
	vertices.push_back(vertex);
}

MeshBuilder MeshBuilder::createCylinder(float radius /*= 1.0f*/, float height /*= 1.0f*/, uint32_t sectorCount /*= 36*/)
{
    MeshBuilder builder;

    const float halfHeight = height * 0.5f;
    const float sectorStep = glm::two_pi<float>() / sectorCount;

    // ============================================================
    // Hull
    // ============================================================

    for (uint32_t i = 0; i <= sectorCount; ++i)
    {
        const float angle = i * sectorStep;

        const float x = radius * cosf(angle);
        const float z = radius * sinf(angle);

        // Outward-facing normal
        const glm::vec3 normal = glm::normalize(
            glm::vec3(x, 0.0f, z)
            );

        // Bottom
        builder.addVertex(
            { x, -halfHeight, z },
            { 1, 1, 1 },
            { static_cast<float>(i) / sectorCount, 0.0f },
            normal
            );

        // Top
        builder.addVertex(
            { x, halfHeight, z },
            { 1, 1, 1 },
            { static_cast<float>(i) / sectorCount, 1.0f },
            normal
            );
    }

    // Hull indices
    //
    // IMPORTANT:
    // The winding must produce outward-facing triangles.
    //
    // bottom0 -> top0 -> top1 -> bottom1
    //
    for (uint32_t i = 0; i < sectorCount; ++i)
    {
        const uint32_t bottom0 = i * 2;
        const uint32_t top0 = bottom0 + 1;

        const uint32_t bottom1 = bottom0 + 2;
        const uint32_t top1 = bottom0 + 3;

        builder.addQuad(
            bottom0,
            top0,
            top1,
            bottom1
            );
    }

    // ============================================================
    // Top cap
    // ============================================================

    const uint32_t centerTop = builder.vertexCount();

    builder.addVertex(
        { 0.0f, halfHeight, 0.0f },
        { 1, 1, 1 },
        { 0.5f, 0.5f },
        { 0, 1, 0 }
        );

    const uint32_t topStart = builder.vertexCount();

    for (uint32_t i = 0; i <= sectorCount; ++i)
    {
        const float angle = i * sectorStep;

        const float x = radius * cosf(angle);
        const float z = radius * sinf(angle);

        builder.addVertex(
            { x, halfHeight, z },
            { 1, 1, 1 },
            {
                x / radius * 0.5f + 0.5f,
                z / radius * 0.5f + 0.5f
            },
            { 0, 1, 0 }
            );
    }

    // Viewed from above -> CCW -> +Y
    for (uint32_t i = 0; i < sectorCount; ++i)
    {
        builder.addTriangle(
            centerTop,
            topStart + i,
            topStart + i + 1
            );
    }

    // ============================================================
    // Bottom cap
    // ============================================================

    const uint32_t centerBottom = builder.vertexCount();

    builder.addVertex(
        { 0.0f, -halfHeight, 0.0f },
        { 1, 1, 1 },
        { 0.5f, 0.5f },
        { 0, -1, 0 }
        );

    const uint32_t bottomStart = builder.vertexCount();

    for (uint32_t i = 0; i <= sectorCount; ++i)
    {
        const float angle = i * sectorStep;

        const float x = radius * cosf(angle);
        const float z = radius * sinf(angle);

        builder.addVertex(
            { x, -halfHeight, z },
            { 1, 1, 1 },
            {
                x / radius * 0.5f + 0.5f,
                z / radius * 0.5f + 0.5f
            },
            { 0, -1, 0 }
            );
    }

    // Viewed from below -> CCW -> -Y
    for (uint32_t i = 0; i < sectorCount; ++i)
    {
        builder.addTriangle(
            centerBottom,
            bottomStart + i + 1,
            bottomStart + i
            );
    }

    return builder;
}

MeshBuilder MeshBuilder::createSphere(float radius /*= 1.0f*/, uint32_t sectorCount /*= 36*/, uint32_t stackCount /*= 18*/)
{
	MeshBuilder builder;

	float stackStep = glm::pi<float>() / stackCount;
	float sectorStep = 2 * glm::pi<float>() / sectorCount;
	
	for (uint32_t i = 0; i <= stackCount; ++i) {

		float stackAngle = glm::pi<float>() / 2 - i * stackStep; // from pi/2 to -pi/2
		float xy = radius * cosf(stackAngle); // r * cos(u)
		float z = radius * sinf(stackAngle); // r * sin(u)

		for (uint32_t j = 0; j <= sectorCount; ++j) {
			float sectorAngle = j * sectorStep; // from 0 to 2pi

			float x = xy * cosf(sectorAngle); // r * cos(u) * cos(v)
			float y = xy * sinf(sectorAngle); // r * cos(u) * sin(v)

			builder.addVertex({ { x, y, z }, { 1.0f, 1.0f, 1.0f }, { (float)j / sectorCount, (float)i / stackCount }, { x / radius, y / radius, z / radius }, { 0.0f, 0.0f, 0.0f, 1.0f } });
		}

	}

	for (uint32_t i = 0; i < stackCount; ++i) {
		for (uint32_t j = 0; j < sectorCount; ++j) {
			uint32_t k1 = i * (sectorCount + 1) + j;
			uint32_t k2 = k1 + sectorCount + 1;

			if (i != 0) {
				builder.addTriangle(k1, k2, k1 + 1);
			}

			if (i != (stackCount - 1)) {
				builder.addTriangle(k1 + 1, k2, k2 + 1);
			}
		}
	}

	return builder;
}

MeshBuilder MeshBuilder::createQuad(float width /*= 1.0f*/, float height /*= 1.0f*/)
{
	MeshBuilder builder;
	builder.addVertex({ { -width * 0.5f, -height * 0.5f, 0.0f }, { 1.0f, 0.0f, 0.0f }, { 0.0f, 0.0f }, { 0.0f, 0.0f, 1.0f }, { 1.0f, 0.0f, 0.0f, 1.0f } }); // Bottom-left
	builder.addVertex({ { width * 0.5f, -height * 0.5f, 0.0f }, { 0.0f, 1.0f, 0.0f }, { 1.0f, 0.0f }, { 0.0f, 0.0f, 1.0f }, { 1.0f, 0.0f, 0.0f, 1.0f } }); // Bottom-right
	builder.addVertex({ { width * 0.5f, height * 0.5f, 0.0f }, { 0.0f, 0.0f, 1.0f }, { 1.0f, 1.0f }, { 0.0f, 0.0f, 1.0f }, { 1.0f, 0.0f, 0.0f, 1.0f } }); // Top-right
	builder.addVertex({ { -width * 0.5f, height * 0.5f, 0.0f }, { 1.0f, 1.0f, 0.0f }, { 0.0f, 1.0f }, { 0.0f, 0.0f, 1.0f }, { 1.0f, 0.0f, 0.0f, 1.0f } }); // Top-left

	builder.addQuad(0, 1, 2, 3); // Front face
	return builder;
}

MeshBuilder MeshBuilder::createCube(float size /*= 1.0f*/)
{
	const float h = size * 0.5f;

	MeshBuilder builder;

	// Back -Z
	builder.addVertex({ {-h,-h,-h}, {1,1,1}, {0,0}, { 0, 0,-1}, {1,0,0,1} });
	builder.addVertex({ { h,-h,-h}, {1,1,1}, {1,0}, { 0, 0,-1}, {1,0,0,1} });
	builder.addVertex({ { h, h,-h}, {1,1,1}, {1,1}, { 0, 0,-1}, {1,0,0,1} });
	builder.addVertex({ {-h, h,-h}, {1,1,1}, {0,1}, { 0, 0,-1}, {1,0,0,1} });

	// Front +Z
	builder.addVertex({ {-h,-h, h}, {1,1,1}, {0,0}, { 0, 0, 1}, {-1,0,0,1} });
	builder.addVertex({ { h,-h, h}, {1,1,1}, {1,0}, { 0, 0, 1}, {-1,0,0,1} });
	builder.addVertex({ { h, h, h}, {1,1,1}, {1,1}, { 0, 0, 1}, {-1,0,0,1} });
	builder.addVertex({ {-h, h, h}, {1,1,1}, {0,1}, { 0, 0, 1}, {-1,0,0,1} });

	// Left -X
	builder.addVertex({ {-h,-h,-h}, {1,1,1}, {0,0}, {-1, 0, 0}, {0,0,1,1} });
	builder.addVertex({ {-h,-h, h}, {1,1,1}, {1,0}, {-1, 0, 0}, {0,0,1,1} });
	builder.addVertex({ {-h, h, h}, {1,1,1}, {1,1}, {-1, 0, 0}, {0,0,1,1} });
	builder.addVertex({ {-h, h,-h}, {1,1,1}, {0,1}, {-1, 0, 0}, {0,0,1,1} });

	// Right +X
	builder.addVertex({ { h,-h,-h}, {1,1,1}, {0,0}, { 1, 0, 0}, {0,0,-1,1} });
	builder.addVertex({ { h,-h, h}, {1,1,1}, {1,0}, { 1, 0, 0}, {0,0,-1,1} });
	builder.addVertex({ { h, h, h}, {1,1,1}, {1,1}, { 1, 0, 0}, {0,0,-1,1} });
	builder.addVertex({ { h, h,-h}, {1,1,1}, {0,1}, { 1, 0, 0}, {0,0,-1,1} });

	// Top +Y
	builder.addVertex({ {-h, h,-h}, {1,1,1}, {0,0}, { 0, 1, 0}, {1,0,1,1} });
	builder.addVertex({ { h, h,-h}, {1,1,1}, {1,0}, { 0, 1, 0}, {1,0,1,1} });
	builder.addVertex({ { h, h, h}, {1,1,1}, {1,1}, { 0, 1, 0}, {1,0,1,1} });
	builder.addVertex({ {-h, h, h}, {1,1,1}, {0,1}, { 0, 1, 0}, {1,0,1,1} });

	// Bottom -Y
	builder.addVertex({ {-h,-h,-h}, {1,1,1}, {0,0}, { 0,-1, 0}, {0,1,1,1} });
	builder.addVertex({ { h,-h,-h}, {1,1,1}, {1,0}, { 0,-1, 0}, {0,1,1,1} });
	builder.addVertex({ { h,-h, h}, {1,1,1}, {1,1}, { 0,-1, 0}, {0,1,1,1} });
	builder.addVertex({ {-h,-h, h}, {1,1,1}, {0,1}, { 0,-1, 0}, {0,1,1,1} });


	builder.addQuad(0, 1, 2, 3); // Back
	builder.addQuad(4, 5, 6, 7); // Front
	builder.addQuad(8, 9, 10, 11); // Left
	builder.addQuad(12, 13, 14, 15); // Right
	builder.addQuad(16, 17, 18, 19); // Top
	builder.addQuad(20, 21, 22, 23); // Bottom

	return builder;
}

GFXEngine::Graphics::Mesh2D MeshBuilder::buildMesh2D() const
{
	Mesh2D mesh;
	std::vector<EngineTypes::Vertex2D> vertices2D;
	vertices2D.reserve(vertices.size());
	for (const auto& vertex : vertices) {
		vertices2D.push_back({ vertex.pos, vertex.color, vertex.texCoord });
	}
	mesh.setVertices(std::move(vertices2D));
	mesh.setIndices(indices);
	return mesh;
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