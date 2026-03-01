#pragma once
#include "DataTypes.h"
#include "Entity.h"
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
			const LibGFX::Pipeline& m_pipeline;

		public:
			Sprite(const Graphics::SpriteMaterial& material, const Graphics::Mesh& mesh, const LibGFX::Pipeline& pipeline)
				: m_material(material), m_mesh(mesh), m_pipeline(pipeline) {
				this->transform.position = glm::vec3(0.0f);
				this->transform.rotation = glm::quat(1.0f, 0.0f, 0.0f, 0.0f);
				this->transform.scale = glm::vec3(1.0f);
			}
			virtual ~Sprite() = default;
			
			virtual void init(GFXEngine::Graphics::Renderer& renderer) override;
			virtual void update(float deltaTime) override;
			virtual void render(GFXEngine::Graphics::Renderer& renderer, GFXEngine::Graphics::Camera& camera, uint32_t imageIndex) override;
			virtual void destroy(GFXEngine::Graphics::Renderer& renderer) override;
		};
	}
}
