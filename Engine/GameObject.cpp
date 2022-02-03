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
	for (auto comp : m_components) {
		comp->OnInitialise();
	}
}

void GameObject::AddComponent(Component* component)
{
	if (component)
	{
		component->m_owner = this;
		m_components.push_back(component);
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
	for (const auto comp : m_components)
	{
		comp->OnUpdate(dt);
	}
}

template<class T>
inline T* GameObject::GetComponentOfType()
{
	//bool is_type = [](Component* c) {return dynamic_cast<T*>(c) != nullptr; }

	//return std::find_if(m_components.begin(), m_components.end(), is_type);
}
