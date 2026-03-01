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

		public:
			UnlitMaterial(const std::string& texturePath) 
				: m_texturePath(texturePath) {}

			void init(Renderer& renderer) override;
			void bind(Renderer& renderer, VkPipelineLayout pipelineLayout, uint32_t imageIndex, uint32_t firstSet) const override;
			void destroy(Renderer& renderer) override;
		};
	}
}
