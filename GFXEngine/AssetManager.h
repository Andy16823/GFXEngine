#pragma once
#include "Asset.h"
#include <unordered_map>
#include <memory>
#include <functional>
#include <nlohmann/json.hpp>

namespace GFXEngine {

	/// <summary>
	/// Function type for asset loaders. An asset loader is a function that takes a file path and returns a unique pointer to an Asset.
	/// Parameters:
	/// 1: The name of the asset (derived from the file name without extension).
	/// 2: The file path of the asset to load.
	/// 3: Whether to load the asset lazily (i.e., defer loading until the asset is accessed).
	/// </summary>
	using AssetLoaderFunc = std::function<std::unique_ptr<Asset>(const std::string&, const std::filesystem::path&, bool)>;

	/// <summary>
	/// AssetManager is responsible for managing the lifecycle of assets in the engine. 
	/// </summary>
	class AssetManager
	{
	private:
		std::unordered_map<std::string, std::unique_ptr<Asset>> m_assets;
		std::unordered_map<std::string, AssetLoaderFunc> m_loaders;

	public:
		/// <summary>
		/// Load all assets from the specified directory.
		/// </summary>
		/// <param name="directory">The directory to load assets from.</param>
		/// <param name="recursive">Whether to load assets from subdirectories.</param>
		/// <param name="lazy">Whether to load assets lazily.</param>
		void loadFromDirectory(const std::filesystem::path& directory, bool recursive = true, bool lazy = false);

		/// <summary>
		/// Load a single asset from the specified file path. The type of asset is determined by the file extension and the registered loaders.
		/// </summary>
		/// <param name="filePath">The file path of the asset to load.</param>
		/// <param name="lazy">Whether to load the asset lazily.</param>
		/// <returns>The loaded asset, or nullptr if the asset could not be loaded.</returns>
		Asset* loadFromFile(const std::filesystem::path& filePath, bool lazy = false);

		/// <summary>
		/// Unload all assets that implement the FileAsset interface. 
		/// This will free any resources associated with the loaded files, but will not remove the assets from the manager.
		/// </summary>
		void unloadAssets();

		/// <summary>
		/// Initialize graphics resources for all assets that implement the GraphicsAsset interface. 
		/// </summary>
		/// <param name="renderer"></param>
		void initializeGraphicsAssets(Graphics::Renderer& renderer);

		/// <summary>
		/// Destroy graphics resources for all assets that implement the GraphicsAsset interface.
		/// </summary>
		/// <param name="renderer"></param>
		void destroyGraphicsAssets(Graphics::Renderer& renderer);

		/// <summary>
		/// Add an asset to the manager. The asset will be stored with its name as the key. If an asset with the same name already exists, it will be replaced.
		/// </summary>
		/// <param name="asset">The asset to add.</param>
		/// <returns>The added asset.</returns>
		Asset* addAsset(std::unique_ptr<Asset> asset) {
			auto name = asset->getName();
			return m_assets.emplace(name, std::move(asset)).first->second.get();
		}

		/// <summary>
		/// Remove an asset from the manager by name. If the asset does not exist, this function does nothing.
		/// </summary>
		/// <param name="name">The name of the asset to remove.</param>
		void removeAsset(const std::string& name) {
			m_assets.erase(name);
		}

		/// <summary>
		/// Get an asset by name and cast it to the specified type. 
		/// If the asset does not exist or cannot be cast to the specified type, this function returns nullptr. 
		/// If the asset is a FileAsset and is not loaded, it will be loaded before being returned.
		/// </summary>
		/// <typeparam name="T">The type to cast the asset to.</typeparam>
		/// <param name="name">The name of the asset to retrieve.</param>
		/// <returns>The asset cast to the specified type, or nullptr if the asset does not exist or cannot be cast.</returns>
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

		template<typename T>
		AssetHandle<T> getHandle(const std::string& name) {
			auto it = m_assets.find(name);
			if (it == m_assets.end()) {
				return AssetHandle<T>(nullptr);
			}

			auto* asset = dynamic_cast<T*>(it->second.get());
			if (!asset) {
				return AssetHandle<T>(nullptr);
			}

			if (auto* fileAsset = dynamic_cast<FileAsset*>(asset)) {
				if (!fileAsset->isLoaded()) {
					fileAsset->load();
				}
			}

			return AssetHandle<T>(asset);
		}

		/// <summary>
		/// Iterate over all assets and apply the given function to each asset. 
		/// This can be used for operations that need to be performed on all assets, such as initialization or cleanup.
		/// </summary>
		/// <param name="func">The function to apply to each asset.</param>
		void forEachAsset(const std::function<void(Asset*)>& func) {
			for (auto& pair : m_assets) {
				func(pair.second.get());
			}
		}

		/// <summary>
		/// Iterate over all assets of the specified type and apply the given function to each asset.
		/// This can be used for operations that need to be performed on all assets of a specific type, such as initialization or cleanup.
		/// </summary>
		/// <typeparam name="T"></typeparam>
		/// <param name="func"></param>
		template<typename T>
		void forEachAssetOfType(const std::function<void(T*)>& func) {
			for (auto& pair : m_assets) {
				if (auto asset = dynamic_cast<T*>(pair.second.get())) {
					func(asset);
				}
			}
		}

		/// <summary>
		/// Check if an asset with the given name exists in the manager.
		/// </summary>
		/// <param name="name"></param>
		/// <returns></returns>
		bool contains(const std::string& name) const {
			return m_assets.contains(name);
		}

		/// <summary>
		/// Clear all assets from the manager.
		/// </summary>
		void clear() {
			m_assets.clear();
			m_loaders.clear();
		}

		/// <summary>
		/// Register a loader function for a specific file extension.
		/// </summary>
		/// <param name="type">The file extension for which to register the loader.</param>
		/// <param name="loader">The loader function to register.</param>
		void registerLoader(const std::string& type, AssetLoaderFunc loader) {
			m_loaders[type] = std::move(loader);
		}
	};
}
