#pragma once
#include "Asset.h"
#include <unordered_map>
#include <memory>
#include <functional>

namespace GFXEngine {

	/// <summary>
	/// AssetManager is responsible for managing the lifecycle of assets in the engine. 
	/// </summary>
	class AssetManager
	{
	private:
		std::unordered_map<std::string, std::unique_ptr<Asset>> m_assets;

	public:
		bool addAsset(std::unique_ptr<Asset> asset) {
			auto name = asset->getName();
			return m_assets.emplace(name, std::move(asset)).second;
		}

		void removeAsset(const std::string& name) {
			m_assets.erase(name);
		}

		Asset* getAsset(const std::string& name) {
			auto it = m_assets.find(name);
			if (it != m_assets.end()) {
				return it->second.get();
			}
			return nullptr;
		}

		template<typename T>
		T* getAssetOfType(const std::string& name) {
			auto it = m_assets.find(name);

			if (it == m_assets.end()) {
				return nullptr;
			}

			return dynamic_cast<T*>(it->second.get());
		}

		void forEachAsset(const std::function<void(Asset&)>& func) {
			for (auto& pair : m_assets) {
				func(*pair.second);
			}
		}

		template<typename T>
		void forEachAssetOfType(const std::function<void(T&)>& func) {
			for (auto& pair : m_assets) {
				if (auto asset = dynamic_cast<T*>(pair.second.get())) {
					func(*asset);
				}
			}
		}

		bool contains(const std::string& name) const {
			return m_assets.contains(name);
		}

		void clear() {
			m_assets.clear();
		}
	};
}
