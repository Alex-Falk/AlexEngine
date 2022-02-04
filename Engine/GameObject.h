#pragma once

#include <rpc.h>

#include "nclgl/RenderNode.h"
#include "PhysicsEngine/Node.h"
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

	void SetTransform(const Matrix4 transform);
	Matrix4 GetTransform() const;

	void OnUpdate(float dt) const;
protected:

	

private:

	UUID m_id;

	std::vector<Component*> m_components;

	Matrix4 m_transform;
};

