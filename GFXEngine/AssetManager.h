#pragma once
#include "Asset.h"
#include <unordered_map>
#include <memory>
#include <functional>
#include <nlohmann/json.hpp>

namespace GFXEngine {

	using AssetLoaderFunc = std::function<std::unique_ptr<Asset>(const std::string&, const std::filesystem::path&, bool)>;

	class AssetManager
	{
	private:
		std::unordered_map<std::string, std::unique_ptr<Asset>> m_assets;
		std::unordered_map<std::string, AssetLoaderFunc> m_loaders;

	public:
		
		//************************************
		// Method:    loadFromDirectory
		// FullName:  GFXEngine::AssetManager::loadFromDirectory
		// Access:    public 
		// Returns:   void
		// Qualifier:
		// Parameter: const std::filesystem::path & directory
		// Parameter: bool recursive
		// Parameter: bool lazy
		//************************************
		void loadFromDirectory(const std::filesystem::path& directory, bool recursive = true, bool lazy = false);

		//************************************
		// Method:    loadFromFile
		// FullName:  GFXEngine::AssetManager::loadFromFile
		// Access:    public 
		// Returns:   GFXEngine::Asset*
		// Qualifier:
		// Parameter: const std::filesystem::path & filePath
		// Parameter: bool lazy
		//************************************
		Asset* loadFromFile(const std::filesystem::path& filePath, bool lazy = false);

		//************************************
		// Method:    unloadAssets
		// FullName:  GFXEngine::AssetManager::unloadAssets
		// Access:    public 
		// Returns:   void
		// Qualifier:
		//************************************
		void unloadAssets();

		//************************************
		// Method:    initializeGraphicsAssets
		// FullName:  GFXEngine::AssetManager::initializeGraphicsAssets
		// Access:    public 
		// Returns:   void
		// Qualifier:
		// Parameter: Graphics::Renderer & renderer
		//************************************
		void initializeGraphicsAssets(Graphics::Renderer& renderer);

		//************************************
		// Method:    destroyGraphicsAssets
		// FullName:  GFXEngine::AssetManager::destroyGraphicsAssets
		// Access:    public 
		// Returns:   void
		// Qualifier:
		// Parameter: Graphics::Renderer & renderer
		//************************************
		void destroyGraphicsAssets(Graphics::Renderer& renderer);

		//************************************
		// Method:    addAsset
		// FullName:  GFXEngine::AssetManager::addAsset
		// Access:    public 
		// Returns:   GFXEngine::Asset*
		// Qualifier:
		// Parameter: std::unique_ptr<Asset> asset
		//************************************
		Asset* addAsset(std::unique_ptr<Asset> asset) {
			auto name = asset->getName();
			return m_assets.emplace(name, std::move(asset)).first->second.get();
		}

		//************************************
		// Method:    removeAsset
		// FullName:  GFXEngine::AssetManager::removeAsset
		// Access:    public 
		// Returns:   void
		// Qualifier:
		// Parameter: const std::string & name
		//************************************
		void removeAsset(const std::string& name) {
			m_assets.erase(name);
		}

		//************************************
		// Method:    get
		// FullName:  GFXEngine::AssetManager::get
		// Access:    public 
		// Returns:   T*
		// Qualifier:
		// Parameter: const std::string & name
		//************************************
		template<typename T>
		T* get(const std::string& name) {
			auto it = m_assets.find(name);

			if (it == m_assets.end()) {
				return nullptr;
			}

			auto* asset = dynamic_cast<T*>(it->second.get());
			if (!asset) 
			{
				return nullptr;
			}

			if (auto* fileAsset = dynamic_cast<FileAsset*>(asset)) 
			{
				if (!fileAsset->isLoaded()) {
					fileAsset->load();
				}
			}

			return asset;
		}

		//************************************
		// Method:    forEachAsset
		// FullName:  GFXEngine::AssetManager::forEachAsset
		// Access:    public 
		// Returns:   void
		// Qualifier:
		// Parameter: const std::function<void
		// Parameter: Asset * 
		// Parameter: > & func
		//************************************
		void forEachAsset(const std::function<void(Asset*)>& func) {
			for (auto& pair : m_assets) {
				func(pair.second.get());
			}
		}

		//************************************
		// Method:    forEachAssetOfType
		// FullName:  GFXEngine::AssetManager::forEachAssetOfType
		// Access:    public 
		// Returns:   void
		// Qualifier:
		// Parameter: const std::function<void
		// Parameter: T * 
		// Parameter: > & func
		//************************************
		template<typename T>
		void forEachAssetOfType(const std::function<void(T*)>& func) {
			for (auto& pair : m_assets) {
				if (auto asset = dynamic_cast<T*>(pair.second.get())) {
					func(asset);
				}
			}
		}

		//************************************
		// Method:    contains
		// FullName:  GFXEngine::AssetManager::contains
		// Access:    public 
		// Returns:   bool
		// Qualifier: const
		// Parameter: const std::string & name
		//************************************
		bool contains(const std::string& name) const {
			return m_assets.contains(name);
		}

		//************************************
		// Method:    clear
		// FullName:  GFXEngine::AssetManager::clear
		// Access:    public 
		// Returns:   void
		// Qualifier:
		//************************************
		void clear() {
			m_assets.clear();
			m_loaders.clear();
		}

		//************************************
		// Method:    registerLoader
		// FullName:  GFXEngine::AssetManager::registerLoader
		// Access:    public 
		// Returns:   void
		// Qualifier:
		// Parameter: const std::string & type
		// Parameter: AssetLoaderFunc loader
		//************************************
		void registerLoader(const std::string& type, AssetLoaderFunc loader) {
			m_loaders[type] = std::move(loader);
		}
	};
}
