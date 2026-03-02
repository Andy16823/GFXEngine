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
			UnlitMaterial(const std::string& texturePath, const GeometryPipeline& pipeline) 
				: m_texturePath(texturePath), m_pipeline(pipeline) {}

			void init(Renderer& renderer) override;
			void bind(Renderer& renderer, const Camera& camera, uint32_t imageIndex) const override;
			void destroy(Renderer& renderer) override;

			const LibGFX::Pipeline& getPipeline() const override { return m_pipeline; }

		private:
			LibGFX::Image m_texture;
			std::string m_texturePath;
			VkDescriptorSet m_textureDescriptorSet = VK_NULL_HANDLE;
			const GeometryPipeline& m_pipeline;
		};
	}
}
