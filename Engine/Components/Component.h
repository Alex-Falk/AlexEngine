#pragma once
#include <string>
#include <vcruntime_typeinfo.h>

class GameObject;

class Component
{
	friend class GameObject;

public:
	virtual ~Component();
	Component(std::string name);

	virtual void OnInitialise() = 0;
	virtual void OnUpdate(float dt) = 0;

	GameObject* GetOwner() const { return m_owner; }

	std::string GetName() const { return m_name; }

protected:
	GameObject* m_owner;
	std::string m_name;
};
