#pragma once
#include "Asset.h"
#include "Material.h"
#include <memory>

namespace GFXEngine {
	namespace Graphics {

		/// <summary>
		/// MaterialAsset is a specialized Asset that holds a Material instance. 
		/// The MaterialAsset can created from a Material instance or loaded from a JSON file.
		/// </summary>
		class MaterialAsset 
			: public Asset, public GraphicsAsset, public FileAsset {

		private:
			bool m_initialized = false;
			std::unique_ptr<Material> m_material = nullptr;

		public:
			MaterialAsset(const std::string& name) : Asset(name) {}
			MaterialAsset(const std::string& name, std::unique_ptr<Material> material)
				: Asset(name), m_material(std::move(material)) {}

		public:
			void init(Graphics::Renderer& renderer) override;
			void destroy(Graphics::Renderer& renderer) override;
			bool isInitialized() const override { return m_initialized; }
			Material* getMaterial() const { return m_material.get(); }

		public:
			void load() override;
			bool isLoaded() const override;
			void unload() override;
		};
	}
}