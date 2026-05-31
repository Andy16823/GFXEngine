#include "InstanceHandle.h"
#include "InstancedModel.h"

using namespace GFXEngine;

nlohmann::json Core::InstanceHandle::serialize() const
{
	auto data = Entity::serialize();
	data["instanceIndex"] = m_instanceIndex;
	data["instanceModel"] = m_parentModel.isResolved() ? m_parentModel.get().getUUID() : "";
	return data;
}

void Core::InstanceHandle::deserialize(const nlohmann::json& data, SerializationContext& context, SerializationFlags flags /*= SerializationFlags::None*/)
{
	Entity::deserialize(data, context, flags);
	m_instanceIndex = data.value("instanceIndex", static_cast<size_t>(-1));
	m_parentModel = EngineTypes::EntityReference{ data.value("instanceModel", ""), nullptr };
}

void Core::InstanceHandle::resolveReferences(SerializationContext& context)
{
	Entity::resolveReferences(context);
	if (context.entityRegistry.contains(m_parentModel.uuid)) {
		m_parentModel.set(context.getEntity(m_parentModel.uuid));
	}
	else {
		std::cerr << "Warning: Failed to resolve parent model reference for InstanceHandle with UUID " << this->uuid << ". Parent model UUID: " << m_parentModel.uuid << std::endl;
	}
}

void GFXEngine::Core::InstanceHandle::propertyChanged(PropertyComponentType component)
{
	if (component == PropertyComponentType::Transform || component == PropertyComponentType::Visibility) {
		if (m_parentModel.isResolved()) {
			m_parentModel.getAs<InstancedModel>().updateInstance({
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