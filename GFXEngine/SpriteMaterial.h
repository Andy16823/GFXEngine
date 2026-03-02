#pragma once
#include "Material.h"
#include "GeometryPipeline.h"
#include "Imaging.h"
#include <string>

namespace GFXEngine {
	namespace Graphics {

		/// <summary>
		/// Material class specifically designed for rendering sprites. 
		/// It manages a texture and its associated descriptor set, 
		/// and uses a geometry pipeline for rendering.
		/// </summary>
		class SpriteMaterial : public Material {

		public:
			SpriteMaterial(const std::string& texturePath) 
				: m_texturePath(texturePath) {}

			void init(Renderer& renderer) override;
			void bind(Renderer& renderer, const Camera& camera, const LibGFX::Pipeline& pipeline, uint32_t imageIndex) const override;
			void destroy(Renderer& renderer) override;

		private:
			std::string m_texturePath;
			LibGFX::Image m_texture;
			VkDescriptorSet m_textureDescriptorSet = VK_NULL_HANDLE;
		};
	}
}