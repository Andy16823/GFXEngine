#pragma once
#include "Material.h"
#include "Imaging.h"
#include <string>

namespace GFXEngine {
	namespace Graphics {
		class PBRMaterial : public Material
		{
		public:
			PBRMaterial(const std::string& albedoPath, const std::string& normalPath, const std::string& metallicRoughnessPath, const std::string& aoPath)
				: m_albedoPath(albedoPath), m_normalPath(normalPath), m_metallicRoughnessPath(metallicRoughnessPath), m_aoPath(aoPath) {}

			void init(Renderer& renderer) override;
			void bind(Renderer& renderer, const Camera& camera, const LibGFX::Pipeline& pipeline, uint32_t imageIndex) const override;
			void destroy(Renderer& renderer) override;
		private:
			const std::string m_albedoPath;
			const std::string m_normalPath;
			const std::string m_metallicRoughnessPath;
			const std::string m_aoPath;

			LibGFX::Image m_albedo;
			LibGFX::Image m_normal;
			LibGFX::Image m_metallicRoughness;
			LibGFX::Image m_ao;

			VkDescriptorSet m_descriptorSet = VK_NULL_HANDLE;

		};
	}
}