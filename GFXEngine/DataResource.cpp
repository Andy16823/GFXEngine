#include "DataResource.h"
#include "Utils.h"

using namespace GFXEngine;
using namespace GFXEngine::Core;

GFXEngine::Core::DataResource::DataResource(const std::string& name, const std::string& path) : Asset(name)
{
	if (!Utils::fileExists(path)) {
		throw std::runtime_error("DataResource error: File '" + path + "' does not exist");
	}
	data = GFXEngine::Utils::loadJsonFromFile(path);
}

const nlohmann::json* DataResource::findProperty(std::span<const std::string> path) const
{
	const nlohmann::json* current = &data;
	for (const auto& property : path) {
		if (!current->contains(property)) {
			return nullptr;
		}
		current = &current->at(property);
	}
	return current;
}

bool DataResource::hasProperty(std::span<const std::string> propertyPath) const
{
	const nlohmann::json* current = &data;
	for (const auto& property : propertyPath) {
		if (!current->contains(property)) {
			return false;
		}
		current = &current->at(property);
	}
	return true;
}

bool DataResource::hasProperty(const std::string& propertyName) const
{
	return data.contains(propertyName);
}
