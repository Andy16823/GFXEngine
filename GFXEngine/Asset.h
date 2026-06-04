#pragma once
#include <string>

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
	public:
		Asset(const std::string& name);
		virtual ~Asset() = default;
		const std::string& getUUID() const { return m_uuid; }
		const std::string& getName() const { return m_name; }

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
	public:
		virtual ~FileAsset() = default;
		virtual void load(const std::string& filePath) = 0;
		virtual bool isLoaded() const = 0;
		virtual const std::string& getFilePath() const = 0;
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
}