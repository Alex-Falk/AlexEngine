#include "GameObject.h"
#include "PhysicsEngine/GraphicsPipeline.h"

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
		m_components.push_back(component);
}

template<class T>
inline T* GameObject::GetComponentOfType()
{
	//bool is_type = [](Component* c) {return dynamic_cast<T*>(c) != nullptr; }

	//return std::find_if(m_components.begin(), m_components.end(), is_type);
}