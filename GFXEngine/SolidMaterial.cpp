#include "SolidMaterial.h"

nlohmann::json GFXEngine::Graphics::SolidMaterial::serialize() const
{
	auto data = Material::serialize();
	data["color"] = { m_color.r, m_color.g, m_color.b, m_color.a };
	return data;
}

void GFXEngine::Graphics::SolidMaterial::deserialize(const nlohmann::json& data, GFXEngine::SerializationContext& context, GFXEngine::SerializationFlags flags /*= GFXEngine::SerializationFlags::None*/)
{
	Material::deserialize(data, context, flags);
	if (data.contains("color") && data["color"].is_array() && data["color"].size() == 4)
	{
		m_color = glm::vec4(data["color"][0], data["color"][1], data["color"][2], data["color"][3]);
	}
}

void GFXEngine::Graphics::SolidMaterial::init(Renderer& renderer)
{
	VkDeviceSize bufferSize = sizeof(glm::vec4);
	m_buffer = renderer.createBuffer(
		bufferSize,
		VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT,
		VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT);
	renderer.updateBuffer(m_buffer, &m_color, 1);
	m_decriptorSet = renderer.allocateUniformBufferDescriptorSet(m_buffer, 0, renderer.getUniformBufferLayout());
}

void GFXEngine::Graphics::SolidMaterial::updateMaterial(Renderer& renderer)
{
	renderer.updateBuffer(m_buffer, &m_color, 1);
}

void GFXEngine::Graphics::SolidMaterial::destroy(Renderer & renderer)
{
	renderer.destroyBuffer(m_buffer);
	renderer.freeUniformBufferDescriptorSet(m_decriptorSet);
}
