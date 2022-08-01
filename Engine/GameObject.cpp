#include "GameObject.h"
#include "nclgl/GraphicsPipeline.h"

GameObject::GameObject()
{
}

GameObject::~GameObject()
{
}

UUID GameObject::GetId()
{
	return m_id;
}

void GameObject::OnInitialise()
{
	for (const auto& comp : m_components)
	{
		comp.second->OnInitialise();
	}
}

void GameObject::AddComponent(Component* component)
{
	if (component)
	{
		auto type = component->GetName();
		if (m_components.find(type) != m_components.end())
		{
			return;
		}

		component->m_owner = this;
		m_components[type] = component;
	}
}

void GameObject::SetTransform(const Maths::Matrix4 transform)
{
	m_transform = transform;
}

Maths::Matrix4 GameObject::GetTransform() const
{
	return m_transform;
}

void GameObject::TranslatePosition(const Vector3& by)
{
	m_transform.Translate(by);
}

void GameObject::TranslateLocalPosition(const Vector3& by)
{
	m_transform.Translate(by);
}

void GameObject::SetPosition(const Vector3& position)
{
	m_transform.SetPositionVector(position);
}

void GameObject::SetRotation(const Maths::Quaternion& rotation)
{
	const auto& pos = m_transform.GetPositionVector();
	m_transform = rotation.ToMatrix4();
	m_transform.SetPositionVector(pos);
}

void GameObject::OnUpdate(const float dt) const
{
	for (const auto& comp : m_components)
	{
		comp.second->OnUpdate(dt);
	}
}

template <class T>
T* GameObject::GetComponentOfType()
{
	if (!std::is_base_of_v<Component, T>)
	{
		return nullptr;
	}

	auto comp = m_components.find(typeid(T).name());
	if (comp != m_components.end())
	{
		return comp;
	}

	return nullptr;
}
