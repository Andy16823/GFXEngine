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
		void* sender = nullptr;
		std::type_index senderType = typeid(void);

		template<typename T>
		bool isSender() const
		{
			return senderType == typeid(T);
		}

		template<typename T>
		T* getSender() const
		{
			if (senderType == typeid(T))
			{
				return static_cast<T*>(sender);
			}

			return nullptr;
		}
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
		void emit(const std::string& messageType, const nlohmann::json& data = {}, void* sender = nullptr, std::type_index senderType = typeid(void));
		void emit(const std::string& messageType, const std::string& message, void* sender = nullptr, std::type_index senderType = typeid(void));
	};
}
