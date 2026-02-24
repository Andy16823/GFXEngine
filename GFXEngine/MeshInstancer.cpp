#include "MeshInstancer.h"
#include "DataTypes.h"

void GFXEngine::Core::MeshInstancer::init(GFXEngine::Graphics::Renderer& renderer)
{
	size_t bufferSize = m_numInstances * sizeof(GFXEngine::EngineTypes::InstanceData);

	m_instanceBuffer = renderer.createBuffer(
		bufferSize,
		VK_BUFFER_USAGE_VERTEX_BUFFER_BIT | VK_BUFFER_USAGE_STORAGE_BUFFER_BIT,
		VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT
	);

	std::vector<GFXEngine::EngineTypes::InstanceData> instanceData = bakeInstanceData();
	renderer.updateBuffer(m_instanceBuffer, instanceData.data(), m_numInstances);

	// TODO: Create a descriptor set for the instance buffer and bind it to the material's pipeline layout
}

void GFXEngine::Core::MeshInstancer::render(GFXEngine::Graphics::Renderer& renderer, GFXEngine::Graphics::Camera& camera, uint32_t imageIndex)
{
	throw std::logic_error("The method or operation is not implemented.");
}

std::vector<GFXEngine::EngineTypes::InstanceData> GFXEngine::Core::MeshInstancer::bakeInstanceData() const
{
	std::vector<GFXEngine::EngineTypes::InstanceData> instanceData(m_numInstances);
	for (size_t i = 0; i < m_numInstances; ++i) {
		instanceData[i].model = glm::mat4(1.0f);
		instanceData[i].extras = glm::vec4(0.0f);
	}
	return instanceData;
}
