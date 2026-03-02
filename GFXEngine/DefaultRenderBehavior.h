#pragma once
#include "Behavior.h"
#include "GeometryPipeline.h"

namespace GFXEngine {
	namespace Core {
		/// <summary>
		/// Default render behavior that does nothing.
		/// </summary>
		class DefaultRenderBehavior : public Behavior {
		public:
			DefaultRenderBehavior(const Graphics::GeometryPipeline& pipeline) : m_pipeline(pipeline) {}
			void init(Graphics::Renderer& renderer) override;
			void update(float deltaTime) override;
			void render(Graphics::Renderer& renderer, Graphics::Camera& camera, uint32_t imageIndex) override;
			void destroy(Graphics::Renderer& renderer) override;
		private:
			const Graphics::GeometryPipeline& m_pipeline;
		};
	}
}
