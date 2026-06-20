#pragma once
#include <unordered_map>
#include <string>
#include <typeindex>
#include <stdexcept>

namespace GFXEngine {

	struct ServiceEntry {
		std::type_index type;
		void* service;
	};

	class ServiceManager {

	public:
		//************************************
		// Method:    ServiceManager
		// FullName:  GFXEngine::ServiceManager::ServiceManager
		// Access:    public 
		// Returns:   
		// Qualifier:
		//************************************
		ServiceManager() = default;
		
		//************************************
		// Method:    ServiceManager
		// FullName:  GFXEngine::ServiceManager::ServiceManager
		// Access:    
		// Returns:   
		// Qualifier:
		//************************************
		~ServiceManager() = default;

	public:
		//************************************
		// Method:    getService
		// FullName:  GFXEngine::ServiceManager::getService
		// Access:    public 
		// Returns:   T*
		// Qualifier:
		// Parameter: const std::string & serviceId
		//************************************
		template<typename T>
		T* getService(const std::string& serviceId) {
			auto it = m_services.find(serviceId);
			if (it != m_services.end()) {
				return static_cast<T*>(it->second.service);
			}
			return nullptr;
		}

		//************************************
		// Method:    addService
		// FullName:  GFXEngine::ServiceManager::addService
		// Access:    public 
		// Returns:   void
		// Qualifier:
		// Parameter: const std::string & serviceId
		// Parameter: T * service
		//************************************
		template<typename T>
		void addService(const std::string& serviceId, T* service) {
			if (m_services.find(serviceId) != m_services.end()) {
				throw std::runtime_error("Service with ID '" + serviceId + "' already exists");
			}
			m_services.emplace(serviceId, ServiceEntry{ typeid(T), static_cast<void*>(service) });
		}

		//************************************
		// Method:    removeService
		// FullName:  GFXEngine::ServiceManager::removeService
		// Access:    public 
		// Returns:   void
		// Qualifier:
		// Parameter: const std::string & serviceId
		//************************************
		void removeService(const std::string& serviceId) {
			m_services.erase(serviceId);
		}

		//************************************
		// Method:    clearServices
		// FullName:  GFXEngine::ServiceManager::clearServices
		// Access:    public 
		// Returns:   void
		// Qualifier:
		//************************************
		void clearServices() {
			m_services.clear();
		}

	private:
		std::unordered_map<std::string, ServiceEntry> m_services;
	};
}