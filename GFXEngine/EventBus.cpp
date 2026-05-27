#include "EventBus.h"

std::string GFXEngine::EventBus::subscribe(const std::string& messageType, std::function<void(const Message&)> callback)
{
	std::string listenerId = Utils::generateUUID();
	m_messageListeners[messageType].push_back({ listenerId, std::move(callback) });
	return listenerId;
}

bool GFXEngine::EventBus::unsubscribe(const std::string& listenerId)
{
	for (auto& [messageType, listeners] : m_messageListeners) {
		auto it = std::remove_if(listeners.begin(), listeners.end(),
			[listenerId](const MessageListener& listener) {
				return listener.id == listenerId;
			});
		if (it != listeners.end()) {
			listeners.erase(it, listeners.end());
			return true;
		}
	}
	return false;
}

void GFXEngine::EventBus::emit(const Message& message)
{
	if (m_messageListeners.find(message.type) != m_messageListeners.end()) {
		for (const auto& listener : m_messageListeners[message.type]) {
			listener.callback(message);
		}
	}
}

void GFXEngine::EventBus::emit(const std::string& messageType, const std::string& message, void* sender /*= nullptr*/, std::type_index senderType /*= typeid(void)*/)
{
	emit(messageType, nlohmann::json{ {"message", message} }, sender, senderType);
}

void GFXEngine::EventBus::emit(const std::string& messageType, const nlohmann::json& data /*= {}*/, void* sender /*= nullptr*/, std::type_index senderType /*= typeid(void)*/)
{
	Message message{ messageType, data, sender, senderType };
	emit(message);
}
