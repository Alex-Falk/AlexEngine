#include "Keyboard.h"

Keyboard::Keyboard(HWND& hwnd)
{
	//Initialise the arrays to false!
	ZeroMemory(keyStates, KEYBOARD_MAX * sizeof(bool));
	ZeroMemory(holdStates, KEYBOARD_MAX * sizeof(bool));

	//Tedious windows RAW input stuff
	rid.usUsagePage = HID_USAGE_PAGE_GENERIC; //The keyboard isn't anything fancy
	rid.usUsage = HID_USAGE_GENERIC_KEYBOARD; //but it's definitely a keyboard!
	rid.dwFlags = RIDEV_INPUTSINK; //Yes, we want to always receive RAW input...
	rid.hwndTarget = hwnd; //Windows OS window handle
	RegisterRawInputDevices(&rid, 1, sizeof(rid)); //We just want one keyboard, please!
}

/*
Updates variables controlling whether a keyboard key has been
held for multiple frames.
*/
void Keyboard::UpdateHolds()
{
	memcpy(holdStates, keyStates, KEYBOARD_MAX * sizeof(bool));
}

/*
Sends the keyboard to sleep, so it doesn't process any
keypresses until it receives a Wake()
*/
void Keyboard::Sleep()
{
	isAwake = false; //Night night!
	//Prevents incorrectly thinking keys have been held / pressed when waking back up
	ZeroMemory(keyStates, KEYBOARD_MAX * sizeof(bool));
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
bool Keyboard::KeyHeld(const KeyboardKeys key)
{
	if (KeyDown(key) && holdStates[key])
	{
		return true;
	}
	return false;
}

/*
Returns true only if the key is down, but WASN't down last update.
Doesn't need bounds checking - a KeyboardKeys enum is always in range
*/
bool Keyboard::KeyTriggered(const KeyboardKeys key)
{
	return (KeyDown(key) && !KeyHeld(key));
}

void Keyboard::AddKeyMapping(const std::string& mappingName, KeyboardKeys key)
{
	m_keyMappings[mappingName] = key;
}

void Keyboard::RemoveKeyMapping(const std::string& mappingName)
{
	const auto itr = m_keyMappings.find(mappingName);
	if (itr != m_keyMappings.end())
	{
		m_keyMappings.erase(itr);
	}
}

bool Keyboard::KeyDown(const std::string& mappingName)
{
	const auto itr = m_keyMappings.find(mappingName);
	if (itr == m_keyMappings.end())
	{
		return false;
	}

	return KeyDown(itr->second);
}

bool Keyboard::KeyHeld(const std::string& mappingName)
{
	const auto itr = m_keyMappings.find(mappingName);
	if (itr == m_keyMappings.end())
	{
		return false;
	}

	return KeyHeld(itr->second);
}

bool Keyboard::KeyTriggered(const std::string& mappingName)
{
	const auto itr = m_keyMappings.find(mappingName);
	if (itr == m_keyMappings.end())
	{
		return false;
	}

	return KeyTriggered(itr->second);
}

/*
Updates the keyboard state with data received from the OS.
*/
void Keyboard::Update(RAWINPUT* raw)
{
	if (isAwake)
	{
		DWORD key = raw->data.keyboard.VKey;

		//We should do bounds checking!
		if (key < 0 || key > KEYBOARD_MAX)
		{
			return;
		}

		//First bit of the flags tag determines whether the key is down or up
		const auto keyboardKey = static_cast<KeyboardKeys>(key);
		bool wasDown = KeyDown(keyboardKey);
		keyStates[key] = !(raw->data.keyboard.Flags & RI_KEY_BREAK);
	}
}
