#pragma once

#include<vector>

#include "Globals.h"
#include "Module.h"

class ModuleOpenGL;
class ModuleWindow;
class ModuleTextures;
class ModuleInput;
class ModuleProgram;
class ModuleRenderExercise;
class ModuleEditor;
class ModuleDebugDraw;
class ModuleCamera;

class Application
{
public:

	Application();
	~Application();

	bool Init();
	update_status Update();
	bool CleanUp();

    //Confusing @DEL
    //ModuleOpenGL* GetOpenGL() { return render; }
    //ModuleWindow* GetWindow() { return window; }
    //ModuleInput*  GetInput() { return input; }
    //ModuleProgram* GetProgram() { return program; }
    //ModuleRenderExercise* GetRenderExercise() { return renderExercise; }
    //ModuleEditor* GetEditor() { return editor; }

public:

    ModuleOpenGL* render = nullptr;
    ModuleWindow* window = nullptr;
    ModuleInput* input = nullptr;
    ModuleProgram* program = nullptr;
    ModuleRenderExercise* renderExercise = nullptr;
    ModuleEditor* editor = nullptr;
    ModuleDebugDraw* debugDraw = nullptr;
    ModuleCamera* camera = nullptr;

private:
    std::vector<Module*> modules;

};

extern Application* App;
