#ifndef __MODULESCENEKEN_H__
#define __MODULESCENEKEN_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"

struct SDL_Texture;

class ModuleSceneKen : public Module
{
public:
	ModuleSceneKen( bool start_enabled = true);
	~ModuleSceneKen();

	bool Start() override;
	update_status Update() override;
	bool CleanUp() override;

private:
	
	SDL_Texture* graphics = nullptr;
	SDL_Rect ground;
	SDL_Rect background;
	SDL_Rect foreground;
	Animation flag;

	Animation orangeBoy;
	Animation purpleBoy;
	Animation greyPair;
	Animation redGirl;
	Animation greenBoy;
	Animation blueBoy;

};

#endif // __MODULESCENEKEN_H__