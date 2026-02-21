#pragma once
#include "Material.h"
#include "MeshPipeline.h"
#include "Imaging.h"
#include <string>

namespace GFXEngine {
	namespace Graphics {
		class SpriteMaterial : public Material {
		private:
			const MeshPipeline& m_pipeline;
			std::string m_texturePath;
			LibGFX::Image m_texture;
			VkDescriptorSet m_textureDescriptorSet;

		public:
			SpriteMaterial(const std::string& texturePath, const MeshPipeline& pipeline) : m_texturePath(texturePath), m_pipeline(pipeline) {}
			void init(Renderer& renderer) override;
			void bind(Renderer& renderer, Camera3D& camera, uint32_t imageIndex) override;
			void destroy(Renderer& renderer) override;
			VkPipelineLayout getPipelineLayout() const override { return m_pipeline.getPipelineLayout(); }
		};
	}
}
