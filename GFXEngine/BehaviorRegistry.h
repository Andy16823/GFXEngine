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

		bool registerBehavior(const std::string& name, FactoryFunction factory);
		bool isRegistered(const std::string& name) const;
		std::unique_ptr<Core::Behavior> createBehavior(const std::string& name);
		std::vector<std::string> getRegisteredBehaviors() const;

		void clear();
		void foreachBehavior(const std::function<void(const std::string&)>& func) const;
	private:
		std::unordered_map<std::string, FactoryFunction> m_registry;
	};
}