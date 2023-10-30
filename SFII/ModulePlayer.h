#ifndef __MODULEPLAYER_H__
#define __MODULEPLAYER_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "Point.h"

struct SDL_Texture;
struct Collider;

struct PlayerInput
{
	bool W_active;
	bool A_active;
	bool S_active;
	bool D_active;

	bool U_active;
	bool I_active;
	bool O_active;	
	bool J_active;
	bool K_active;
	bool L_active;
};

class ModulePlayer : public Module
{
public:

	enum class PlayerState
	{
		IDLE,
		CROUCH,
		JUMP,
		BCKWRD,
		FRWRD,
		JUMP_BCKWRD,
		JUMP_FORWRD,
		STANDING_LP,
		STANDING_MP,
		STANDING_HP,
		CROUCHING_LP,
		CROUCHING_MP,
		CROUCHING_HP
	};

	ModulePlayer(bool start_enabled = true);
	~ModulePlayer() override;

	bool Start() override;
	update_status PreUpdate() override;
	update_status Update() override;
	bool CleanUp() override;

private:

	SDL_Texture* graphics = nullptr;
	Animation* currAnim = nullptr;

	PlayerInput playerInput;
	PlayerState playerState;
	iPoint position;
	bool jumping = false;

	Animation idle;
	Animation crouch;
	Animation jump;
	Animation backward;	
	Animation forward;
	Animation jumpBackward;	
	Animation jumpForward;
	Animation standingLP;
	Animation standingMP;
	Animation standingHP;	
	Animation crouchingLP;
	Animation crouchingMP;
	Animation crouchingHP;
	Animation standingLK;
	Animation standingMK;
	Animation standingHK;

	Collider* playerCollider = nullptr;
};

#endif // __MODULEPLAYER_H__