#include "Globals.h"
#include "Application.h"
#include "ModuleWindow.h"
#include "ModuleOpengl.h"

ModuleWindow::ModuleWindow()
{
	windowSize.x = SCREEN_WIDTH;
	windowSize.y = SCREEN_HEIGHT;
}

// Destructor
ModuleWindow::~ModuleWindow()
{
}

// Called before render is available
bool ModuleWindow::Init()
{
	LOG("Init SDL window & surface");
	bool ret = true;

	if(SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		LOG("SDL_VIDEO could not initialize! SDL_Error: %s\n", SDL_GetError());
		ret = false;
	}
	else
	{

		Uint32 flags = SDL_WINDOW_SHOWN |  SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE;

		if(FULLSCREEN == true)
		{
			flags |= SDL_WINDOW_FULLSCREEN;
		}

		window = SDL_CreateWindow(TITLE, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, windowSize.x, windowSize.y, flags);

		if(window == NULL)
		{
			LOG("Window could not be created! SDL_Error: %s\n", SDL_GetError());
			ret = false;
		}
		else
		{
			//Get window surface
			
			screen_surface = SDL_GetWindowSurface(window);
		}
	}

	return ret;
}

// Called before quitting
bool ModuleWindow::CleanUp()
{
	LOG("Destroying SDL window and quitting all SDL systems");

	//Destroy window
	if(window != NULL)
	{
		SDL_DestroyWindow(window);
	}

	//Quit SDL subsystems
	SDL_Quit();
	return true;
}

SDL_Window* ModuleWindow::GetWindow()
{
	return window;
}

const float2 ModuleWindow::GetWindowSize() const
{
	return windowSize;
}

const int ModuleWindow::GetWidth() const
{
	return windowSize.x;
}

const int ModuleWindow::GetHeight() const
{
	return windowSize.y;
}

void ModuleWindow::SetWidth(int width)
{
	windowSize.x = width; 
	//SDL_SetWindowSize(window, windowSize.x, windowSize.y);
}

void ModuleWindow::SetHeight(int height)
{	
	windowSize.y = height; 
	//SDL_SetWindowSize(window, windowSize.x, windowSize.y);
}

