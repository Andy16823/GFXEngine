#pragma once
#include "Entity.h"
#include "MeshModel.h"

namespace GFXEngine {
	namespace Core {

		/// <summary>
		/// Model entity that represents a 3D mesh model in the scene.
		/// </summary>
		class Model : public Entity
		{
		private:
			const Graphics::MeshModel& m_meshModel;
			const LibGFX::Pipeline& m_pipeline;

		public:
			Model(const Graphics::MeshModel& meshModel, const LibGFX::Pipeline& pipeline) 
				: m_meshModel(meshModel), m_pipeline(pipeline) {}

			void render(GFXEngine::Graphics::Renderer& renderer, GFXEngine::Graphics::Camera& camera, uint32_t imageIndex) override;
			const Graphics::MeshModel& getMeshModel() const { return m_meshModel; }
		};
	}
}