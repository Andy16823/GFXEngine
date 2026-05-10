#pragma once
#include "Asset.h"
#include <unordered_map>
#include <memory>

namespace GFXEngine {

	/// <summary>
	/// AssetManager is responsible for managing the lifecycle of assets in the engine. 
	/// </summary>
	class AssetManager
	{
	private:
		std::unordered_map<std::string, std::unique_ptr<Asset>> m_assets;

	public:
		void addAsset(std::unique_ptr<Asset> asset) {
			m_assets[asset->getName()] = std::move(asset);
		}

		void removeAsset(const std::string& name) {
			m_assets.erase(name);
		}

		Asset* getAsset(const std::string& name) const {
			auto it = m_assets.find(name);
			if (it != m_assets.end()) {
				return it->second.get();
			}
			return nullptr;
		}
	};
}
