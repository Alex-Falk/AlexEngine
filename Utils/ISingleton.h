#pragma once
#include <memory>

template <class T>
class ISingleton
{
public:
	ISingleton(const ISingleton&) = delete;
	ISingleton& operator=(const ISingleton&) = delete;

	static std::shared_ptr<T> Instance()
	{
		if (!m_instance)
		{
			m_instance = std::make_shared<T>();
		}

		return m_instance;
	}

	static void Delete()
	{
		if (m_instance)
		{
			m_instance.reset();
		}
	}
protected:
	ISingleton() = default;
	virtual ~ISingleton() = default;

private:
	static std::shared_ptr<T> m_instance;

};

template <class T>
std::shared_ptr<T> ISingleton<T>::m_instance = nullptr;
