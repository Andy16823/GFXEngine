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
		ServiceManager() = default;
		~ServiceManager() = default;

		template<typename T>
		T* getService(const std::string& serviceId) {
			auto it = m_services.find(serviceId);
			if (it != m_services.end()) {
				return static_cast<T*>(it->second.service);
			}
			return nullptr;
		}

		template<typename T>
		void addService(const std::string& serviceId, T* service) {
			if (m_services.find(serviceId) != m_services.end()) {
				throw std::runtime_error("Service with ID '" + serviceId + "' already exists");
			}
			m_services.emplace(serviceId, ServiceEntry{ typeid(T), static_cast<void*>(service) });
		}

		void removeService(const std::string& serviceId) {
			m_services.erase(serviceId);
		}

		void clearServices() {
			m_services.clear();
		}
	private:
		std::unordered_map<std::string, ServiceEntry> m_services;
	};
}