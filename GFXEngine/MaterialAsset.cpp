#include "MaterialAsset.h"
#include "Utils.h"
#include "SolidMaterial.h"
#include "RuntimeContext.h"
#include "SerializationContext.h"

void GFXEngine::Graphics::MaterialAsset::init(Graphics::Renderer& renderer)
{
	if (!m_initialized) {
		if (m_material) {
			m_material->init(renderer);
			m_initialized = true;
		}
	}
}

void GFXEngine::Graphics::MaterialAsset::destroy(Graphics::Renderer & renderer)
{
	if (m_initialized) {
		if (m_material) {
			m_material->destroy(renderer);
			m_initialized = false;
		}
	}
}

void GFXEngine::Graphics::MaterialAsset::load()
{
	auto filepath = this->getFilePath();
	// If the file path is not empty, attempt to load the material from the JSON file
	if (!filepath.empty()) {
		// Load the JSON data from the specified file path
		nlohmann::json data = GFXEngine::Utils::loadJsonFromFile(filepath);
		std::string materialType = data["type"].get<std::string>();

		// Create the appropriate material type based on the "type" field in the JSON
		if (materialType == (typeid(SolidMaterial).name())) {
			m_material = std::make_unique<SolidMaterial>();
		}
		else {
			throw std::runtime_error("Unsupported material type: " + materialType);
		}

		// Deserialize the material data from the JSON
		auto& ctx = GFXEngine::RuntimeContext::get();
		GFXEngine::SerializationContext sctx = ctx.createSerializationContext();
		m_material->deserialize(data, sctx, GFXEngine::SerializationFlags::None);
	}
	else {
		throw std::runtime_error("File path is empty for MaterialAsset: " + this->getName());
	}
}

bool GFXEngine::Graphics::MaterialAsset::isLoaded() const
{
	return m_material != nullptr;
}

void GFXEngine::Graphics::MaterialAsset::unload()
{
	// Unused since the material asset dont hold any cpu resources
}
