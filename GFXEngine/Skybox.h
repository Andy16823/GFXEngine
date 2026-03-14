#pragma once
#include "Entity.h"
#include "Imaging.h"
#include "EnviromentPipeline.h"

// TODO: Create basemesh class and then let mesh inherit from it, and also create an simple mesh class that just takes in vertices and indices and creates a basemesh, then let skybox inherit from basemesh instead of entity, since it doesn't need materials or multiple meshes. This will also make it easier to implement other simple entities in the future like a fullscreen quad for post processing effects, or a simple cube for testing.
namespace GFXEngine {
	namespace Core {
		class Skybox : public Entity
		{
		public:
			Skybox(const LibGFX::Cubemap& cubemap, const Graphics::EnviromentPipeline& pipeline) 
				: m_cubemap(cubemap), m_pipeline(pipeline) {}

			void init(Scene& scene, GFXEngine::Graphics::Renderer& renderer) override;
			void render(Scene& scene, GFXEngine::Graphics::Renderer& renderer, GFXEngine::Graphics::Camera& camera, uint32_t imageIndex) override;
			void destroy(Scene& scene, GFXEngine::Graphics::Renderer& renderer) override;

			size_t getMeshCount() const override;
			std::pair<const Graphics::Mesh&, const Graphics::Material&> getMeshAndMaterial(size_t index) const override;
		private:
			const Graphics::EnviromentPipeline& m_pipeline;
			const LibGFX::Cubemap& m_cubemap;
			VkDescriptorSet m_cubemapDescriptorSet;
			LibGFX::Buffer m_vertexBuffer;
			LibGFX::Buffer m_indexBuffer;
		};
	}
}