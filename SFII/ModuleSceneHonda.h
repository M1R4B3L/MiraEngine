#ifndef __MODULESCENEHONDA_H__
#define __MODULESCENEHONDA_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"

struct SDL_Texture;

class ModuleSceneHonda : public Module
{
public:
	ModuleSceneHonda( bool start_enabled = true);
	~ModuleSceneHonda();

	bool Start() override;
	update_status Update() override;
	bool CleanUp() override;

private:
	
	SDL_Texture* graphics = nullptr;
	SDL_Rect ground;
	SDL_Rect background;
	SDL_Rect foreground;
	Animation flag;
	Animation redGirl;
};

#endif // __MODULESCENEKEN_H__