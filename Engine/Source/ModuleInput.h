#pragma once
#include "Module.h"
#include "Globals.h"

typedef unsigned __int8 Uint8;

enum KeyState
{
	KEY_IDLE = 0,
	KEY_DOWN,
	KEY_REPEAT,
	KEY_UP
};

class ModuleInput : public Module
{
public:
	
	ModuleInput();
	~ModuleInput() override;

	bool Init();
	update_status Update();
	bool CleanUp();

	// Check key states (includes mouse and joy buttons)
	const KeyState GetKey(int id) const;

	const KeyState GetMouseButtonDown(int id) const;

private:

	KeyState* keyboard = nullptr;
	KeyState  mouseButtons[MAX_MOUSE_BUTTONS];

	int mouseMotionX;
	int mouseMotionY;
	int mouseX;
	int mouseY;
};