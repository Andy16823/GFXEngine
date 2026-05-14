#pragma once
#include "ServiceManager.h"

const std::string ASSET_MANAGER_SERVICE_ID = "AssetManager";
const std::string BEHAVIOR_REGISTRY_SERVICE_ID = "BehaviorRegistry";

namespace GFXEngine {
	class RuntimeContext
	{
	public: 
		static RuntimeContext& getInstance()
		{
			static RuntimeContext instance;
			return instance;
		}

		void addService(const std::string& serviceId, void* service) {
			m_serviceManager.addService(serviceId, service);
		}

		template<typename T>
		T* getService(const std::string& serviceId) {
			return m_serviceManager.getService<T>(serviceId);
		}

		void removeService(const std::string& serviceId) {
			m_serviceManager.removeService(serviceId);
		}
	private:
		RuntimeContext() = default;
		~RuntimeContext() = default;

		RuntimeContext(const RuntimeContext&) = delete;
		RuntimeContext& operator=(const RuntimeContext&) = delete;
		RuntimeContext(RuntimeContext&&) = delete;
		RuntimeContext& operator=(RuntimeContext&&) = delete;

		Core::ServiceManager m_serviceManager;
	};
}
