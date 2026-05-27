#pragma once
#include <string>
#include <functional>
#include <unordered_map>
#include "nlohmann/json.hpp"
#include "Utils.h"

namespace GFXEngine {

	/// <summary>
	/// Eventbus Message
	/// </summary>
	struct Message {
		std::string type;
		nlohmann::json data;
		std::string senderUUID;
	};

	/// <summary>
	/// Eventbus Message Listener
	/// </summary>
	struct MessageListener {
		std::string id;
		std::function<void(const Message&)> callback;
	};

	/// <summary>
	/// EventBus class for decoupled communication between entities and systems.
	/// </summary>
	class EventBus
	{
	private:
		std::unordered_map<std::string, std::vector<MessageListener>> m_messageListeners;

	public:
		EventBus() = default;
		~EventBus() = default;

		std::string subscribe(const std::string& messageType, std::function<void(const Message&)> callback);
		bool unsubscribe(const std::string& listenerId);
		void emit(const Message& message);
	};
}
