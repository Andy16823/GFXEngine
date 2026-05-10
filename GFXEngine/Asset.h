#pragma once
#include <string>

namespace GFXEngine {
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
	};
}