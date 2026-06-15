#pragma once
#include <string>
#include <cassert>
#include <concepts>

namespace GFXEngine {

	/// <summary>
	/// Forward declaration of the Renderer class to avoid circular dependencies.
	/// </summary>
	namespace Graphics {
		class Renderer;
	}

	/// <summary>
	/// Base class for all assets in the engine. Each asset has a unique identifier (UUID) and can be extended to represent specific types of assets such as textures, meshes, materials, etc.
	/// </summary>
	class Asset
	{
	protected:
		std::string m_uuid;
		std::string m_name;
		uint32_t m_refCount = 0;

	public:
		Asset(const std::string& name);
		virtual ~Asset() = default;
		const std::string& getUUID() const { return m_uuid; }
		const std::string& getName() const { return m_name; }

		void incrementRefCount() { ++m_refCount; }
		void decrementRefCount() { 
			assert(m_refCount > 0 && "Reference count cannot be negative");
			--m_refCount; 
		}

		template<typename T>
		T* as() {
			return dynamic_cast<T*>(this);
		}
	};

	/// <summary>
	/// FileAsset interface represents that the asset can be loaded from a file.
	/// </summary>
	class FileAsset
	{
	private:
		std::string m_filePath;

	public:
		FileAsset(const std::string& filePath) : m_filePath(filePath) {}
		virtual ~FileAsset() = default;
		virtual void load() = 0;
		virtual bool isLoaded() const = 0;
		virtual void unload() = 0;
		const std::string& getFilePath() const { return m_filePath; }
	};
	
	/// <summary>
	/// GraphicsAsset interface represents that the asset has GPU resources that need to be initialized and destroyed with the renderer.
	/// </summary>
	class GraphicsAsset
	{
	public:
		virtual ~GraphicsAsset() = default;

		virtual void init(Graphics::Renderer& renderer) = 0;
		virtual void destroy(Graphics::Renderer& renderer) = 0;
		virtual bool isInitialized() const = 0;
	};

	/// <summary>
	/// AssetHandle is a smart pointer-like class that manages the reference counting of an Asset. 
	/// It ensures that the reference count is properly incremented and decremented when the handle is created, copied, or destroyed. 
	/// This allows for safe sharing of assets across different parts of the engine without worrying about manual memory management.
	/// </summary>
	/// <typeparam name="T"></typeparam>
	template<std::derived_from<Asset> T>
	class AssetHandle
	{
	private:
		T* m_asset = nullptr;

	public:
		AssetHandle() = default;

		explicit AssetHandle(T* asset)
			: m_asset(asset)
		{
			if (m_asset)
			{
				m_asset->incrementRefCount();
			}
		}

		AssetHandle(AssetHandle&& other) noexcept
			: m_asset(other.m_asset)
		{
			other.m_asset = nullptr; // Prevent the moved-from handle from decrementing the ref count
		}

		AssetHandle& operator=(AssetHandle&& other) noexcept
		{
			if (this != &other) 
			{
				if (m_asset)
				{
					m_asset->decrementRefCount();
				}
				m_asset = other.m_asset;
				other.m_asset = nullptr;
			}

			return *this;
		}

		AssetHandle(const AssetHandle& other)
			: m_asset(other.m_asset)
		{
			if (m_asset)
			{
				m_asset->incrementRefCount();
			}
		}

		AssetHandle& operator=(const AssetHandle& other) 
		{
			if (this != &other) 
			{
				if (m_asset)
				{
					m_asset->decrementRefCount();
				}
				m_asset = other.m_asset;
				if (m_asset)
				{
					m_asset->incrementRefCount();
				}
			}

			return *this;
		}

		~AssetHandle()
		{
			if (m_asset)
			{
				m_asset->decrementRefCount();
			}
		}

		void set(T* asset)
		{
			if (m_asset == asset)
			{
				return;
			}

			if (m_asset)
			{
				m_asset->decrementRefCount();
			}

			m_asset = asset;

			if (m_asset)
			{
				m_asset->incrementRefCount();
			}
		}

		void release()
		{
			if (m_asset)
			{
				m_asset->decrementRefCount();
				m_asset = nullptr;
			}
		}

		T* get() const
		{
			return m_asset;
		}

		T* operator->() const
		{
			return m_asset;
		}

		T& operator*() const
		{
			return *m_asset;
		}

		explicit operator bool() const
		{
			return m_asset != nullptr;
		}
	};
	
}