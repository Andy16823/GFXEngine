#pragma once
#include "Material.h"
#include "GeometryPipeline.h"
#include "Imaging.h"


namespace GFXEngine {
	namespace Graphics {

		/// <summary>
		/// UnlitMaterial is a simple material that uses a single texture
		/// and does not interact with lighting. It is suitable for rendering objects 
		/// that should appear fully lit regardless of the scene's 
		/// lighting conditions, such as sprites or UI elements.
		/// </summary>
		class UnlitMaterial : public Material {

		public:
			UnlitMaterial(const std::string& texturePath) 
				: m_texturePath(texturePath) {}

			void init(Renderer& renderer) override;
			void bind(Renderer& renderer, const Camera& camera, const LibGFX::Pipeline& pipeline, uint32_t imageIndex) const override;
			void destroy(Renderer& renderer) override;

		private:
			LibGFX::Image m_texture;
			std::string m_texturePath;
			VkDescriptorSet m_textureDescriptorSet = VK_NULL_HANDLE;
		};
	}
}
