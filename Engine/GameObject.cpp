#include "GameObject.h"

#include "Components/PhysicsComponent.h"
#include "Components/RenderComponent.h"
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

void GameObject::AddComponent(std::unique_ptr<Component> component)
{
	if (component)
	{
		const auto type = component->GetId();
		if (m_components.find(type) != m_components.end())
		{
			return;
		}

		component->m_owner = this;
		m_components[type] = std::move(component);
	}
}

void GameObject::SetTransform(const Maths::Matrix4 transform)
{
	m_transform = transform;
}

Maths::Matrix4 GameObject::GetTransform() const
{
	if (auto* component = GetComponentOfType<PhysicsComponent>())
	{
		return component->GetWorldTransform();
	}
	else if (const auto* renderComponent = GetComponentOfType<RenderComponent>())
	{
		return renderComponent->GetWorldTransform();
	}

	NCLERROR("Game Object has neither got a Physics or Render Component")
	return Maths::Matrix4();
}

void GameObject::TranslatePosition(const Vector3& by)
{
	m_transform.Translate(by);
}

void GameObject::TranslateLocalPosition(const Vector3& by)
{
	//m_transform.Translate(by);
	GetComponentOfType<PhysicsComponent>()->TranslatePosition(by);
}

void GameObject::SetPosition(const Vector3& position)
{
	//m_transform.SetPositionVector(position);
	if (auto* component = GetComponentOfType<PhysicsComponent>())
	{
		component->SetPosition(position);
	}
}

void GameObject::SetRotation(const Maths::Quaternion& rotation)
{
	//const auto& pos = m_transform.GetPositionVector();
	//m_transform = rotation.ToMatrix4();
	//m_transform.SetPositionVector(pos);

	GetComponentOfType<PhysicsComponent>()->SetRotation(rotation);
}

void GameObject::OnUpdate(const float dt) const
{
	for (const auto& comp : m_components)
	{
		comp.second->OnUpdate(dt);
	}
}

template <class T>
T* GameObject::GetComponentOfType() const
{
	if (!std::is_base_of_v<Component, T>)
	{
		return nullptr;
	}

	ComponentHash id = typeid(T).hash_code();

	if (const auto comp = m_components.find(id); comp != m_components.end())
	{
		return static_cast<T*>(comp->second.get());
	}

	return nullptr;
}
