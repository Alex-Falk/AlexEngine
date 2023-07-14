#pragma once
#include <Windows.h>

namespace ae
{
	class InputDevice
	{
	public:
		InputDevice();
		virtual ~InputDevice() = default;

		virtual void SetAwake(bool awake);
		bool IsAwake() const;

	protected:
		virtual void Update(RAWINPUT* rawInput) = 0;
		virtual void UpdateHeld() = 0;

		bool m_awake = true;
		RAWINPUTDEVICE m_rawInputDevice;
	};
}
