#include "InputDevice.h"

void ae::InputDevice::SetAwake(bool awake)
{
	m_awake = awake;
}

bool ae::InputDevice::IsAwake() const
{
	return m_awake;
}
