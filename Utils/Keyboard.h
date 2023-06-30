#pragma once
#include "InputDevice.h"
class Keyboard : public InputDevice
{
public:
	Keyboard();
protected:
	void Update(RAWINPUT* rawInput) override;
	void UpdateHeld() override;
};

