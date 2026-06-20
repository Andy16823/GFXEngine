#pragma once
#include "DataTypes.h"
#include "AABB.h"

namespace GFXEngine {
	namespace Graphics {

		class Shapes
		{
		public:
			//************************************
			// Method:    createPlane
			// FullName:  GFXEngine::Graphics::Shapes::createPlane
			// Access:    public static 
			// Returns:   std::pair<std::vector<GFXEngine::EngineTypes::Vertex3D>, std::vector<uint32_t>>
			// Qualifier:
			//************************************
			static std::pair<std::vector<GFXEngine::EngineTypes::Vertex3D>, std::vector<uint32_t>> createPlane();

			//************************************
			// Method:    createQuad
			// FullName:  GFXEngine::Graphics::Shapes::createQuad
			// Access:    public static 
			// Returns:   std::pair<std::vector<GFXEngine::EngineTypes::Vertex2D>, std::vector<uint32_t>>
			// Qualifier:
			//************************************
			static std::pair<std::vector<GFXEngine::EngineTypes::Vertex2D>, std::vector<uint32_t>> createQuad();
			
			//************************************
			// Method:    createSkybox
			// FullName:  GFXEngine::Graphics::Shapes::createSkybox
			// Access:    public static 
			// Returns:   std::pair<std::vector<GFXEngine::EngineTypes::PositionVertex>, std::vector<uint32_t>>
			// Qualifier:
			//************************************
			static std::pair<std::vector<GFXEngine::EngineTypes::PositionVertex>, std::vector<uint32_t>> createSkybox();
			
			//************************************
			// Method:    createFramebufferQuad
			// FullName:  GFXEngine::Graphics::Shapes::createFramebufferQuad
			// Access:    public static 
			// Returns:   std::pair<std::vector<GFXEngine::EngineTypes::FramebufferVertex>, std::vector<uint32_t>>
			// Qualifier:
			//************************************
			static std::pair<std::vector<GFXEngine::EngineTypes::FramebufferVertex>, std::vector<uint32_t>> createFramebufferQuad();
			
			//************************************
			// Method:    createAabbVertices
			// FullName:  GFXEngine::Graphics::Shapes::createAabbVertices
			// Access:    public static 
			// Returns:   std::pair<std::vector<GFXEngine::EngineTypes::PositionVertex>, std::vector<uint32_t>>
			// Qualifier:
			// Parameter: const GFXEngine::Math::AABB & aabb
			//************************************
			static std::pair<std::vector<GFXEngine::EngineTypes::PositionVertex>, std::vector<uint32_t>> createAabbVertices(const GFXEngine::Math::AABB& aabb);
		};
	}
}
