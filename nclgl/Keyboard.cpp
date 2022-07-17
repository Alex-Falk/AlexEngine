#include "Keyboard.h"

Keyboard::Keyboard(HWND &hwnd)	{
	//Initialise the arrays to false!
	ZeroMemory(keyStates,  KEYBOARD_MAX * sizeof(bool));
	ZeroMemory(holdStates, KEYBOARD_MAX * sizeof(bool));

	//Tedious windows RAW input stuff
	rid.usUsagePage		= HID_USAGE_PAGE_GENERIC;		//The keyboard isn't anything fancy
    rid.usUsage			= HID_USAGE_GENERIC_KEYBOARD;	//but it's definitely a keyboard!
    rid.dwFlags			= RIDEV_INPUTSINK;				//Yes, we want to always receive RAW input...
    rid.hwndTarget		= hwnd;							//Windows OS window handle
    RegisterRawInputDevices(&rid, 1, sizeof(rid));		//We just want one keyboard, please!
}

/*
Updates variables controlling whether a keyboard key has been
held for multiple frames.
*/
void Keyboard::UpdateHolds()	{
	memcpy(holdStates,keyStates,KEYBOARD_MAX * sizeof(bool));
	
	for (const auto& itr : keyHeldMappings)
	{
		if (KeyHeld(itr.first))
		{
			for (const auto& otherItr : itr.second)
			{
				otherItr.second();
			}
		}
	}
}

/*
Sends the keyboard to sleep, so it doesn't process any
keypresses until it receives a Wake()
*/
void Keyboard::Sleep()	{
	isAwake = false;	//Night night!
	//Prevents incorrectly thinking keys have been held / pressed when waking back up
	ZeroMemory(keyStates,  KEYBOARD_MAX * sizeof(bool));
	ZeroMemory(holdStates, KEYBOARD_MAX * sizeof(bool));
}

/*
Returns if the key is down. Doesn't need bounds checking - 
a KeyboardKeys enum is always in range
*/
bool Keyboard::KeyDown(const KeyboardKeys key) const
{
	return keyStates[key];
}

/*
Returns if the key is down, and has been held down for multiple updates. 
Doesn't need bounds checking - a KeyboardKeys enum is always in range
*/
bool Keyboard::KeyHeld(const KeyboardKeys key)	{
	if(KeyDown(key) && holdStates[key]) {
		return true;
	}
	return false;
}

/*
Returns true only if the key is down, but WASN't down last update.
Doesn't need bounds checking - a KeyboardKeys enum is always in range
*/
bool Keyboard::KeyTriggered(const KeyboardKeys key)	 {
	return (KeyDown(key) && !KeyHeld(key));
}

void Keyboard::AddOnKeyDown(const KeyboardKeys key, const std::string& name, const std::function<void()> fn)
{
	keyDownMappings[key][name] = fn;
}

void Keyboard::AddOnKeyHeld(KeyboardKeys key, const std::string& name, std::function<void()> fn)
{
	keyHeldMappings[key][name] = fn;
}

void Keyboard::AddOnKeyUp(const KeyboardKeys key, const std::string& name, const std::function<void()> fn)
{
	keyUpMappings[key][name] = fn;
}

void Keyboard::RemoveOnKeyDown(const KeyboardKeys key, const std::string& name)
{
	const auto itr = keyDownMappings[key].find(name);
	keyDownMappings[key].erase(itr);
}

void Keyboard::RemoveOnKeyHeld(KeyboardKeys key, const std::string& name)
{
	const auto itr = keyHeldMappings[key].find(name);
	keyHeldMappings[key].erase(itr);
}

void Keyboard::RemoveOnKeyUp(const KeyboardKeys key, const std::string& name)
{
	const auto itr = keyUpMappings[key].find(name);
	keyUpMappings[key].erase(itr);
}


/*
Updates the keyboard state with data received from the OS.
*/
void Keyboard::Update(RAWINPUT* raw)	{
	if(isAwake)	{
		DWORD key = (DWORD)raw->data.keyboard.VKey;

		//We should do bounds checking!
		if(key < 0 || key > KEYBOARD_MAX)	{
			return;
		}

		//First bit of the flags tag determines whether the key is down or up
		const auto keyboardKey = static_cast<KeyboardKeys>(key);
		bool wasDown = KeyDown(keyboardKey);
		keyStates[key] = !(raw->data.keyboard.Flags & RI_KEY_BREAK);

		if (wasDown && !KeyDown(keyboardKey))
		{
			for (const auto& itr : keyUpMappings[keyboardKey])
			{
				itr.second();
			}
		}

		if(KeyTriggered(keyboardKey))
		{
			for (const auto& itr : keyDownMappings[keyboardKey])
			{
				itr.second();
			}
		}
	}
}