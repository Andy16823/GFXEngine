#pragma once
#include "DataTypes.h"

namespace GFXEngine {
	namespace Graphics {
		class Shapes
		{
		public:
			static std::vector<GFXEngine::EngineTypes::Vertex3D> createPlane();
			static std::vector<uint32_t> createPlaneIndices();
			static std::vector<GFXEngine::EngineTypes::Vertex3D> createSprite();
			static std::vector<uint32_t> createSpriteIndices();
		};
	}
}
