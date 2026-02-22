#pragma once
#include "Entity.h"
#include "MeshModel.h"

namespace GFXEngine {
	namespace Core {
		class Model : public Entity
		{
		private:
			const Graphics::MeshModel& m_meshModel;

		public:
			Model(const Graphics::MeshModel& meshModel) : m_meshModel(meshModel) {}
			void render(GFXEngine::Graphics::Renderer& renderer, GFXEngine::Graphics::Camera& camera, uint32_t imageIndex) override;
			const Graphics::MeshModel& getMeshModel() const { return m_meshModel; }
		};
	}
}