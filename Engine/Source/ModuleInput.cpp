#include "Globals.h"
#include "Application.h"
#include "ModuleInput.h"
#include "ModuleOpenGL.h"
#include "ModuleModel.h"
#include "ModuleTexture.h"
#include "SDL.h"

#include "backends/imgui_impl_sdl2.h"
#include <algorithm>

ModuleInput::ModuleInput()
{
	keyboard = new KeyState[MAX_KEYBOARD_BUTTONS];
}

// Destructor
ModuleInput::~ModuleInput()
{
	delete keyboard;
}

// Called before render is available
bool ModuleInput::Init()
{
	LOG("Init SDL input event system");
	bool ret = true;
	SDL_Init(0);

	if(SDL_InitSubSystem(SDL_INIT_EVENTS) < 0)
	{
		LOG("SDL_EVENTS could not initialize! SDL_Error: %s\n", SDL_GetError());
		ret = false;
	}

	return ret;
}

// Called every draw update
update_status ModuleInput::PreUpdate()
{
	const Uint8* keys = SDL_GetKeyboardState(NULL);

	for (int i = 0; i < MAX_KEYBOARD_BUTTONS; ++i)
	{
		if (keys[i] == 1)
		{
			if (keyboard[i] == KEY_IDLE)
				keyboard[i] = KEY_DOWN;
			else
				keyboard[i] = KEY_REPEAT;
		}
		else
		{
			if (keyboard[i] == KEY_REPEAT || keyboard[i] == KEY_DOWN)
				keyboard[i] = KEY_UP;
			else
				keyboard[i] = KEY_IDLE;
		}
	}

	//Uint32 buttons = SDL_GetMouseState((int*)&mousePos.x, (int*)&mousePos.y);

	for (int i = 0; i < MAX_MOUSE_BUTTONS; ++i)
	{
		if (mouseButtons[i] == KEY_DOWN)
			mouseButtons[i] = KEY_REPEAT;

		if (mouseButtons[i] == KEY_UP)
			mouseButtons[i] = KEY_IDLE;
	}

	mouseMotion = float2::zero;
	yWheel = 0;

	static int id;
    SDL_Event sdlEvent;
    while (SDL_PollEvent(&sdlEvent) != 0)
    {
        ImGui_ImplSDL2_ProcessEvent(&sdlEvent);
        switch (sdlEvent.type)
        {
            case SDL_QUIT:
                return UPDATE_STOP;
            case SDL_WINDOWEVENT:
				if (sdlEvent.window.event == SDL_WINDOWEVENT_RESIZED)
					App->render->WindowResized(sdlEvent.window.data1, sdlEvent.window.data2);
                if (sdlEvent.window.event == SDL_WINDOWEVENT_CLOSE)
                    return UPDATE_STOP;
                break;
			case SDL_MOUSEBUTTONDOWN:
				mouseButtons[sdlEvent.button.button - 1] = KEY_DOWN;
				break;
			case SDL_MOUSEBUTTONUP:
				mouseButtons[sdlEvent.button.button - 1] = KEY_UP;
				break;
			case SDL_MOUSEMOTION:
				mouseMotion.x = sdlEvent.motion.xrel;
				mouseMotion.y = sdlEvent.motion.yrel;
				mousePos.x = sdlEvent.motion.x;
				mousePos.y = sdlEvent.motion.y;
				//LOG("%f %f %f %f", mouseMotion.x, mouseMotion.y, mousePos.x, mousePos.y);
				break;
			case SDL_MOUSEWHEEL:
				yWheel = sdlEvent.wheel.y;
				break;
			case SDL_DROPFILE:	
				std::string temp = sdlEvent.drop.file;
				std::replace(temp.begin(), temp.end(), '\\', '/');
				if (strstr(temp.c_str(), ".gltf") != NULL)
				{
					App->model->CleanModel();
					App->model->LoadModel(temp.c_str());
				}
				if ((strstr(temp.c_str(), ".dds") != NULL) || (strstr(temp.c_str(), ".tga") != NULL) || (strstr(temp.c_str(), ".png") != NULL) || (strstr(temp.c_str(), ".jpg") != NULL))
				{
					App->texture->LoadTexture(temp.c_str());
				}
				break;
        }
    }

    return UPDATE_CONTINUE;
}

// Called before quitting
bool ModuleInput::CleanUp()
{
	LOG("Quitting SDL input event subsystem");
	SDL_QuitSubSystem(SDL_INIT_EVENTS);
	return true;
}

const KeyState ModuleInput::GetKey(int id) const
{
    return keyboard[id];
}

const KeyState ModuleInput::GetMouseButtonDown(int id) const
{
	return mouseButtons[id - 1];
}

const float2 ModuleInput::GetMousePos() const
{
	return mousePos;
}

const float2 ModuleInput::GetMouseMotion() const
{
	return mouseMotion;
}

const float ModuleInput::GetWheelScrollY() const
{
	return yWheel;
}
