#include "InstanceHandle.h"
#include "InstancedModel.h"

using namespace GFXEngine;

void GFXEngine::Core::InstanceHandle::propertyChanged(PropertyComponentType component)
{
	if (component == PropertyComponentType::Transform || component == PropertyComponentType::Visibility) {
		if (m_parentModel) {
			m_parentModel->updateInstance({
				.model = this->getModelMatrix(),
				.extras = glm::vec4(this->isVisible() ? 1.0f : 0.0f, 0.0f, 0.0f, 0.0f) // Use extras.x to store visibility
				}, m_instanceIndex);
		}
	}
}

size_t GFXEngine::Core::InstanceHandle::getMeshCount() const
{
	return 0;
}

GFXEngine::Core::MeshMaterialPair GFXEngine::Core::InstanceHandle::getMeshAndMaterial(size_t index) const
{
	return std::nullopt;
}
