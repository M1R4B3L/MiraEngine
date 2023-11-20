#pragma once

#include <stdio.h>

#define LOG(format, ...) log(__FILE__, __LINE__, format, __VA_ARGS__);

void log(const char file[], int line, const char* format, ...);

enum update_status
{
	UPDATE_CONTINUE = 1,
	UPDATE_STOP,
	UPDATE_ERROR
};

// Configuration -----------
#define SCREEN_WIDTH 640 //1280	
#define SCREEN_HEIGHT 480 //720
#define MAX_KEYBOARD_BUTTONS 300
#define MAX_MOUSE_BUTTONS 5
#define FULLSCREEN false
#define VSYNC false
#define TITLE "Yes Darling"
