#include "Application.h"
#include "ModuleWindow.h"
#include "ModuleOpenGL.h"
#include "ModuleEditor.h"
#include "EditorPanelManager.h"
#include "AboutPanel.h"
#include "MenuBarPanel.h"

#include "backends/imgui_impl_sdl2.h"
#include "backends/imgui_impl_opengl3.h"

#include "imgui.h"

ModuleEditor::ModuleEditor()
{
    editorPanels.reserve(2);

    editorPanels.push_back(menuBar = new MenuBarPanel());
    editorPanels.push_back(about = new AboutPanel());


    aboutOpen = true;
}

ModuleEditor::~ModuleEditor()
{
    for (std::vector<EditorPanelManager*>::iterator it = editorPanels.begin(); it != editorPanels.end(); ++it)
    {
        delete* it;
    }

    editorPanels.clear();
}

bool ModuleEditor::Init()
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    io = &(ImGui::GetIO());
    io->ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    io->ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
    io->ConfigFlags |= ImGuiConfigFlags_DockingEnable;         // Enable Docking
    io->ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;       // Enable Multi-Viewport / Platform Windows

    //TODO ImGui::Style
    
    ImGui_ImplSDL2_InitForOpenGL(App->window->GetWindow(), App->render->GetContext());
    ImGui_ImplOpenGL3_Init("#version 460");

    return true;
}

update_status ModuleEditor::Update()
{
    update_status ret = update_status::UPDATE_CONTINUE;

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplSDL2_NewFrame();
    ImGui::NewFrame();

    static bool docking = true;
    
    //if (CreateDockWindow("Root Window", true, ImGuiWindowFlags_MenuBar))
    //{
    //    //TODO Change to handle if is active
    //  
    //    bool draw = true;
    //    for (unsigned i = 0; i < editorPanels.size(); ++i)
    //    {
    //        if (editorPanels[i]->IsOpen())
    //        {
    //            draw = editorPanels[i]->Draw();
    //
    //            if (!draw)
    //            {
    //                ret = update_status::UPDATE_STOP;
    //                LOG("[EDITOR] Exited through %s Panel", editorPanels[i]->GetName());
    //                break;
    //            }
    //        }
    //    }
    //
    //    ImGui::End();
    //}

    //ImGui::ShowDemoWindow();

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    if (io->ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
        SDL_Window* backup_current_window = SDL_GL_GetCurrentWindow();
        SDL_GLContext backup_current_context = SDL_GL_GetCurrentContext();
        ImGui::UpdatePlatformWindows();
        ImGui::RenderPlatformWindowsDefault();
        
        SDL_GL_MakeCurrent(backup_current_window, backup_current_context);
    }

    return ret;
}

bool ModuleEditor::CleanUp()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();

    return true;
}

bool ModuleEditor::CreateDockWindow(const char* name, bool open, int windowFlags)
{
    bool ret = true;

    windowFlags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove
        | ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus
        | ImGuiWindowFlags_NoDocking | ImGuiWindowFlags_NoBackground;

    //TODO Only if window resize
    ImGuiViewport* viewport = ImGui::GetWindowViewport();

    ImGui::SetNextWindowPos(viewport->Pos);
    ImGui::SetNextWindowSize(viewport->Size);
    ImGui::SetNextWindowViewport(viewport->ID);
    //Resize

    //ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));

    ret = ImGui::Begin(name, &open, windowFlags);

    ImGui::PopStyleVar(2);

    //Deactivate Docking???
    //if (docking)
    {
        if (io->ConfigFlags & ImGuiConfigFlags_DockingEnable)
        {
            ImGuiID dckspace_id = ImGui::GetID("Root Window");
            ImGui::DockSpace(dckspace_id, ImVec2(0.0, 0.0), ImGuiDockNodeFlags_PassthruCentralNode);
        }
    }

    return ret;
}

