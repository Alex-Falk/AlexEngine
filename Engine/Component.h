#pragma once

class GameObject;

class Component
{
public:

	virtual void OnInitialise() {};

	inline GameObject* GetOwner() { return m_owner; }

private:
	GameObject* m_owner;

};

