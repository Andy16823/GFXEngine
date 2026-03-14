#pragma once
#include "DataTypes.h"

namespace GFXEngine {
	namespace Graphics {

		/// <summary>
		/// Factory class for creating common shapes like planes, sprites, and quads. This helps to avoid redundant code when generating vertex and index data for these frequently used shapes.
		/// </summary>
		class Shapes
		{
		public:
			static std::vector<GFXEngine::EngineTypes::Vertex3D> createPlane();
			static std::vector<uint32_t> createPlaneIndices();
			static std::pair<std::vector<GFXEngine::EngineTypes::Vertex3D>, std::vector<uint32_t>> createSprite();
			static std::pair<std::vector<GFXEngine::EngineTypes::PositionVertex>, std::vector<uint32_t>> createSkybox();
			static void createSprite(std::vector<GFXEngine::EngineTypes::Vertex3D>& vertices, std::vector<uint32_t>& indices);
			static std::pair<std::vector<GFXEngine::EngineTypes::Vertex3D>, std::vector<uint32_t>> createFramebufferQuad();
		};
	}
}
