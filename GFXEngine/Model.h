#pragma once
#include "Entity.h"
#include "MeshModel.h"
#include "GeometryPipeline.h"

namespace GFXEngine {
	namespace Core {

		/// <summary>
		/// Model entity that represents a 3D mesh model in the scene.
		/// </summary>
		class Model : public Entity
		{
		private:
			const Graphics::MeshModel& m_meshModel;	

		public:
			Model(const Graphics::MeshModel& meshModel, const Graphics::GeometryPipeline& pipeline) 
				: m_meshModel(meshModel) {}

			void init(Scene& scene, GFXEngine::Graphics::Renderer& renderer) override;
			void render(Scene& scene, GFXEngine::Graphics::Renderer& renderer, GFXEngine::Graphics::Camera& camera, uint32_t imageIndex) override;

			size_t getMeshCount() const override;
			std::pair<const Graphics::Mesh&, const Graphics::Material&> getMeshAndMaterial(size_t index) const override;

			const Graphics::MeshModel& getMeshModel() const { return m_meshModel; }


			

		};
	}
}