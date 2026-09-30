#pragma once
#include <string>
#include <typeindex>

namespace GFXEngine {

	namespace Graphics {
		class Renderer;
	}

	class Asset
	{
	protected:
		std::string m_uuid;
		std::string m_name;
		uint32_t m_refCount = 0;
	public:
		
		//************************************
		// Method:    Asset
		// FullName:  GFXEngine::Asset::Asset
		// Access:    public 
		// Returns:   
		// Qualifier:
		// Parameter: const std::string & name
		//************************************
		Asset(const std::string& name);
		
		//************************************
		// Method:    ~Asset
		// FullName:  GFXEngine::Asset::~Asset
		// Access:    virtual public 
		// Returns:   
		// Qualifier:
		//************************************
		virtual ~Asset() = default;
		
		//************************************
		// Method:    getUUID
		// FullName:  GFXEngine::Asset::getUUID
		// Access:    public 
		// Returns:   const std::string&
		// Qualifier: const
		//************************************
		const std::string& getUUID() const { return m_uuid; }
		
		//************************************
		// Method:    getName
		// FullName:  GFXEngine::Asset::getName
		// Access:    public 
		// Returns:   const std::string&
		// Qualifier: const
		//************************************
		const std::string& getName() const { return m_name; }

		//************************************
		// Method:    as
		// FullName:  GFXEngine::Asset::as
		// Access:    public 
		// Returns:   T*
		// Qualifier:
		//************************************
		template<typename T>
		T* as() {
			return dynamic_cast<T*>(this);
		}

		//************************************
		// Method:    increaseRef
		// FullName:  GFXEngine::Asset::increaseRef
		// Access:    public 
		// Returns:   void
		// Qualifier:
		//************************************
		void increaseRef() {
			m_refCount++;
		}

		//************************************
		// Method:    decreaseRef
		// FullName:  GFXEngine::Asset::decreaseRef
		// Access:    public 
		// Returns:   void
		// Qualifier:
		//************************************
		void decreaseRef() {
			if (m_refCount > 0) {
				m_refCount--;
			}
		}

		//************************************
		// Method:    getRefCount
		// FullName:  GFXEngine::Asset::getRefCount
		// Access:    public 
		// Returns:   uint32_t
		// Qualifier: const
		//************************************
		uint32_t getRefCount() const { return m_refCount; }

		//************************************
		// Method:    isReferenced
		// FullName:  GFXEngine::Asset::isReferenced
		// Access:    public 
		// Returns:   bool
		// Qualifier: const
		//************************************
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
		
		//************************************
		// Method:    FileAsset
		// FullName:  GFXEngine::FileAsset::FileAsset
		// Access:    public 
		// Returns:   
		// Qualifier: : m_filePath(filePath)
		// Parameter: const std::string & filePath
		//************************************
		FileAsset(const std::string& filePath) : m_filePath(filePath) {}
		
		//************************************
		// Method:    ~FileAsset
		// FullName:  GFXEngine::FileAsset::~FileAsset
		// Access:    virtual public 
		// Returns:   
		// Qualifier:
		//************************************
		virtual ~FileAsset() = default;
		
		//************************************
		// Method:    load
		// FullName:  GFXEngine::FileAsset::load
		// Access:    virtual public 
		// Returns:   void
		// Qualifier:
		//************************************
		virtual void load() = 0;
		
		//************************************
		// Method:    isLoaded
		// FullName:  GFXEngine::FileAsset::isLoaded
		// Access:    virtual public 
		// Returns:   bool
		// Qualifier: const
		//************************************
		virtual bool isLoaded() const = 0;
		
		//************************************
		// Method:    unload
		// FullName:  GFXEngine::FileAsset::unload
		// Access:    virtual public 
		// Returns:   void
		// Qualifier:
		//************************************
		virtual void unload() = 0;
		
		//************************************
		// Method:    getFilePath
		// FullName:  GFXEngine::FileAsset::getFilePath
		// Access:    public 
		// Returns:   const std::string&
		// Qualifier: const
		//************************************
		const std::string& getFilePath() const { return m_filePath; }
	};
	
	/// <summary>
	/// GraphicsAsset interface represents that the asset has GPU resources that need to be initialized and destroyed with the renderer.
	/// </summary>
	class GraphicsAsset
	{
	public:

		//************************************
		// Method:    ~GraphicsAsset
		// FullName:  GFXEngine::GraphicsAsset::~GraphicsAsset
		// Access:    virtual public 
		// Returns:   
		// Qualifier:
		//************************************
		virtual ~GraphicsAsset() = default;

		//************************************
		// Method:    init
		// FullName:  GFXEngine::GraphicsAsset::init
		// Access:    virtual public 
		// Returns:   void
		// Qualifier:
		// Parameter: Graphics::Renderer & renderer
		//************************************
		virtual void init(Graphics::Renderer& renderer) = 0;

		//************************************
		// Method:    destroy
		// FullName:  GFXEngine::GraphicsAsset::destroy
		// Access:    virtual public 
		// Returns:   void
		// Qualifier:
		// Parameter: Graphics::Renderer & renderer
		//************************************
		virtual void destroy(Graphics::Renderer& renderer) = 0;
		
		//************************************
		// Method:    isInitialized
		// FullName:  GFXEngine::GraphicsAsset::isInitialized
		// Access:    virtual public 
		// Returns:   bool
		// Qualifier: const
		//************************************
		virtual bool isInitialized() const = 0;
	};

	/// <summary>
	/// AssetReference is a simple structure that holds a non-owning pointer to an Asset, allowing entities to reference assets without owning them directly.
	/// </summary>
	struct AssetReference
	{
		std::type_index assetType = typeid(void);
		void* asset = nullptr;

		operator bool() const {
			return asset != nullptr;
		}

		template<typename T>
		void set(T* assetPtr) {
			static_assert(std::derived_from<T, class GFXEngine::Asset>, "AssetReference can only hold pointers to Asset-derived types");
			assetType = typeid(T);
			asset = assetPtr;
			assetPtr->increaseRef();
		}

		template <typename T>
		T* get() const {
			if (assetType == typeid(T)) {
				return static_cast<T*>(asset);
			}
			return nullptr;
		}

		template <typename T>
		bool isTypeOf() const {
			return assetType == typeid(T);
		}

		void clear() {
			static_cast<Asset*>(asset)->decreaseRef();
			assetType = typeid(void);
			asset = nullptr;

		}
	};

}