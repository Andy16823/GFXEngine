#include "Shapes.h"

std::vector<GFXEngine::EngineTypes::Vertex3D> GFXEngine::Graphics::Shapes::createPlane()
{
	std::vector<EngineTypes::Vertex3D> vertices = {
		{{-0.5f, 0.0f, -0.5f}, {1.0f, 1.0f, 1.0f}, {0.0f, 0.0f}, {0.0f, 1.0f, 0.0f}},
		{{ 0.5f, 0.0f, -0.5f}, {1.0f, 1.0f, 1.0f}, {1.0f, 0.0f}, {0.0f, 1.0f, 0.0f}},
		{{ 0.5f, 0.0f,  0.5f}, {1.0f, 1.0f, 1.0f}, {1.0f, 1.0f}, {0.0f, 1.0f, 0.0f}},
		{{-0.5f, 0.0f,  0.5f}, {1.0f, 1.0f, 1.0f}, {0.0f, 1.0f}, {0.0f, 1.0f, 0.0f}}
	};
	return vertices;
}

std::vector<uint32_t> GFXEngine::Graphics::Shapes::createPlaneIndices()
{
	std::vector<uint32_t> indices = {
		0, 1, 2,
		2, 3, 0
	};
	return indices;
}

std::vector<GFXEngine::EngineTypes::Vertex3D> GFXEngine::Graphics::Shapes::createSprite()
{
	std::vector<EngineTypes::Vertex3D> vertices = {
		{{-0.5f, -0.5f, 0.0f}, {1.0f, 1.0f, 1.0f}, {0.0f, 0.0f}, {0.0f, 0.0f, 1.0f}},
		{{ 0.5f, -0.5f, 0.0f}, {1.0f, 1.0f, 1.0f}, {1.0f, 0.0f}, {0.0f, 0.0f, 1.0f}},
		{{ 0.5f,  0.5f, 0.0f}, {1.0f, 1.0f, 1.0f}, {1.0f, 1.0f}, {0.0f, 0.0f, 1.0f}},
		{{-0.5f,  0.5f, 0.0f}, {1.0f, 1.0f, 1.0f}, {0.0f, 1.0f}, {0.0f, 0.0f, 1.0f}}
	};
	return vertices;
}

std::vector<uint32_t> GFXEngine::Graphics::Shapes::createSpriteIndices()
{
	std::vector<uint32_t> indices = {
		0, 1, 2,
		2, 3, 0
	};
	return indices;
}
