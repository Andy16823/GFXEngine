#include "Entity.h"
#include "Behavior.h"

void GFXEngine::Core::Entity::init(Scene& scene, GFXEngine::Graphics::Renderer& renderer)
{
	// Compute AABB based on meshes
	Math::AABB combinedAABB;
	size_t meshCount = getMeshCount();
	for (size_t i = 0; i < meshCount; ++i) {
		auto [mesh, material] = getMeshAndMaterial(i);
		Math::AABB meshAABB = mesh.computeAABB(); // Dont call this every frame, only on init or when mesh data changes
		combinedAABB = combinedAABB.unionWith(meshAABB);
	}
	setAABB(combinedAABB);

	// Initialize behaviors
	for (auto& behavior : m_behaviors) {
		behavior->init(scene, renderer);
	}
}

void GFXEngine::Core::Entity::update(Scene& scene, float deltaTime)
{
	for (auto& behavior : m_behaviors) {
		behavior->update(scene, deltaTime);
	}
}

void GFXEngine::Core::Entity::render(Scene& scene, GFXEngine::Graphics::Renderer& renderer, GFXEngine::Graphics::Camera& camera, uint32_t imageIndex)
{
	for (auto& behavior : m_behaviors) {
		behavior->render(scene, renderer, camera, imageIndex);
	}
}

void GFXEngine::Core::Entity::destroy(Scene& scene, GFXEngine::Graphics::Renderer& renderer)
{
	for (auto& behavior : m_behaviors) {
		behavior->destroy(scene, renderer);
	}
}

nlohmann::json GFXEngine::Core::Entity::serialize() const
{
	nlohmann::json data;
	data["name"] = m_name;
	data["visible"] = m_visible;
	data["transform"] = transform.serialize();
	data["tags"] = m_tags;

	std::vector<nlohmann::json> behaviorsData;
	for (const auto& bhv : m_behaviors) {
		nlohmann::json bhvData;
		bhvData["name"] = bhv->getName();
		
		for (const auto& prop : bhv->getProperties()) {
			nlohmann::json propData;
			propData["name"] = prop.name;
			propData["type"] = static_cast<int>(prop.type);
			switch (prop.type)
			{
				case PropertyType::String:
					propData["value"] = *static_cast<std::string*>(prop.data);
					break;
				case PropertyType::Int:
					propData["value"] = *static_cast<int*>(prop.data);
					break;
				case PropertyType::Bool:
					propData["value"] = *static_cast<bool*>(prop.data);
					break;
				case PropertyType::Float:
					propData["value"] = *static_cast<float*>(prop.data);
					break;
				case PropertyType::Vector2:
					glm::vec2 vec2Value = *static_cast<glm::vec2*>(prop.data);
					propData["value"] = { vec2Value.x, vec2Value.y };
					break;
				case PropertyType::Vector3:
					glm::vec3 vec3Value = *static_cast<glm::vec3*>(prop.data);
					propData["value"] = { vec3Value.x, vec3Value.y, vec3Value.z };
					break;
				case PropertyType::Vector4:
					glm::vec4 vec4Value = *static_cast<glm::vec4*>(prop.data);
					propData["value"] = { vec4Value.x, vec4Value.y, vec4Value.z, vec4Value.w };
					break;
				case PropertyType::Color:
					glm::vec4 colorValue = *static_cast<glm::vec4*>(prop.data);
					propData["value"] = { colorValue.r, colorValue.g, colorValue.b, colorValue.a };
					break;
			default:
				break;
			}
			bhvData["properties"].push_back(propData);
		}
		behaviorsData.push_back(bhvData);
	}
	data["behaviors"] = behaviorsData;
	return data;
}

void GFXEngine::Core::Entity::deserialize(const nlohmann::json& data)
{
	m_name = data.value("name", "");
	m_visible = data.value("visible", true);
	transform.deserialize(data.value("transform", nlohmann::json{}));
	m_tags = data.value("tags", std::vector<std::string>{});
	// TODO: Deserialize behaviors
}