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

	bool Init() override;
	update_status PreUpdate() override;
	bool CleanUp() override; 

	// Check key states (includes mouse and joy buttons)
	const KeyState GetKey(int id) const;
	const KeyState GetMouseButtonDown(int id) const;
	const float2 GetMousePos() const;
	const float2 GetMouseMotion() const;
	const float GetWheelScrollY() const;
	

private:

	KeyState* keyboard = nullptr;
	KeyState  mouseButtons[MAX_MOUSE_BUTTONS];

	float2 mouseMotion;
	float2 mousePos;
	float yWheel;

};