#pragma once
#include "Material.h"
#include "OptionalRef.h"
#include "Imaging.h"

namespace GFXEngine {
	namespace Graphics {
		class EnviromentMaterial : public Material
		{
		private:
			LibGFX::CubemapData m_cubemapData;
			LibGFX::Cubemap m_cubemap;
			VkDescriptorSet m_cubemapDescriptorSet;

		public:
			void init(Renderer& renderer) override;
			void destroy(Renderer& renderer) override;
			void contributeToRenderTask(RenderTaskBuilder& builder, const RenderContext& context) const override;

			void setCubemapData(LibGFX::CubemapData data) { m_cubemapData = std::move(data); }
		};
	}
}
