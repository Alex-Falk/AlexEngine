#pragma once

#include <rpc.h>

#include "nclgl/RenderNode.h"
#include "PhysicsEngine/PhysicsObject.h"
#include <Engine/Component.h>

class GameObject {

public:
	GameObject();
	~GameObject();

	UUID GetId();

	virtual void OnInitialise();

	void AddComponent(Component* component);

	template<class T>
	T* GetComponentOfType();

protected:

private:

	UUID m_id;

	std::vector<Component*> m_components;

};

