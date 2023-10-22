#ifndef __MODULEPLAYER_H__
#define __MODULEPLAYER_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "Point.h"

struct SDL_Texture;

class ModulePlayer : public Module
{
public:

	enum class PlayerState
	{
		IDLE,
		BCKWRD,
		FORWRD,
		JAB
	};

	ModulePlayer(bool start_enabled = true);
	~ModulePlayer();

	bool Start();
	update_status Update();
	bool CleanUp();

public:

	SDL_Texture* graphics = nullptr;
	Animation* currAnim = nullptr;

	Animation idle;
	Animation backward;
	Animation forward;
	Animation jab;
	iPoint position;

private:
	PlayerState playerState = PlayerState::IDLE;
};

#endif // __MODULEPLAYER_H__