#pragma once
#include "Material.h"
#include "GeometryPipeline.h"
#include "Imaging.h"
#include <string>

namespace GFXEngine {
	namespace Graphics {

		/// <summary>
		/// SpriteMaterial is a concrete implementation of the Material interface for rendering textured sprites. 
		/// It manages its own texture resource and descriptor set for binding the texture to the shader.
		/// </summary>
		class SpriteMaterial : public Material {
		private:
			std::string m_texturePath;
			LibGFX::Image m_texture;
			VkDescriptorSet m_textureDescriptorSet = VK_NULL_HANDLE;

		public:
			SpriteMaterial(const std::string& texturePath) : m_texturePath(texturePath) {}
			void init(Renderer& renderer) override;
			void bind(Renderer& renderer, VkPipelineLayout pipelineLayout, uint32_t imageIndex, uint32_t firstSet) const override;
			void destroy(Renderer& renderer) override;
		};
	}
}