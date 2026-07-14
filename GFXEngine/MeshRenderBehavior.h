#pragma once
#include "Behavior.h"
#include "IRenderable.h"
#include "Mesh3D.h"

namespace GFXEngine {
	namespace Core {
		class MeshRenderBehavior : public Behavior, public Graphics::IRenderable
		{
		private:
			Graphics::Mesh3D* m_mesh = nullptr;
			Graphics::Material* m_material = nullptr;
			Graphics::GraphicsPipeline* m_pipeline = nullptr;

		public:
			MeshRenderBehavior(Graphics::Mesh3D* mesh, Graphics::Material* material, Graphics::GraphicsPipeline* pipeline)
				: m_mesh(mesh), m_material(material), m_pipeline(pipeline) {}

		public:
			// Geerbt über Behavior
			void init(Scene& scene, Graphics::Renderer& renderer) override;
			void update(Scene& scene, Graphics::Camera& camera, float deltaTime) override;
			void destroy(Scene& scene, Graphics::Renderer& renderer) override;
			std::string getName() const override;
			std::vector<PropertyInfo> getProperties() override;

		public:
			// Geerbt über IRenderable
			void buildRenderTasks(Graphics::RenderContext& context, Graphics::RenderQueue& renderQueue) override;
		};
	}
}