#pragma once
#include <map>

namespace GFXEngine {
	namespace Core {

		/// <summary>
		/// ServiceManager is a simple class that allows registering and retrieving services by a unique char identifier. 
		/// </summary>
		class ServiceManager {

		public:
			ServiceManager() = default;
			~ServiceManager() = default;

			template<typename T>
			T* getService(char serviceId) {
				return static_cast<T*>(m_services[serviceId]);
			}

			void registerService(char serviceId, void* service);
		private:
			std::map<char, void*> m_services;
		};
	}
}