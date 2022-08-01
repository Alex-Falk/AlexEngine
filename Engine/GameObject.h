#pragma once

#include <rpc.h>
#include <unordered_map>

#include "nclgl/RenderNode.h"
#include "PhysicsEngine/PhysicsNode.h"
#include <Engine/Component.h>
#include <Maths/Matrix4.h>

class GameObject
{
public:
	GameObject();
	virtual ~GameObject();

	UUID GetId();

	virtual void OnInitialise();

	void AddComponent(std::unique_ptr<Component> component);

	template <class T>
	T* GetComponentOfType();

	void SetTransform(Maths::Matrix4 transform);
	Maths::Matrix4 GetTransform() const;
	void TranslatePosition(const Vector3& by);
	void TranslateLocalPosition(const Vector3& by);

	void SetPosition(const Vector3& position);
	void SetRotation(const Maths::Quaternion& rotation);


	void OnUpdate(float dt) const;
protected:
	Maths::Matrix4 m_transform;

private:
	UUID m_id;

	unordered_map<std::string, std::unique_ptr<Component>> m_components;


};
