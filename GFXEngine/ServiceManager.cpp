#include "ServiceManager.h"

void GFXEngine::Core::ServiceManager::registerService(char serviceId, void* service)
{
	m_services[serviceId] = service;
}
