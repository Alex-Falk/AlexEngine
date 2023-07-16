#pragma once

#include <map>
#include <typeindex>
#include <vector>

#include "Utils/ISingleton.h"

#define USE_SYSTEM(ptr) ptr = SystemManager::Instance()->GetSystem<std::decay_t<decltype(*ptr)>>();

namespace Ae
{
	class ISystem;
}

class SystemManager : public ISingleton<SystemManager>
{
public:
	template <class T>
	T* GetSystem()
	{
		const type_info& typeId = typeid(T);
		if (m_systems.find(typeId) != m_systems.end())
		{
			return dynamic_cast<T*>(m_systems[typeId]);
		}

		auto newSystem = new T();
		m_systems[typeId] = std::move(newSystem) ;
		return dynamic_cast<T*>(m_systems[typeId]);
	}

private:
	std::map<std::type_index, Ae::ISystem*> m_systems;
};

