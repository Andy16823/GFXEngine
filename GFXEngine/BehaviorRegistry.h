#pragma once
#include <unordered_map>
#include <string>
#include <memory>
#include <functional>
#include "Behavior.h"


namespace GFXEngine {
	class BehaviorRegistry {
	public:
		using FactoryFunction = std::function<std::unique_ptr<Core::Behavior>()>;

	private:
		std::unordered_map<std::string, FactoryFunction> m_registry;

	public:
		//************************************
		// Method:    registerBehavior
		// FullName:  GFXEngine::BehaviorRegistry::registerBehavior
		// Access:    public 
		// Returns:   bool
		// Qualifier:
		// Parameter: const std::string & name
		// Parameter: FactoryFunction factory
		//************************************
		bool registerBehavior(const std::string& name, FactoryFunction factory);
		
		//************************************
		// Method:    isRegistered
		// FullName:  GFXEngine::BehaviorRegistry::isRegistered
		// Access:    public 
		// Returns:   bool
		// Qualifier: const
		// Parameter: const std::string & name
		//************************************
		bool isRegistered(const std::string& name) const;
		
		//************************************
		// Method:    createBehavior
		// FullName:  GFXEngine::BehaviorRegistry::createBehavior
		// Access:    public 
		// Returns:   std::unique_ptr<GFXEngine::Core::Behavior>
		// Qualifier:
		// Parameter: const std::string & name
		//************************************
		std::unique_ptr<Core::Behavior> createBehavior(const std::string& name);
		
		//************************************
		// Method:    getRegisteredBehaviors
		// FullName:  GFXEngine::BehaviorRegistry::getRegisteredBehaviors
		// Access:    public 
		// Returns:   std::vector<std::string>
		// Qualifier: const
		//************************************
		std::vector<std::string> getRegisteredBehaviors() const;

		//************************************
		// Method:    clear
		// FullName:  GFXEngine::BehaviorRegistry::clear
		// Access:    public 
		// Returns:   void
		// Qualifier:
		//************************************
		void clear();
		
		//************************************
		// Method:    foreachBehavior
		// FullName:  GFXEngine::BehaviorRegistry::foreachBehavior
		// Access:    public 
		// Returns:   void
		// Qualifier: const
		// Parameter: const std::function<void
		// Parameter: const std::string & 
		// Parameter: > & func
		//************************************
		void foreachBehavior(const std::function<void(const std::string&)>& func) const;
	};
}