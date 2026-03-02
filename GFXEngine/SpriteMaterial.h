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
		private:
			std::string m_texturePath;
			LibGFX::Image m_texture;
			VkDescriptorSet m_textureDescriptorSet = VK_NULL_HANDLE;
			const GeometryPipeline& m_pipeline;

		public:
			SpriteMaterial(const std::string& texturePath, const GeometryPipeline& pipeline) 
				: m_texturePath(texturePath), m_pipeline(pipeline) {}

			void init(Renderer& renderer) override;
			void bind(Renderer& renderer, const Camera& camera, uint32_t imageIndex) const override;
			void destroy(Renderer& renderer) override;
			
			const LibGFX::Pipeline& getPipeline() const override { return m_pipeline; }
		};
	}
}