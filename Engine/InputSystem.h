#pragma once
#include "nclgl/Keyboard.h"
#include "nclgl/Mouse.h"
#include "nclgl/TSingleton.h"

class InputSystem : public TSingleton<InputSystem>
{
	friend class TSingleton<InputSystem>;

public:
	void BindKeyboardDown(KeyboardKeys key, std::string name, std::function<void> fn);
	void BindKeyboardUp(KeyboardKeys key, std::string name, std::function<void> fn);

	void UnbindKeyboardDown(KeyboardKeys key, std::string name);
	void UnbindKeyboardUp(KeyboardKeys key, std::string name);

	void UnbindKeyboardDown(KeyboardKeys key);
	void UnbindKeyboardUp(KeyboardKeys key);

	void BindMouseDown(MouseButtons button, std::string name, std::function<void> fn);
	void BindMouseUp(MouseButtons button, std::string name, std::function<void> fn);

	void UnbindMouseDown(KeyboardKeys key, std::string name);
	void UnbindMouseUp(KeyboardKeys key, std::string name);

	void UnbindMouseDown(KeyboardKeys key);
	void UnbindMouseUp(KeyboardKeys key);



private:

	Keyboard m_keyboard;
	Mouse m_mouse;
};

