#ifndef __ModuleWindow_H__
#define __ModuleWindow_H__

#include "Module.h"
#include "SDL.h"

class Application;

class ModuleWindow : public Module
{
public:

	ModuleWindow();
	~ModuleWindow() override;

	bool Init() override;

	bool CleanUp() override;

	SDL_Window* GetWindow() { return window; }

	const int GetWidth() const { return width; }
	const int GetHeight() const { return height; }

	void SetWidth(int _width) { width = _width; }
	void SetHeight(int _height) { height = _height; }

private:
	SDL_Window* window = nullptr;
	SDL_Surface* screen_surface = nullptr;

	int width;
	int height;
};

#endif // __ModuleWindow_H__