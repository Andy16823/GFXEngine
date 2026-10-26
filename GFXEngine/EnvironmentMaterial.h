#pragma once
#include "Material.h"
#include "OptionalRef.h"
#include "Imaging.h"

namespace GFXEngine {
	namespace Graphics {

		/// <summary>
		/// EnvironmentMaterial is a material that uses a cubemap for rendering. 
		/// It is used for skyboxes and reflections.
		/// </summary>
		class EnvironmentMaterial 
			: public Material
		{
		private:
			LibGFX::CubemapData m_cubemapData;
			LibGFX::Cubemap m_cubemap;
			VkDescriptorSet m_cubemapDescriptorSet;

		public:
			void init(Renderer& renderer) override;
			void destroy(Renderer& renderer) override;
			void updateMaterial(Renderer& renderer) override;
		public:
			VkDescriptorSet getDescriptorSet(uint32_t imageIndex) const override { return m_cubemapDescriptorSet; }
			void setCubemapData(LibGFX::CubemapData data) { m_cubemapData = std::move(data); }
		};
	}
}
