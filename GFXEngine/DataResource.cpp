#include "DataResource.h"
#include "Utils.h"
#include <span>
#include <cassert>

using namespace GFXEngine;
using namespace GFXEngine::Core;

void DataResource::load(const std::string& filePath)
{
	assert(!m_loaded && "DataResource is already loaded");

	if (!Utils::fileExists(filePath)) {
		throw std::runtime_error("DataResource error: File '" + filePath + "' does not exist");
	}
	data = GFXEngine::Utils::loadJsonFromFile(filePath);
	m_filePath = filePath;
	m_loaded = true;
}

const nlohmann::json* DataResource::findProperty(std::initializer_list<std::string> path) const
{
	return this->findProperty(std::span<const std::string>(path.begin(), path.size()));
}

const nlohmann::json* DataResource::findProperty(std::span<const std::string> path) const
{
	assert(m_loaded && "DataResource must be loaded before accessing properties");

	const nlohmann::json* current = &data;
	for (const auto& property : path) {
		if (!current->contains(property)) {
			return nullptr;
		}
		current = &current->at(property);
	}
	return current;
}

bool DataResource::hasProperty(std::span<std::string> propertyPath) const
{
	assert(m_loaded && "DataResource must be loaded before checking properties");

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
	assert(m_loaded && "DataResource must be loaded before checking properties");

	return data.contains(propertyName);
}
