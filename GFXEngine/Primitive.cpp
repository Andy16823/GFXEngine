#include "Primitive.h"
#include "EngineDefinitions.h"

void GFXEngine::Core::Primitive::buildRenderTasks(Graphics::RenderContext& context, Graphics::RenderQueue& renderQueue)
{
	auto pipeline = context.renderer.getPipeline<Graphics::GraphicsPipeline>(Defintions::SOLID_COLOR_PIPELINE);
	Graphics::GraphicResources resources;
	resources[Defintions::CAMERA_RESOURCE] = context.camera.getDescriptorSet(context.imageIndex);
	this->getScene()->getGraphicResources(resources, context.imageIndex);
	this->getGraphicResources(resources, context.imageIndex);

	for (size_t i = 0; i < this->getMeshCount(); ++i) {
		auto meshMaterialPair = this->getMeshAndMaterial(i);
		if (!meshMaterialPair.has_value()) {
			std::cerr << "Warning: Mesh " << i << " in Primitive '" << this->name << "' is missing a valid mesh/material pair. Skipping render task for this mesh." << std::endl;
			continue;
		}
		const auto& [mesh, material] = meshMaterialPair.value();

		// Create render task builder and set common properties
		Graphics::RenderTaskBuilder taskBuilder;
		taskBuilder.setPipeline(pipeline)
			.setMesh(&mesh)
			.setModelMatrix(this->getModelMatrix());

		this->getMeshMaterialGraphicResources(resources, context.imageIndex, i);
		pipeline->getGraphicsPass().bindResources(taskBuilder, resources);
		renderQueue.addRenderTask(taskBuilder.build());
	}
}

void GFXEngine::Core::Primitive::getMeshMaterialGraphicResources(Graphics::GraphicResources& resources, uint32_t imageIndex, size_t meshIndex) const
{
	auto meshMaterialPair = getMeshAndMaterial(meshIndex);
	if (meshMaterialPair.has_value()) {
		const auto& [mesh, material] = meshMaterialPair.value();
		resources[Defintions::MATERIAL_RESOURCE] = material.getDescriptorSet(imageIndex);
	}
	else {
		std::cerr << "Warning: Mesh index " << meshIndex << " in Primitive '" << this->name << "' is invalid. No graphic resources will be provided for this mesh." << std::endl;
	}
}

size_t GFXEngine::Core::Primitive::getMeshCount() const
{
    return 1;
}

GFXEngine::Core::MeshMaterialPair GFXEngine::Core::Primitive::getMeshAndMaterial(size_t index) const
{
	if (index == 0)
	{
		return std::make_pair(std::ref(*m_mesh), std::ref(*m_material));
	}
	else
	{
		return std::nullopt;
	}
}
