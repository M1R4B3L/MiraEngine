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
	idle.frames.push_back({7, 14, 60, 89});
	idle.frames.push_back({94, 15, 60, 89});
	idle.frames.push_back({184, 14, 60, 89});
	idle.frames.push_back({280, 11, 55, 93});
	idle.frames.push_back({367, 12, 57, 93});
	idle.speed = 0.2f;

	crouch.frames.push_back({32,1206,53,89});
	crouch.frames.push_back({115,1207,57,89});
	crouch.frames.push_back({197,1207,61,89});
	crouch.speed = 0.3f;
	crouch.loop = false;

	jump.frames.push_back({17,843,60,89});
	jump.frames.push_back({100,823,56,104});
	jump.frames.push_back({176,805,50,89});
	jump.frames.push_back({251,798,54,77});
	jump.frames.push_back({327,813,48,70});
	jump.frames.push_back({397,810,48,89});
	jump.frames.push_back({464,819,55,109});
	jump.speed = 0.15f;
	jump.loop = false;

	// walk backward animation (arcade sprite sheet)
	backward.frames.push_back({542, 131, 61, 87});
	backward.frames.push_back({628, 129, 59, 90});
	backward.frames.push_back({713, 128, 57, 90});
	backward.frames.push_back({797, 127, 58, 90});
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

	standingLP.frames.push_back({19,272,67,91});
	standingLP.frames.push_back({108,272,92,91});
	standingLP.frames.push_back({108,272,92,91});
	standingLP.frames.push_back({108,272,92,91});
	standingLP.frames.push_back({19,272,67,91 });
	standingLP.speed = 0.38f;
	standingLP.loop = false;

	standingMP.frames.push_back({253,269,74,95});
	standingMP.frames.push_back({333,268,74,95});
	standingMP.frames.push_back({432,268,109,94});
	standingMP.frames.push_back({432,268,109,94});
	standingMP.frames.push_back({333,268,74,95 });
	standingMP.frames.push_back({253,269,74,95 });
	standingMP.speed = 0.39f;
	standingMP.loop = false;

	standingHP.frames.push_back({ 253,269,74,95 });
	standingHP.frames.push_back({ 333,268,74,95 });
	standingHP.frames.push_back({ 432,268,109,94 });
	standingHP.frames.push_back({ 432,268,109,94 });
	standingHP.frames.push_back({ 333,268,74,95 });
	standingHP.frames.push_back({ 253,269,74,95 });
	standingHP.speed = 0.21f;
	standingHP.loop = false;

	crouchingLP.frames.push_back({24,1316,69,89});
	crouchingLP.frames.push_back({118,1316,95,89});
	crouchingLP.frames.push_back({ 24,1316,69,89 });
	crouchingLP.speed = 0.38f;
	crouchingLP.loop = false;

	crouchingMP.frames.push_back({ 265,1316,64,89 });
	crouchingMP.frames.push_back({ 359,1316,66,89 });
	crouchingMP.frames.push_back({ 450,1316,92,89 });
	crouchingMP.frames.push_back({ 450,1316,92,89 });
	crouchingMP.frames.push_back({ 359,1316,66,89 });
	crouchingMP.frames.push_back({ 265,1316,64,89 });
	crouchingMP.speed = 0.19f;
	crouchingMP.loop = false;

	crouchingHP.frames.push_back({ 592,1316,60,89 });
	crouchingHP.frames.push_back({ 677,1315,73,91 });
	crouchingHP.frames.push_back({ 772,1279,57,126 });
	crouchingHP.frames.push_back({ 677,1315,73,91 });
	crouchingHP.frames.push_back({ 592,1316,60,89 });
	crouchingHP.speed = 0.045f;
	crouchingHP.loop = false;
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

	//TODO 100: Switch App->input for better optimization
	//TODO 101: Switch App->renderer->Blit for a function pls :)
	switch (playerState)
	{
	case PlayerState::IDLE:
		{	
			currAnim = &idle;
			playerSpeed = 0;

			App->renderer->Blit(graphics, position.x, position.y, &(currAnim->GetCurrentFrame()));
			
			if ((App->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT))
			{
				jumping = true;
				playerState = PlayerState::JUMP;
			}

			if (App->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT)
			{
				playerState = PlayerState::CROUCH;
			}

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
				playerState = PlayerState::STANDING_LP;
			}

			if (App->input->GetKey(SDL_SCANCODE_I) == KEY_DOWN)
			{
				playerState = PlayerState::STANDING_MP;
			}

			if (App->input->GetKey(SDL_SCANCODE_O) == KEY_DOWN)
			{
				playerState = PlayerState::STANDING_HP;
			}
			break;
		}
	case PlayerState::CROUCH:
		{
			currAnim = &crouch;
			playerSpeed = 0;

			App->renderer->Blit(graphics, position.x, position.y, &(currAnim->GetCurrentFrame()));

			if (!(App->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT))
			{
				currAnim->Reset();
				playerState = PlayerState::IDLE;
			}

			if (App->input->GetKey(SDL_SCANCODE_U) == KEY_DOWN)
			{
				playerState = PlayerState::CROUCHING_LP;
			}

			if (App->input->GetKey(SDL_SCANCODE_I) == KEY_DOWN)
			{
				playerState = PlayerState::CROUCHING_MP;
			}

			if (App->input->GetKey(SDL_SCANCODE_O) == KEY_DOWN)
			{
				playerState = PlayerState::CROUCHING_HP;
			}
			//CROUCH ATTACKS
			break;
		}
		//Movement
	case PlayerState::JUMP:
		{
			currAnim = &jump;
			if ((position.y >= 10) && jumping)
			{
				playerSpeed = 4;
				position.y -= playerSpeed;
			}
			else
			{
				jumping = false;
				position.y += playerSpeed;
			}
		
			App->renderer->Blit(graphics, position.x, position.y, &(currAnim->GetCurrentFrame()));
			
			if (currAnim->Finished() && position.y >= 110)
			{
				position.y = 110;
				currAnim->Reset();
				playerState = PlayerState::IDLE;
			}
			break;
		}
	case PlayerState::FORWRD:
		{	
			currAnim = &forward;
			playerSpeed = 3;
			position.x += playerSpeed;
			App->renderer->camera.x -= 1.25f;

			App->renderer->Blit(graphics, position.x, position.y, &(currAnim->GetCurrentFrame()));

			if (!(App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT))
			{
				playerState = PlayerState::IDLE;
			}

			if ((App->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT))
			{
				playerState = PlayerState::CROUCH;
			}

			if (App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT)
			{
				playerState = PlayerState::BCKWRD;
			}
			
			if (App->input->GetKey(SDL_SCANCODE_U) == KEY_DOWN)
			{
				playerState = PlayerState::STANDING_LP;
			}

			if (App->input->GetKey(SDL_SCANCODE_I) == KEY_DOWN)
			{
				playerState = PlayerState::STANDING_MP;
			}

			if (App->input->GetKey(SDL_SCANCODE_O) == KEY_DOWN)
			{
				playerState = PlayerState::STANDING_HP;
			}
			break;
		}	

	case PlayerState::BCKWRD:
		{
			currAnim = &backward;
			playerSpeed = 3;
			position.x -= playerSpeed;
			App->renderer->camera.x += 1.25f; 
			
			App->renderer->Blit(graphics, position.x, position.y, &(currAnim->GetCurrentFrame()));

			if (!(App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT))
			{
				playerState = PlayerState::IDLE;
			}

			if ((App->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT))
			{
				playerState = PlayerState::CROUCH;
			}

			if (App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT)
			{
				playerState = PlayerState::FORWRD;
			}

			if (App->input->GetKey(SDL_SCANCODE_U) == KEY_DOWN)
			{
				playerState = PlayerState::STANDING_LP;
			}

			if (App->input->GetKey(SDL_SCANCODE_I) == KEY_DOWN)
			{
				playerState = PlayerState::STANDING_MP;
			}

			if (App->input->GetKey(SDL_SCANCODE_O) == KEY_DOWN)
			{
				playerState = PlayerState::STANDING_HP;
			}
			break;
		}
		//Attacks
	case PlayerState::STANDING_LP:
		{
			currAnim = &standingLP;
			playerSpeed = 0;

			App->renderer->Blit(graphics, position.x, position.y, &(currAnim->GetCurrentFrame()));

			if (currAnim->Finished())
			{
				currAnim->Reset();
				playerState = PlayerState::IDLE;
			}
			//static int i = 0;
			//i++;
			//LOG("%d", i);
			break;
		}
	case PlayerState::STANDING_MP:
		{
			currAnim = &standingMP;
			playerSpeed = 0;

			App->renderer->Blit(graphics, position.x, position.y, &(currAnim->GetCurrentFrame()));

			if (currAnim->Finished())
			{
				currAnim->Reset();
				playerState = PlayerState::IDLE;
			}
			//static int i = 0;
			//i++;
			//LOG("%d", i);
			break;
		}
	case PlayerState::STANDING_HP:
		{
			currAnim = &standingHP;
			playerSpeed = 0;

			App->renderer->Blit(graphics, position.x, position.y, &(currAnim->GetCurrentFrame()));

			if (currAnim->Finished())
			{
				currAnim->Reset();
				playerState = PlayerState::IDLE;
			}
			//static int i = 0;
			//i++;
			//LOG("%d", i);
			break;
		}
	case PlayerState::CROUCHING_LP:
		{
			currAnim = &crouchingLP;
			playerSpeed = 0;

			App->renderer->Blit(graphics, position.x, position.y, &(currAnim->GetCurrentFrame()));

			if (currAnim->Finished() && (App->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT))
			{
				currAnim->Reset();
				playerState = PlayerState::CROUCH;
			}

			if(currAnim->Finished() && !(App->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT))
			{
				currAnim->Reset();
				playerState = PlayerState::IDLE;
			}

			//static int i = 0;
			//i++;
			//LOG("%d", i);
			break;
		}
	case PlayerState::CROUCHING_MP:
		{
			currAnim = &crouchingMP;
			playerSpeed = 0;

			App->renderer->Blit(graphics, position.x, position.y, &(currAnim->GetCurrentFrame()));

			if (currAnim->Finished() && (App->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT))
			{
				currAnim->Reset();
				playerState = PlayerState::CROUCH;
			}

			if (currAnim->Finished() && !(App->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT))
			{
				currAnim->Reset();
				playerState = PlayerState::IDLE;
			}

			//static int i = 0;
			//i++;
			//LOG("%d", i);
			break;
		}
	case PlayerState::CROUCHING_HP:
		{
			currAnim = &crouchingHP;
			playerSpeed = 0;

			if (currAnim->GetCurrentFrame().y == 1279)
			{
				position.y = 110 - 37;
				App->renderer->Blit(graphics, position.x, position.y, &(currAnim->GetCurrentFrame()));
			}
			else
			{
				position.y = 110;
				App->renderer->Blit(graphics, position.x, position.y, &(currAnim->GetCurrentFrame()));
			}

			if (currAnim->Finished() && (App->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT))
			{
				currAnim->Reset();
				playerState = PlayerState::CROUCH;
			}

			if (currAnim->Finished() && !(App->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT))
			{
				currAnim->Reset();
				playerState = PlayerState::IDLE;
			}
			//static int i = 0;
			//i++;
			//LOG("%d", i);
			break;
		}
	}

	//TODO 102: Render Only once cause position problems. Move to PostUpdate 
	//App->renderer->Blit(graphics, position.x, position.y, &(currAnim->GetCurrentFrame()));

	return UPDATE_CONTINUE;
}
