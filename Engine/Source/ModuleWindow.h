#pragma once

#include "Module.h"
#include "SDL.h"

#include "Math/float2.h"

class Application;

class ModuleWindow : public Module
{
public:

	ModuleWindow();
	~ModuleWindow() override;

	bool Init() override;

	bool CleanUp() override;

	SDL_Window* GetWindow();

	const float2 GetWindowSize() const;
	const int GetWidth() const;
	const int GetHeight() const; 

	void SetWidth(int width); 
	void SetHeight(int height);

private:
	SDL_Window* window = nullptr;
	SDL_Surface* screen_surface = nullptr;

	float2 windowSize;
};
