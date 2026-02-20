#pragma once
#include "DataTypes.h"

namespace GFXEngine {
	namespace Graphics {
		class Shapes
		{
		public:
			static std::vector<GFXEngine::EngineTypes::Vertex3D> createPlane();
			static std::vector<uint32_t> createPlaneIndices();
			static std::pair<std::vector<GFXEngine::EngineTypes::Vertex3D>, std::vector<uint32_t>> createSprite();
			static void createSprite(std::vector<GFXEngine::EngineTypes::Vertex3D>& vertices, std::vector<uint32_t>& indices);
			static std::pair<std::vector<GFXEngine::EngineTypes::Vertex3D>, std::vector<uint32_t>> createFramebufferQuad();
		};
	}
}
