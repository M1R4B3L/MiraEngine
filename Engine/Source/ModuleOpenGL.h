#pragma once

#include "Module.h"

struct SDL_Texture;
struct SDL_Renderer;
struct SDL_Rect;

class ModuleOpenGL : public Module
{
public:
	ModuleOpenGL();
	~ModuleOpenGL() override;

	bool Init() override;
	update_status PreUpdate() override;
	update_status Update() override;
	update_status PostUpdate() override;
	bool CleanUp() override;

	void WindowResized(unsigned width, unsigned height);
	void WindowSizeChanged(unsigned width, unsigned height);
	
	void* GetContext() { return context; }

private:
	void* context = nullptr;
	//unsigned vertexbuffer;

};
