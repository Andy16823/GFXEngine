#include "Shapes.h"

std::pair<std::vector<GFXEngine::EngineTypes::Vertex3D>, std::vector<uint32_t>> GFXEngine::Graphics::Shapes::createPlane()
{
	std::vector<EngineTypes::Vertex3D> vertices = {
		{{-0.5f, 0.0f, -0.5f}, {1.0f, 1.0f, 1.0f}, {0.0f, 0.0f}, {0.0f, 1.0f, 0.0f}, {0.0f, 0.0f, 0.0f, 0.0f}},
		{{ 0.5f, 0.0f, -0.5f}, {1.0f, 1.0f, 1.0f}, {1.0f, 0.0f}, {0.0f, 1.0f, 0.0f}, {0.0f, 0.0f, 0.0f, 0.0f}},
		{{ 0.5f, 0.0f,  0.5f}, {1.0f, 1.0f, 1.0f}, {1.0f, 1.0f}, {0.0f, 1.0f, 0.0f}, {0.0f, 0.0f, 0.0f, 0.0f}},
		{{-0.5f, 0.0f,  0.5f}, {1.0f, 1.0f, 1.0f}, {0.0f, 1.0f}, {0.0f, 1.0f, 0.0f}, {0.0f, 0.0f, 0.0f, 0.0f}}
	};

	std::vector<uint32_t> indices = {
		0, 1, 2,
		2, 3, 0
	};

	return { vertices, indices };
}

std::pair<std::vector<GFXEngine::EngineTypes::Vertex2D>, std::vector<uint32_t>> GFXEngine::Graphics::Shapes::createQuad()
{
	std::vector<EngineTypes::Vertex2D> vertices = {
		{{-0.5f, -0.5f}, {1.0f, 1.0f, 1.0f}, {0.0f, 0.0f}},
		{{ 0.5f, -0.5f}, {1.0f, 1.0f, 1.0f}, {1.0f, 0.0f}},
		{{ 0.5f,  0.5f}, {1.0f, 1.0f, 1.0f}, {1.0f, 1.0f}},
		{{-0.5f,  0.5f}, {1.0f, 1.0f, 1.0f}, {0.0f, 1.0f}}
	};

	std::vector<uint32_t> indices = {
		0, 1, 2,
		2, 3, 0
	};

	return { vertices, indices };
}

std::pair<std::vector<GFXEngine::EngineTypes::FramebufferVertex>, std::vector<uint32_t>> GFXEngine::Graphics::Shapes::createFramebufferQuad()
{
	std::vector<EngineTypes::FramebufferVertex> vertices = {
		{{-1.0f, -1.0f, 0.0f}, {0.0f, 0.0f}},
		{{ 1.0f, -1.0f, 0.0f}, {1.0f, 0.0f}},
		{{ 1.0f,  1.0f, 0.0f}, {1.0f, 1.0f}},
		{{-1.0f,  1.0f, 0.0f}, {0.0f, 1.0f}}
	};
	std::vector<uint32_t> indices = {
		0, 1, 2,
		2, 3, 0
	};
	return { vertices, indices };
}

std::pair<std::vector<GFXEngine::EngineTypes::PositionVertex>, std::vector<uint32_t>> GFXEngine::Graphics::Shapes::createSkybox()
{
	std::vector<GFXEngine::EngineTypes::PositionVertex> vertices = {
		// Front (+Z)
		{{-1.0f, -1.0f,  1.0f}}, // 0
		{{ 1.0f, -1.0f,  1.0f}}, // 1
		{{ 1.0f,  1.0f,  1.0f}}, // 2
		{{-1.0f,  1.0f,  1.0f}}, // 3

		// Back (-Z)
		{{-1.0f, -1.0f, -1.0f}}, // 4
		{{ 1.0f, -1.0f, -1.0f}}, // 5
		{{ 1.0f,  1.0f, -1.0f}}, // 6
		{{-1.0f,  1.0f, -1.0f}}, // 7
	};

	std::vector<uint32_t> indices = {
		// Front (+Z)
		0, 2, 1, 0, 3, 2,
		// Back (-Z)
		5, 6, 4, 4, 6, 7,
		// Left (-X)
		4, 7, 0, 0, 7, 3,
		// Right (+X)
		1, 2, 5, 5, 2, 6,
		// Top (+Y)
		3, 7, 2, 2, 7, 6,
		// Bottom (-Y)
		4, 0, 5, 5, 0, 1
	};
	return { vertices, indices };
}