#include "Entity.h"
#include "Behavior.h"
#include "BehaviorRegistry.h"
#include "Utils.h"

GFXEngine::Core::Entity::Entity()
{
	uuid = GFXEngine::Utils::generateUUID();
}

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
	data["name"] = name;
	data["uuid"] = uuid;
	data["visible"] = m_visible;
	data["transform"] = transform.serialize();
	data["tags"] = m_tags;

	std::vector<nlohmann::json> behaviorsData;
	for (const auto& bhv : m_behaviors) {
		nlohmann::json bhvData;
		bhvData["name"] = bhv->getName();
		bhvData["data"] = bhv->serialize();
		behaviorsData.push_back(bhvData);
	}
	data["behaviors"] = behaviorsData;
	return data;
}

void GFXEngine::Core::Entity::deserialize(const nlohmann::json& data, GFXEngine::SerializationContext& context, GFXEngine::SerializationFlags flags)
{
	name = data.value("name", "");
	if (hasFlag(flags, GFXEngine::SerializationFlags::RegenerateUUID)) {
		uuid = Utils::generateUUID();
	} else {
		uuid = data.value("uuid", Utils::generateUUID());
	}
	m_visible = data.value("visible", true);
	transform.deserialize(data.value("transform", nlohmann::json()), context, flags);
	m_tags = data.value("tags", std::vector<std::string>());

	auto behaviorsData = data.value("behaviors", std::vector<nlohmann::json>());
	for (const auto& bhvData : behaviorsData) {
		std::string bhvName = bhvData.value("name", "");
		nlohmann::json bhvJson = bhvData.value("data", nlohmann::json());

		auto behavior = context.behaviors.createBehavior(bhvName);
		if (behavior) {
			behavior->deserialize(bhvJson, context, flags);
			addBehavior(std::move(behavior));
		} else {
			throw std::runtime_error("Unknown behavior type: " + bhvName);
		}
	}
}