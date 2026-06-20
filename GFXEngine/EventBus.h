#pragma once
#include <string>
#include <functional>
#include <unordered_map>
#include "nlohmann/json.hpp"
#include "Utils.h"

namespace GFXEngine {

	struct Message {
		std::string type;
		nlohmann::json data;
		void* sender = nullptr;
		std::type_index senderType = typeid(void);

		//************************************
		// Method:    isSender
		// FullName:  GFXEngine::Message::isSender
		// Access:    public 
		// Returns:   bool
		// Qualifier: const
		//************************************
		template<typename T>
		bool isSender() const
		{
			return senderType == typeid(T);
		}

		//************************************
		// Method:    getSender
		// FullName:  GFXEngine::Message::getSender
		// Access:    public 
		// Returns:   T*
		// Qualifier: const
		//************************************
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

	struct MessageListener {
		std::string id;
		std::function<void(const Message&)> callback;
	};

	class EventBus
	{
	private:
		std::unordered_map<std::string, std::vector<MessageListener>> m_messageListeners;

	public:
		
		//************************************
		// Method:    EventBus
		// FullName:  GFXEngine::EventBus::EventBus
		// Access:    public 
		// Returns:   
		// Qualifier:
		//************************************
		EventBus() = default;
		
		//************************************
		// Method:    ~EventBus
		// FullName:  GFXEngine::EventBus::~EventBus
		// Access:    public 
		// Returns:   
		// Qualifier:
		//************************************
		~EventBus() = default;

		//************************************
		// Method:    subscribe
		// FullName:  GFXEngine::EventBus::subscribe
		// Access:    public 
		// Returns:   std::string
		// Qualifier:
		// Parameter: const std::string & messageType
		// Parameter: std::function<void
		// Parameter: const Message & 
		// Parameter: > callback
		//************************************
		std::string subscribe(const std::string& messageType, std::function<void(const Message&)> callback);
		
		//************************************
		// Method:    unsubscribe
		// FullName:  GFXEngine::EventBus::unsubscribe
		// Access:    public 
		// Returns:   bool
		// Qualifier:
		// Parameter: const std::string & listenerId
		//************************************
		bool unsubscribe(const std::string& listenerId);
		
		//************************************
		// Method:    emit
		// FullName:  GFXEngine::EventBus::emit
		// Access:    public 
		// Returns:   void
		// Qualifier:
		// Parameter: const Message & message
		//************************************
		void emit(const Message& message);
		
		//************************************
		// Method:    emit
		// FullName:  GFXEngine::EventBus::emit
		// Access:    public 
		// Returns:   void
		// Qualifier:
		// Parameter: const std::string & messageType
		// Parameter: const nlohmann::json & data
		// Parameter: void * sender
		// Parameter: std::type_index senderType
		//************************************
		void emit(const std::string& messageType, const nlohmann::json& data = {}, void* sender = nullptr, std::type_index senderType = typeid(void));
	};
}
