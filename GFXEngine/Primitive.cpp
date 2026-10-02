#include "Primitive.h"
#include "EngineDefinitions.h"
#include "AssetManager.h"

using namespace GFXEngine;
using namespace GFXEngine::Core;
using namespace GFXEngine::Graphics;

void GFXEngine::Core::Primitive::buildRenderTasks(GFXEngine::Graphics::RenderContext& context, GFXEngine::Graphics::RenderQueue& renderQueue)
{
	// Build Geometrypass Task
	if (context.renderPass == RenderPassIteration::GeometryPass) {

		// Check if the pipeline id is set
		if (!m_pipelineId.has_value()) {
			throw std::runtime_error("Missing pipeline ID");
		}
		unsigned int pipelineId = m_pipelineId.value();

		// Get the pipeline from the renderer
		auto pipeline = context.renderer.getPipeline<GFXEngine::Graphics::GraphicsPipeline>(pipelineId);
		if (!pipeline) {
			throw std::runtime_error("Pipeline with ID " + std::to_string(pipelineId) + " not found.");
		}

		// Gather resources needed for the render task
		Graphics::GraphicResources ressources;
		ressources[Defintions::CAMERA_RESOURCE] = context.camera.getDescriptorSet(context.imageIndex);
        ressources[Defintions::FRAME_RESOURCE] = context.frameContext.getDescriptorSet(context.imageIndex);
		this->getScene()->getGraphicResources(ressources, context.imageIndex);
		this->getGraphicResources(ressources, context.imageIndex);

		// Create an render task for each mesh :) in this case its only 1
		for (size_t i = 0; i < this->getMeshCount(); i++) {
			auto meshMaterial = this->getMeshAndMaterial(i);
			if (meshMaterial.has_value()) {
				const auto& [mesh, material] = meshMaterial.value();

				RenderTaskBuilder taskBuilder;
				taskBuilder.setPipeline(pipeline)
					.setMesh(&mesh)
					.setModelMatrix(this->getModelMatrix());

				this->getMeshMaterialGraphicResources(ressources, context.imageIndex, i);
				pipeline->getGraphicsPass().bindResources(taskBuilder, ressources);
				renderQueue.addRenderTask(taskBuilder.build());
			}
		}
	}

	// Build render task for the children and behaviors
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
	// Index must be 0
	if (index != 0) {
		throw std::out_of_range("Mesh index out of range");
	}

	// Check if there is a reference set
	if (!m_meshReference.has_value() || !m_materialReference.has_value())
	{
		throw std::runtime_error("Primitive has no valid mesh or material reference");
	}

	MeshAsset* meshAsset = m_meshReference.value()->as<Graphics::MeshAsset>();
	MaterialAsset* materialAsset = m_materialReference.value()->as<Graphics::MaterialAsset>();
	if (!meshAsset || !meshAsset->getMesh() || !materialAsset || !materialAsset->getMaterial()) {
		throw std::runtime_error("Primitive has invalid mesh/material asset reference");
	}

	Graphics::Mesh& mesh = *meshAsset->getMesh();
	Graphics::Material& material = *materialAsset->getMaterial();
	return std::make_optional(std::make_pair(std::ref(mesh), std::ref(material)));
}

nlohmann::json Core::Primitive::serialize() const
{
	if (!m_pipelineId.has_value())
	{
		throw std::logic_error("Primitive has no pipeline assigned.");
	}

	nlohmann::json data = Entity::serialize();

	if (m_meshReference.has_value()) {
		data["mesh"] = m_meshReference.value()->getName();
	}

	if (m_materialReference.has_value()) {
		data["material"] = m_materialReference.value()->getName();
	}
	
	data["pipeline"] = m_pipelineId.value();
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
	m_meshReference = context.assets.get<MeshAsset>(meshName);


	// Deserialize Material
	if (!data.contains("material") || !data["material"].is_string()) {
		throw std::runtime_error("Primitive deserialization error: 'material' field is missing or not a string");
	}
	std::string materialName = data["material"].get<std::string>();
	m_materialReference = context.assets.get<MaterialAsset>(materialName);

	if (!data.contains("pipeline") || !data["pipeline"].is_number_unsigned())
	{
		throw std::runtime_error("Primitive deserialization error: 'pipeline' field is missing or not an unsigned integer");
	}
	m_pipelineId = data["pipeline"].get<unsigned int>();
}

void Core::Primitive::requireAsset(RequiredAssets& assets)
{
	Entity::requireAsset(assets);

	if (!m_meshReference.has_value() || !m_materialReference.has_value()) {
		throw std::runtime_error("Primitive requireAsset error: MeshReference or MaterialReference is invalid");
	}

	assets.emplace(m_meshReference.value()->getName());
	assets.emplace(m_materialReference.value()->getName());
}