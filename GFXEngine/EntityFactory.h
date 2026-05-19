#pragma once
#include <string>
#include <unordered_map>
#include <functional>
#include <memory>

namespace GFXEngine
{
	namespace Core
	{
		class Entity;
	}

	class EntityFactory
	{
	private:
		using FactoryFunction = std::function<std::unique_ptr<GFXEngine::Core::Entity>()>;
		std::unordered_map<std::string, FactoryFunction> m_entityCreators;

	public:
		EntityFactory() = default;
		~EntityFactory() = default;

		template<typename T>
		bool registerEntity()
		{
			static_assert(std::is_base_of<GFXEngine::Core::Entity, T>::value, "T must derive from GFXEngine::Core::Entity");
			FactoryFunction factory = []() {
				return std::make_unique<T>();
				};
			auto result = m_entityCreators.emplace(typeid(T).name(), factory);
			return result.second;
		}

		template<typename T>
		bool registerEntity(const std::string& name) 
		{
			static_assert(std::is_base_of<GFXEngine::Core::Entity, T>::value, "T must derive from GFXEngine::Core::Entity");
			FactoryFunction factory = []() {
				return std::make_unique<T>();
				};

			auto result = m_entityCreators.emplace(name, factory);
			return result.second;
		}

		template<typename T>
		bool registerEntity(const std::string& name, FactoryFunction factory) 
		{
			static_assert(std::is_base_of<GFXEngine::Core::Entity, T>::value, "T must derive from GFXEngine::Core::Entity");
			auto result = m_entityCreators.emplace(name, factory);
			return result.second;
		}

		std::unique_ptr<GFXEngine::Core::Entity> createEntity(const std::string& name) const 
		{
			auto it = m_entityCreators.find(name);
			if (it != m_entityCreators.end())
			{
				return it->second();
			}
			return nullptr;
		}

		void clear()
		{
			m_entityCreators.clear();
		}
	};
}
