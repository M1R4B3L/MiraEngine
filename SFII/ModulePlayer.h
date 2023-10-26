#ifndef __MODULEPLAYER_H__
#define __MODULEPLAYER_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "Point.h"

struct SDL_Texture;
struct Collider;

class ModulePlayer : public Module
{
public:

	enum class PlayerState
	{
		IDLE,
		CROUCH,
		BCKWRD,
		FORWRD,
		STANDING_LP,
		STANDING_MP,
		STANDING_HP,
		CROUCHING_LP,
		CROUCHING_MP,
		CROUCHING_HP
	};

	ModulePlayer(bool start_enabled = true);
	~ModulePlayer();

	bool Start() override;
	update_status Update() override;
	bool CleanUp() override;

private:

	SDL_Texture* graphics = nullptr;
	Animation* currAnim = nullptr;

	PlayerState playerState;
	iPoint position;

	Animation idle;
	Animation crouch;
	Animation backward;
	Animation forward;
	Animation standingLP;
	Animation standingMP;
	Animation standingHP;	
	Animation crouchingLP;
	Animation crouchingMP;
	Animation crouchingHP;

	Collider* playerCollider = nullptr;
};

#endif // __MODULEPLAYER_H__