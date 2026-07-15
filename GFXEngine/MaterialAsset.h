#pragma once
#include "Asset.h"
#include "Material.h"
#include <memory>

namespace GFXEngine {
	namespace Graphics {
		class MaterialAsset : public Asset, public GraphicsAsset {
		private:
			bool m_initialized = false;
			std::unique_ptr<Material> m_material;

		public:
			MaterialAsset(const std::string& name, std::unique_ptr<Material> material)
				: Asset(name), m_material(std::move(material)) {}

		public:
			void init(Graphics::Renderer& renderer) override;
			void destroy(Graphics::Renderer& renderer) override;
			bool isInitialized() const override { return m_initialized; }
			Material* getMaterial() const { return m_material.get(); }
		};
	}
}