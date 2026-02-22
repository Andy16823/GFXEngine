#pragma once
#include "Material.h"
#include "GeometryPipeline.h"
#include "Imaging.h"


namespace GFXEngine {
	namespace Graphics {
		class UnlitMaterial : public Material {
		private:
			const GeometryPipeline& m_pipeline;
			LibGFX::Image m_texture;
			VkDescriptorSet m_textureDescriptorSet = VK_NULL_HANDLE;
			std::string m_texturePath;

		public:
			UnlitMaterial(const std::string& texturePath, const GeometryPipeline& pipeline) : m_texturePath(texturePath), m_pipeline(pipeline) {}
			void init(Renderer& renderer) override;
			void bind(Renderer& renderer, Camera& camera, uint32_t imageIndex) const override;
			void destroy(Renderer& renderer) override;
			VkPipelineLayout getPipelineLayout() const override;
		};
	}
}
