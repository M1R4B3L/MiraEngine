#include "Globals.h"
#include "Application.h"
#include "ModulePlayer.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleTextures.h"
#include "ModuleCollision.h"
#include "SDL/include/SDL.h"

// Reference at https://www.youtube.com/watch?v=OEhmUuehGOA
ModulePlayer::ModulePlayer(bool start_enabled) : Module(start_enabled)
{
	playerState = PlayerState::IDLE;

	position.x = 75;
	position.y = 110;

	// idle animation (arcade sprite sheet)
	idle.frames.push_back({7, 14, 60, 90});
	idle.frames.push_back({95, 15, 60, 89});
	idle.frames.push_back({184, 14, 60, 90});
	idle.frames.push_back({276, 11, 60, 93});
	idle.frames.push_back({366, 12, 60, 92});
	idle.speed = 0.2f;
	
	// walk backward animation (arcade sprite sheet)
	backward.frames.push_back({542, 131, 61, 87});
	backward.frames.push_back({628, 129, 59, 90});
	backward.frames.push_back({713, 128, 57, 90});
	backward.frames.push_back({797, 127, 57, 90});
	backward.frames.push_back({883, 128, 58, 91});
	backward.frames.push_back({974, 129, 57, 89});
	backward.speed = 0.08f;

	// TODO 8: setup the walk forward animation from ryu4.png
	forward.frames.push_back({9,128,60,91});
	forward.frames.push_back({78,128,76,91});
	forward.frames.push_back({162,128,76,92});
	forward.frames.push_back({259,128,76,91});
	forward.frames.push_back({352,128,76,91});
	forward.frames.push_back({432,128,76,92});
	forward.speed = 0.08f;

	jab.frames.push_back({19,272,67,91});
	jab.frames.push_back({108,272,92,91});
	jab.frames.push_back({108,272,92,91});
	jab.frames.push_back({108,272,92,91});
	jab.frames.push_back({19,272,67,91 });
	jab.speed = 0.38f;
	jab.loop = false;
}

ModulePlayer::~ModulePlayer()
{
	// Homework : check for memory leaks
}

// Load assets
bool ModulePlayer::Start()
{
	LOG("Loading player");

	graphics = App->textures->Load("ryu4.png"); // arcade version
	currAnim = &idle;

	return true;
}

// Unload assets
bool ModulePlayer::CleanUp()
{
	LOG("Unloading player");

	App->textures->Unload(graphics);

	return true;
}

// Update
update_status ModulePlayer::Update()
{
	// TODO 9: Draw the player with its animation
	// make sure to detect player movement and change its
	// position while cycling the animation(check Animation.h)

	static int playerSpeed = 0;

	//TODO: Move Rendering to Post Update

	switch (playerState)
	{
	case PlayerState::IDLE:
		{	
			currAnim = &idle;
			playerSpeed = 0;
 
			if (App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT)
			{
				playerState = PlayerState::FORWRD;
			}

			if (App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT)
			{
				playerState = PlayerState::BCKWRD;
			}

			if (App->input->GetKey(SDL_SCANCODE_U) == KEY_DOWN)
			{
				playerState = PlayerState::JAB;
			}

			App->renderer->Blit(graphics, position.x, position.y, &(currAnim->GetCurrentFrame()));
			break;
		}
		//Movement
	case PlayerState::FORWRD:
		{	
			currAnim = &forward;
			playerSpeed = 3;
			position.x += playerSpeed;
			App->renderer->camera.x -= 1.25f;

			if (!(App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT))
			{
				playerState = PlayerState::IDLE;
			}

			if (App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT)
			{
				playerState = PlayerState::BCKWRD;
			}

			if (App->input->GetKey(SDL_SCANCODE_U) == KEY_DOWN)
			{
				playerState = PlayerState::JAB;
			}

			App->renderer->Blit(graphics, position.x, position.y, &(currAnim->GetCurrentFrame()));
			break;
		}	

	case PlayerState::BCKWRD:
		{
			currAnim = &backward;
			playerSpeed = 3;
			position.x -= playerSpeed;
			App->renderer->camera.x += 1.25f;

			if (App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT)
			{
				playerState = PlayerState::FORWRD;
			}

			if (!(App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT))
			{
				playerState = PlayerState::IDLE;
			}

			if (App->input->GetKey(SDL_SCANCODE_U) == KEY_DOWN)
			{
				playerState = PlayerState::JAB;
			}

			App->renderer->Blit(graphics, position.x, position.y, &(currAnim->GetCurrentFrame()));
			break;
		}
		//Attacks
	case PlayerState::JAB:
		{

			currAnim = &jab;
			playerSpeed = 0;

			if (currAnim->Finished())
			{
				currAnim->Reset();
				playerState = PlayerState::IDLE;
			}

			App->renderer->Blit(graphics, position.x, position.y, &(currAnim->GetCurrentFrame()));
			//static int i = 0;
			//i++;
			//LOG("%d", i);
			break;
		}
	}


	return UPDATE_CONTINUE;
}