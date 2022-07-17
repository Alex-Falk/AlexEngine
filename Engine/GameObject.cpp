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
	for (const auto& comp : m_components) {
		comp.second->OnInitialise();
	}
}

void GameObject::AddComponent(Component* component)
{	
	if (component)
	{
		auto type = component->GetType();
		if (m_components.find(type) != m_components.end())
		{
			return;
		}
		
		component->m_owner = this;
		m_components[type] = component;
	}
}

void GameObject::SetTransform(const Matrix4 transform)
{
	m_transform = transform;
}

Matrix4 GameObject::GetTransform() const
{
	return m_transform;
}

void GameObject::OnUpdate(const float dt) const
{
	for (const auto& comp : m_components)
	{
		comp.second->OnUpdate(dt);
	}
}

template<class T>
inline T* GameObject::GetComponentOfType()
{
	if (!std::is_base_of<Component, T>::value)
	{
		return nullptr;
	}

	auto comp = m_components.find(typeid(T).name());
	if ( comp != m_components.end())
	{
		return comp;
	}

	return nullptr;
}
