#include "Component.h"

#include <typeinfo>

Component::~Component()
{
}

Component::Component(std::string name)
{
	m_name = std::move(name);
}

ComponentHash Component::GetId()
{
	return typeid(*this).hash_code();
}
