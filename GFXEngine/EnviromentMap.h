#pragma once
#include "Entity.h"
#include "Imaging.h"
#include "Asset.h"
#include "IRenderable.h"

// TODO: Create basemesh class and then let mesh inherit from it, and also create an simple mesh class that just takes in vertices and indices and creates a basemesh, then let skybox inherit from basemesh instead of entity, since it doesn't need materials or multiple meshes. This will also make it easier to implement other simple entities in the future like a fullscreen quad for post processing effects, or a simple cube for testing.
namespace GFXEngine {
	namespace Graphics {
		class EnviromentMap : public GFXEngine::Asset, public GFXEngine::Graphics::IRenderable
		{
		public:
			EnviromentMap(const std::string& name, const std::vector<std::string>& faceFilepaths) : Asset(name), m_faceFilepaths(faceFilepaths) {}

			void init(GFXEngine::Graphics::Renderer& renderer);
			void buildRenderTasks(GFXEngine::Graphics::RenderContext& context, GFXEngine::Graphics::RenderQueue& renderQueue) override;
			void destroy(GFXEngine::Graphics::Renderer& renderer);

		private:
			std::vector<std::string> m_faceFilepaths;
			LibGFX::Cubemap m_cubemap;

			VkDescriptorSet m_cubemapDescriptorSet;
			LibGFX::Buffer m_vertexBuffer;
			LibGFX::Buffer m_indexBuffer;

		};
	}
}