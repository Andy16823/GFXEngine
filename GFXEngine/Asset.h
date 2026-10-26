#pragma once
#include <string>
#include <typeindex>

namespace GFXEngine {

	namespace Graphics {
		class Renderer;
	}

	/// <summary>
	/// Ass
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

		template<typename T>
		T* as() {
			return dynamic_cast<T*>(this);
		}

		void increaseRef() {
			m_refCount++;
		}

		void decreaseRef() {
			if (m_refCount > 0) {
				m_refCount--;
			}
		}

		uint32_t getRefCount() const { return m_refCount; }

		bool isReferenced() const {	return m_refCount > 0; }
	};

	/// <summary>
	/// FileAsset interface represents that the asset can be loaded from a file.
	/// </summary>
	class FileAsset
	{
	private:
		std::string m_filePath;

	public:
		virtual ~FileAsset() = default;

	public:
		virtual void load() = 0;
		virtual bool isLoaded() const = 0;
		virtual void unload() = 0;
		
	public:
		void setFilePath(const std::string& filePath) { m_filePath = filePath; }
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
	/// AssetHandle for accessing assets
	/// </summary>
	class AssetHandle {
		private:
			GFXEngine::Asset* m_asset = nullptr;

	public:
		
		explicit AssetHandle(GFXEngine::Asset* asset)
			: m_asset(asset)
		{
			if (m_asset)
				m_asset->increaseRef();
		}

		AssetHandle(const AssetHandle& other)
			: m_asset(other.m_asset)
		{
			if (m_asset)
				m_asset->increaseRef();
		}

		AssetHandle& operator=(const AssetHandle& other)
		{
			if (this == &other)
				return *this;

			// Free old asset
			if (m_asset)
				m_asset->decreaseRef();

			// Assign new asset
			m_asset = other.m_asset;

			if (m_asset)
				m_asset->increaseRef();

			return *this;
		}

		AssetHandle& operator=(AssetHandle&& other) noexcept
		{
			if (this == &other)
				return *this;

			// free current reference
			if (m_asset)
				m_asset->decreaseRef();

			// assign pointer
			m_asset = other.m_asset;

			// remove other asset
			other.m_asset = nullptr;

			return *this;
		}

		GFXEngine::Asset* operator->() const
		{
			return m_asset;
		}

		explicit operator bool() const
		{
			return m_asset != nullptr;
		}

		AssetHandle(AssetHandle&& other) noexcept
			: m_asset(other.m_asset)
		{
			other.m_asset = nullptr;
		}

		~AssetHandle() {
			if (m_asset)
				m_asset->decreaseRef();
		}

		GFXEngine::Asset* get() const {
			return m_asset;
		}

		void replace(Asset* asset) {

			if (m_asset == asset)
				return;

			if (m_asset)
				m_asset->decreaseRef();
			
			asset->increaseRef();
			m_asset = asset;
		}

		template<typename T>
		T* as() const {
			if (T* cast = dynamic_cast<T*>(m_asset)) {
				return cast;
			}
			return nullptr;
		}

		template<typename T>
		T* unsafeAs() const {
			return static_cast<T*>(m_asset);
		}
	};
}