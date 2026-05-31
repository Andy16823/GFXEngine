#include "AssetManager.h"
#include "Utils.h"
#include <stdexcept>
#include <iostream>

void GFXEngine::AssetManager::loadFromDirectory(const std::filesystem::path& directory, bool recursive /*= true*/)
{
	if (!std::filesystem::exists(directory) || !std::filesystem::is_directory(directory)) 
	{
		throw std::runtime_error("Directory does not exist: " + directory.string());
	}

	for (const auto& entry : std::filesystem::directory_iterator(directory))
	{
		if (entry.is_directory() && recursive)
		{
			loadFromDirectory(entry.path(), recursive);
		}
		else if (entry.is_regular_file())
		{
			std::string extension = entry.path().extension().string();
			std::string filename = entry.path().filename().string();
			std::string name = entry.path().stem().string();		

			if (m_loaders.contains(extension)) 
			{
				// If a loader exists we assume the file is a JSON file containing the necessary data to create the asset.
				nlohmann::json data = Utils::loadJsonFromFile(entry.path().string());
				m_loaders[extension](name, data);
				std::cout << "Loaded asset '" << name << "' from file: " << entry.path() << std::endl;
			}
		}
	}
}
