#include "EnviromentMap.h"
#include "Shapes.h"
#include "DataTypes.h"
#include "EngineDefinitions.h"
#include "Utils.h"
#include "RenderTask.h"
#include "RenderQueue.h"

using namespace GFXEngine::Graphics;

void EnviromentMap::init(GFXEngine::Graphics::Renderer& renderer)
{
	m_mesh->init(renderer);
	m_envMaterial->init(renderer);
}

void EnviromentMap::destroy(GFXEngine::Graphics::Renderer& renderer)
{
	m_mesh->destroy(renderer);
	m_envMaterial->destroy(renderer);
}

EnviromentMap::EnviromentMap(const std::string& name, const std::vector<std::string>& faceFilepaths) : Asset(name)
{
	auto [vertices, indices] = Graphics::Shapes::createSkybox();
	m_mesh = std::make_unique<PositionMesh>();
	m_mesh->setVertices(std::move(vertices));
	m_mesh->setIndices(std::move(indices));

	m_envMaterial = std::make_unique<EnviromentMaterial>();
	LibGFX::CubemapData cubemapData = GFXEngine::Utils::loadCubemap(faceFilepaths, false);
	m_envMaterial->setCubemapData(std::move(cubemapData));
}
