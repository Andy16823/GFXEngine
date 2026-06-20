#pragma once
#include <string>

namespace GFXEngine {

	namespace Graphics {
		class Renderer;
	}

	class Asset
	{
	protected:
		std::string m_uuid;
		std::string m_name;
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
}