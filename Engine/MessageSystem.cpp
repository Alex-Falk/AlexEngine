#include "MessageSystem.h"

void ae::MessageSystem::addMessage(Message& msg)
{
	m_messageQueue.push(msg);
}

void ae::MessageSystem::onUpdate(float dt)
{
	while (!m_messageQueue.empty())
	{
		auto& msg = m_messageQueue.back();
		if (m_subscribers.find(msg.GetId()) != m_subscribers.end())
		{
			for (auto& subscriber : m_subscribers[msg.GetId()])
			{
				subscriber(msg);
			}
		}

		m_messageQueue.pop();
	}
}

