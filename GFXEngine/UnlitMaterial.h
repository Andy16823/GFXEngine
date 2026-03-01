#pragma once
#include "Material.h"
#include "GeometryPipeline.h"
#include "Imaging.h"


namespace GFXEngine {
	namespace Graphics {

		/// <summary>
		/// UnlitMaterial is a simple material that renders textured geometry without any lighting calculations.
		/// </summary>
		class UnlitMaterial : public Material {
		private:
			LibGFX::Image m_texture;
			std::string m_texturePath;
			VkDescriptorSet m_textureDescriptorSet = VK_NULL_HANDLE;
			const GeometryPipeline& m_pipeline;

		public:
			UnlitMaterial(const std::string& texturePath, const GeometryPipeline& pipeline) : m_texturePath(texturePath), m_pipeline(pipeline) {}

			void init(Renderer& renderer) override;
			void bind(Renderer& renderer, uint32_t imageIndex, uint32_t firstSet) const override;
			void destroy(Renderer& renderer) override;

			const LibGFX::Pipeline& getPipeline() const override { return m_pipeline; }
		};
	}
}
