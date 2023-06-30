#include "InputDevice.h"

void InputDevice::SetAwake(bool awake)
{
	m_awake = awake;
}

bool InputDevice::IsAwake() const
{
	return m_awake;
}
