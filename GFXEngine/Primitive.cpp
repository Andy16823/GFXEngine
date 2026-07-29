#include "Primitive.h"
#include "EngineDefinitions.h"
#include "AssetManager.h"

using namespace GFXEngine;
using namespace GFXEngine::Graphics;

void GFXEngine::Core::Primitive::buildRenderTasks(GFXEngine::Graphics::RenderContext& context, GFXEngine::Graphics::RenderQueue& renderQueue)
{
	if (context.renderPass == RenderPassIteration::GeometryPass) {
		Graphics::GraphicResources ressources;
		ressources[Defintions::CAMERA_RESOURCE] = context.camera.getDescriptorSet(context.imageIndex);
		this->getScene()->getGraphicResources(ressources, context.imageIndex);
		this->getGraphicResources(ressources, context.imageIndex);

		for (size_t i = 0; i < this->getMeshCount(); i++) {
			auto meshMaterial = this->getMeshAndMaterial(i);
			if (meshMaterial.has_value()) {
				const auto& [mesh, material] = meshMaterial.value();

				RenderTaskBuilder taskBuilder;
				taskBuilder.setPipeline(m_pipeline)
					.setMesh(&mesh)
					.setModelMatrix(this->getModelMatrix());

				this->getMeshMaterialGraphicResources(ressources, context.imageIndex, i);
				m_pipeline->getGraphicsPass().bindResources(taskBuilder, ressources);
				renderQueue.addRenderTask(taskBuilder.build());
			}
		}
	}
	Entity::buildRenderTasks(context, renderQueue);
}

void GFXEngine::Core::Primitive::getGraphicResources(GFXEngine::Graphics::GraphicResources& resources, uint32_t imageIndex) const
{

}

void GFXEngine::Core::Primitive::getMeshMaterialGraphicResources(Graphics::GraphicResources& resources, uint32_t imageIndex, size_t meshIndex) const
{
	auto meshMaterial = this->getMeshAndMaterial(meshIndex);
	if (meshMaterial.has_value()) {
		const auto& material = meshMaterial->second;
		resources[Defintions::MATERIAL_RESOURCE] = material.getDescriptorSet(imageIndex);
	}
}

size_t GFXEngine::Core::Primitive::getMeshCount() const
{
	return 1;
}

GFXEngine::Core::MeshMaterialPair GFXEngine::Core::Primitive::getMeshAndMaterial(size_t index) const
{
	if (index != 0) {
		throw std::out_of_range("Mesh index out of range");
	}

	auto* meshAsset = m_meshReference.get<Graphics::MeshAsset>();
	auto* materialAsset = m_materialReference.get<Graphics::MaterialAsset>();
	Graphics::Mesh& mesh = *meshAsset->getMesh();
	Graphics::Material& material = *materialAsset->getMaterial();

	return std::make_optional(std::make_pair(std::ref(mesh), std::ref(material)));
}

nlohmann::json Core::Primitive::serialize() const
{
	nlohmann::json data = Entity::serialize();
	data["mesh"] = m_meshReference.get<MeshAsset>()->getName();
	data["material"] = m_meshReference.get<MaterialAsset>()->getName();

	return data;
}

void GFXEngine::Core::Primitive::deserialize(const nlohmann::json& data, SerializationContext& context, SerializationFlags flags /*= SerializationFlags::None*/)
{
	Entity::deserialize(data, context, flags);
	
	// Deserialize Mesh
	if (!data.contains("mesh") || !data["mesh"].is_string()) {
		throw std::runtime_error("Primitive deserialization error: 'mesh' field is missing or not a string");
	}
	std::string meshName = data["mesh"].get<std::string>();
	
	MeshAsset* meshAsset = context.assets.get<MeshAsset>(meshName);
	if (!meshAsset) {
		throw std::runtime_error("Primitive deserialization error: MeshAsset asset '" + meshName + "' not found");
	}
	m_meshReference.set(meshAsset);


	// Deserialize Material
	if (!data.contains("material") || !data["material"].is_string()) {
		throw std::runtime_error("Primitive deserialization error: 'material' field is missing or not a string");
	}
	std::string materialName = data["material"].get<std::string>();

	MaterialAsset* materialAsset = context.assets.get<MaterialAsset>(materialName);
	if (!materialAsset) {
		throw std::runtime_error("Primitive deserialization error: MaterialAsset asset '" + materialName + "' not found");
	}
	m_materialReference.set(materialAsset);
}

void Core::Primitive::requireAsset(RequiredAssets& assets)
{
	auto meshAsset = m_meshReference.get<MeshAsset>();
	if (!meshAsset) {
		throw std::runtime_error("Primitive requireAsset error: MeshAsset reference is invalid");
	}
	assets.emplace(meshAsset->getName());

	auto materialAsset = m_meshReference.get<MaterialAsset>();
	if (!materialAsset) {
		throw std::runtime_error("Primitive requireAsset error: MaterialAsset reference is invalid");
	}
	assets.emplace(materialAsset->getName());
}
