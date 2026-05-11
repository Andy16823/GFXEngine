#include "BehaviorRegistry.h"

bool GFXEngine::BehaviorRegistry::registerBehavior(const std::string& name, FactoryFunction factory)
{
	auto result = m_registry.emplace(name, std::move(factory));
	return result.second;
}

bool GFXEngine::BehaviorRegistry::isRegistered(const std::string& name) const
{
	return m_registry.find(name) != m_registry.end();
}

std::unique_ptr<GFXEngine::Core::Behavior> GFXEngine::BehaviorRegistry::createBehavior(const std::string& name)
{
	auto it = m_registry.find(name);
	if (it != m_registry.end()) {
		return it->second();
	}
	return nullptr;
}

std::vector<std::string> GFXEngine::BehaviorRegistry::getRegisteredBehaviors() const
{
	std::vector<std::string> names;
	names.reserve(m_registry.size());
	for (const auto& pair : m_registry) {
		names.push_back(pair.first);
	}
	return names;
}

void GFXEngine::BehaviorRegistry::clear()
{
	m_registry.clear();
}
