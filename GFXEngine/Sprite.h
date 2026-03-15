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
		public:
			Sprite(const Graphics::SpriteMaterial& material, const Graphics::Mesh& mesh)
				: m_material(material), m_mesh(mesh) {
				this->transform.position = glm::vec3(0.0f);
				this->transform.rotation = glm::quat(1.0f, 0.0f, 0.0f, 0.0f);
				this->transform.scale = glm::vec3(1.0f);
			}
			virtual ~Sprite() = default;
			
			virtual void init(Scene& scene, GFXEngine::Graphics::Renderer& renderer) override;
			virtual void update(Scene& scene, float deltaTime) override;
			virtual void render(Scene& scene, GFXEngine::Graphics::Renderer& renderer, GFXEngine::Graphics::Camera& camera, uint32_t imageIndex) override;
			virtual void destroy(Scene& scene, GFXEngine::Graphics::Renderer& renderer) override;

			virtual size_t getMeshCount() const override { return 1; }
			virtual std::pair<const Graphics::Mesh&, const Graphics::Material&> getMeshAndMaterial(size_t index) const override;
		private:
			const Graphics::SpriteMaterial& m_material;
			const Graphics::Mesh& m_mesh;
		};
	}
}
