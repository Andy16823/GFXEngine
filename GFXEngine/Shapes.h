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
			static std::pair<std::vector<GFXEngine::EngineTypes::Vertex3D>, std::vector<uint32_t>> createPlane();
			static std::pair<std::vector<GFXEngine::EngineTypes::Vertex2D>, std::vector<uint32_t>> createQuad();
			static std::pair<std::vector<GFXEngine::EngineTypes::PositionVertex>, std::vector<uint32_t>> createSkybox();
			static std::pair<std::vector<GFXEngine::EngineTypes::FramebufferVertex>, std::vector<uint32_t>> createFramebufferQuad();
		};
	}
}
