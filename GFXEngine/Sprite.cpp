#include "Sprite.h"
#include "Utils.h"
#include "Scene.h"
#include "Renderer.h"
#include "Camera.h"
#include "EngineDefinitions.h"

using namespace GFXEngine;
using namespace GFXEngine::Graphics;
using namespace GFXEngine::Core;
using namespace GFXEngine::Math;

void GFXEngine::Core::Sprite::init(Scene& scene,  GFXEngine::Graphics::Renderer& renderer)
{
	Entity::init(scene, renderer);
}

void GFXEngine::Core::Sprite::update(Scene& scene, GFXEngine::Graphics::Camera& camera, float deltaTime)
{
	Entity::update(scene, camera, deltaTime);
}

void Sprite::buildRenderTasks(GFXEngine::Graphics::RenderContext& context, GFXEngine::Graphics::RenderQueue& renderQueue)
{
	if (context.renderPass == Graphics::RenderPassIteration::GeometryPass) 
	{
		// TODO: Render Sprites!
		auto pipeline = context.renderer.getPipeline<Graphics::GraphicsPipeline>(Defintions::SPRITE_PIPELINE);
		Graphics::GraphicResources resources;
		resources[Defintions::CAMERA_RESOURCE] = context.camera.getDescriptorSet(context.imageIndex);
		this->getScene()->getGraphicResources(resources, context.imageIndex);
		this->getGraphicResources(resources, context.imageIndex);

		for (size_t i = 0; i < this->getMeshCount(); ++i) {
			this->getMeshMaterialGraphicResources(resources, context.imageIndex, i);
			auto meshMaterialPair = this->getMeshAndMaterial(i);
			if (!meshMaterialPair.has_value()) {
				std::cerr << "Warning: Mesh " << i << " in Sprite '" << this->name << "' is missing a valid mesh/material pair. Skipping render task for this mesh." << std::endl;
				continue;
			}
			const auto& [mesh, material] = meshMaterialPair.value();

			RenderTaskBuilder taskBuilder;
			taskBuilder.setPipeline(pipeline)
				.setMesh(&mesh)
				.setModelMatrix(this->getTransform().getModelMatrix())
				.setRenderLayer(RenderLayer::Transparent);

			// Bind material descriptor set and push constant for model matrix
			pipeline->getGraphicsPass().bindResources(taskBuilder, resources);
			renderQueue.addRenderTask(taskBuilder.build());
		}
	}
	Entity::buildRenderTasks(context, renderQueue);
}

void GFXEngine::Core::Sprite::destroy(Scene& scene, GFXEngine::Graphics::Renderer& renderer)
{
	Entity::destroy(scene, renderer);
}

void Sprite::getGraphicResources(Graphics::GraphicResources& resources, uint32_t imageIndex) const
{

}

void Sprite::getMeshMaterialGraphicResources(Graphics::GraphicResources& resources, uint32_t imageIndex, size_t meshIndex) const
{
	assert(meshIndex == 0); // Sprite only has one mesh and material
	auto MeshMaterialPair = getMeshAndMaterial(meshIndex);
	if (MeshMaterialPair.has_value()) {
		const auto& material = MeshMaterialPair->second;
		resources[Defintions::MATERIAL_RESOURCE] = material.getDescriptorSet(imageIndex);
	}
}

GFXEngine::Core::MeshMaterialPair Sprite::getMeshAndMaterial(size_t index) const
{
	if(index != 0) {
		throw std::out_of_range("Sprite only has one mesh and material");
	}
	return std::make_optional(std::make_pair(std::ref(m_mesh), std::ref(m_material)));
}
