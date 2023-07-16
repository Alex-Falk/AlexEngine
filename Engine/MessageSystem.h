#pragma once

#include <functional>
#include <map>
#include <queue>
#include <vector>

#include "Interfaces/ISystem.h"
#include "Utils/ISingleton.h"
#include "Message.h"


namespace ae
{
	using MessageCallback = std::function<void(Message& msg)>;

	class MessageSystem : public Ae::ISystem
	{
	public:
		template <class T>
		void subscribe(MessageCallback callback);

		template <class T>
		void unsubscribe(MessageCallback callback);

		void addMessage(Message& msg);
		void onUpdate(float dt) override;

	private:
		std::map<MessageHash, std::vector<MessageCallback>> m_subscribers;
		std::queue<Message> m_messageQueue;
	};
}

template <class T>
void ae::MessageSystem::subscribe(MessageCallback callback)
{
	MessageHash id = typeid(T).hash_code();
	if (m_subscribers.find(id) == m_subscribers.end())
	{
		m_subscribers.emplace(id, std::vector<MessageCallback>{ callback });
	}
	else
	{
		//TODO: what is this function is already here?
		m_subscribers[id].push_back(callback);
	}
}

template <class T>
void ae::MessageSystem::unsubscribe(MessageCallback callback)
{
	MessageHash id = typeid(T).hash_code();
	if (m_subscribers.find(id) != m_subscribers.end())
	{
		auto& vec = m_subscribers[id];
		std::erase(vec, callback);

		if (vec.empty())
		{
			m_subscribers.erase(id);
		}
	}
}
