#pragma once
#include <vcruntime_typeinfo.h>

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

	const char* GetType() { return typeid(this).name(); }

protected:
	GameObject* m_owner;

	

};

