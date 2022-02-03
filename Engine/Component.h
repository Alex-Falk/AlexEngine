#pragma once

class GameObject;

class Component
{
	friend class GameObject;

public:
	virtual ~Component();
	Component();

	virtual void OnInitialise() = 0;
	virtual void OnUpdate(float dt) = 0;

	inline GameObject* GetOwner() const { return m_owner; }

protected:
	GameObject* m_owner;

};

