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
		//************************************
		// Method:    EntityFactory
		// FullName:  GFXEngine::EntityFactory::EntityFactory
		// Access:    public 
		// Returns:   
		// Qualifier:
		//************************************
		EntityFactory() = default;
		
		//************************************
		// Method:    ~EntityFactory
		// FullName:  GFXEngine::EntityFactory::~EntityFactory
		// Access:    public 
		// Returns:   
		// Qualifier:
		//************************************
		~EntityFactory() = default;

		//************************************
		// Method:    registerEntity
		// FullName:  GFXEngine::EntityFactory::registerEntity
		// Access:    public 
		// Returns:   bool
		// Qualifier:
		//************************************
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

		//************************************
		// Method:    registerEntity
		// FullName:  GFXEngine::EntityFactory::registerEntity
		// Access:    public 
		// Returns:   bool
		// Qualifier:
		// Parameter: const std::string & name
		//************************************
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

		//************************************
		// Method:    registerEntity
		// FullName:  GFXEngine::EntityFactory::registerEntity
		// Access:    public 
		// Returns:   bool
		// Qualifier:
		// Parameter: const std::string & name
		// Parameter: FactoryFunction factory
		//************************************
		template<typename T>
		bool registerEntity(const std::string& name, FactoryFunction factory) 
		{
			static_assert(std::is_base_of<GFXEngine::Core::Entity, T>::value, "T must derive from GFXEngine::Core::Entity");
			auto result = m_entityCreators.emplace(name, factory);
			return result.second;
		}

		//************************************
		// Method:    createEntity
		// FullName:  GFXEngine::EntityFactory::createEntity
		// Access:    public 
		// Returns:   std::unique_ptr<GFXEngine::Core::Entity>
		// Qualifier: const
		// Parameter: const std::string & name
		//************************************
		std::unique_ptr<GFXEngine::Core::Entity> createEntity(const std::string& name) const 
		{
			auto it = m_entityCreators.find(name);
			if (it != m_entityCreators.end())
			{
				return it->second();
			}
			return nullptr;
		}

		//************************************
		// Method:    clear
		// FullName:  GFXEngine::EntityFactory::clear
		// Access:    public 
		// Returns:   void
		// Qualifier:
		//************************************
		void clear()
		{
			m_entityCreators.clear();
		}
	};
}
