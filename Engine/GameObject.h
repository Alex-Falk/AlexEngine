#pragma once

#include <rpc.h>
#include <unordered_map>

#include "nclgl/RenderNode.h"
#include "PhysicsEngine/PhysicsNode.h"
#include <Engine/Component.h>

class GameObject {

public:
	GameObject();
	virtual ~GameObject();

	UUID GetId();

	virtual void OnInitialise();

	void AddComponent(Component* component);

	template<class T>
	T* GetComponentOfType();

	void SetTransform(const Matrix4 transform);
	Matrix4 GetTransform() const;
	void TranslatePosition(const Vector3& by);
	void TranslateLocalPosition(const Vector3& by);

	void SetPosition(const Vector3& position);
	void SetRotation(const Quaternion& rotation);

	

	void OnUpdate(float dt) const;
protected:

	

private:

	UUID m_id;

	unordered_map<std::string, Component*> m_components;

	Matrix4 m_transform;
};

