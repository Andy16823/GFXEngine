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
			this->loadFromFile(entry.path());
		}
	}
}

void GFXEngine::AssetManager::loadFromFile(const std::filesystem::path& filePath)
{
	if (!std::filesystem::exists(filePath) || !std::filesystem::is_regular_file(filePath))
	{
		throw std::runtime_error("File does not exist: " + filePath.string());
	}

	std::string extension = filePath.extension().string();
	std::string filename = filePath.filename().string();
	std::string name = filePath.stem().string();

	if (m_loaders.contains(extension))
	{
		// If a loader exists we assume the file is a JSON file containing the necessary data to create the asset.
		auto asset = m_loaders[extension](name, filePath);
		this->addAsset(std::move(asset));
		std::cout << "Loaded asset '" << name << "' from file: " << filePath << std::endl;
	}
}
