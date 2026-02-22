#pragma once
#include "DataTypes.h"
#include "Entity.h"
#include "Imaging.h"
#include "Buffer.h"
#include <vector>
#include "Pipeline.h"
#include "SpriteMaterial.h"
#include "Mesh.h"

namespace GFXEngine {
	namespace Core {

		/// <summary>
		/// Sprite entity that represents a 2D textured quad in the scene. 
		/// It uses a SpriteMaterial for rendering and contains 
		/// vertex and index buffers for the quad geometry.
		/// </summary>
		class Sprite : public Entity
		{
		private:
			const Graphics::SpriteMaterial& m_material;
			const Graphics::Mesh& m_mesh;

		public:
			Sprite(const Graphics::SpriteMaterial& material, const Graphics::Mesh& mesh);
			virtual ~Sprite() = default;
			
			virtual void init(GFXEngine::Graphics::Renderer& renderer) override;
			virtual void update(float deltaTime) override;
			virtual void render(GFXEngine::Graphics::Renderer& renderer, GFXEngine::Graphics::Camera& camera, uint32_t imageIndex) override;
			virtual void destroy(GFXEngine::Graphics::Renderer& renderer) override;
		};
	}
}
