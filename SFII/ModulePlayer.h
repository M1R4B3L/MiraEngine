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
		BCKWRD,
		FORWRD,
		JAB
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
	Animation backward;
	Animation forward;
	Animation jab;

	Collider* playerCollider = nullptr;
};

#endif // __MODULEPLAYER_H__