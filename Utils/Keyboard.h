#pragma once
#include "InputDevice.h"

namespace ae
{
	class Keyboard : public InputDevice
	{
	public:
		Keyboard();
	protected:
		void Update(RAWINPUT* rawInput) override;
		void UpdateHeld() override;
	};
}
