#pragma once

#include "Module.h"
#include "Globals.h"

#include "Math/float2.h"

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
	~ModuleInput();

	bool Init();
	update_status PreUpdate();
	bool CleanUp();

	// Check key states (includes mouse and joy buttons)
	const KeyState GetKey(int id) const;

	const KeyState GetMouseButtonDown(int id) const;

private:

	KeyState* keyboard = nullptr;
	KeyState  mouseButtons[MAX_MOUSE_BUTTONS];

public:

	float2 mouseMotion;
	float2 mousePos;
	float yWheel;
};