
#include "engine.h"

Engine::Engine(string name, int width, int height)
{
    m_WINDOW_NAME = name;
    m_WINDOW_WIDTH = width;
    m_WINDOW_HEIGHT = height;
    m_FULLSCREEN = false;
}

Engine::Engine(string name)
{
    m_WINDOW_NAME = name;
    m_WINDOW_HEIGHT = 0;
    m_WINDOW_WIDTH = 0;
    m_FULLSCREEN = true;
}

Engine::~Engine()
{
    delete m_window;
    delete m_graphics;
    m_window = NULL;
    m_graphics = NULL;
}

bool Engine::Initialize(const vector<pair<GLenum, string>>& shaderVector)
{
    // Start a window
    m_window = new Window();
    if(!m_window->Initialize(m_WINDOW_NAME, &m_WINDOW_WIDTH, &m_WINDOW_HEIGHT))
    {
        printf("The window failed to initialize.\n");
        return false;
    }
    
    // Start the graphics
    m_graphics = new Graphics();
    if(!m_graphics->Initialize(m_WINDOW_WIDTH, m_WINDOW_HEIGHT, shaderVector))
    {
        printf("The graphics failed to initialize.\n");
        return false;
    }
    
    // Set the time
    m_currentTimeMillis = GetCurrentTimeMillis();
    
    // No errors
    return true;
}

void Engine::Run()
{
    m_running = true;
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    
    int width, height;
    unsigned char* pixels = NULL;
    io.Fonts->GetTexDataAsRGBA32(&pixels, &width, &height);
    
    while(m_running)
    {
        // Update the DT
        m_DT = getDT();
        
        // Check the keyboard and mouse input
        while(SDL_PollEvent(&m_event) != 0)
        {
            ImGui_ImplSDL2_ProcessEvent(&m_event);
            
            Keyboard();
            Mouse();
        }
        
        io.DisplaySize.x = 600.0f;             // set the current display width
        io.DisplaySize.y = 600.0f;             // set the current display height here
        
        m_window->InitImGui();
        
        // Update and render the graphics
        m_graphics->Update(m_DT);
        
        // Show MyGui
        ImGui::Begin("test");
        ImGui::Text("Testing");
        ImGui::End();
        ImGui::Render();
        
        m_graphics->Render();
        
        glViewport(0, 0, (int)io.DisplaySize.x, (int)io.DisplaySize.y);
        
        // Swap to the Window
        m_window->Swap();
    }
}

void Engine::Keyboard()
{
    if(m_event.type == SDL_QUIT)
    {
        m_running = false;
    }
    else if (m_event.type == SDL_KEYDOWN)
    {
        // handle key down events here
        if (m_event.key.keysym.sym == SDLK_ESCAPE)
        {
            m_running = false;
        }
        
        // Toggle Rotation Direction
        else if(m_event.key.keysym.sym == SDLK_r)
        {
            if(m_graphics != NULL)
            {
                m_graphics->ToggleRotationDirection();
            }
        }
        
        // Toggle Orbit Direction
        else if(m_event.key.keysym.sym == SDLK_o)
        {
            if(m_graphics != NULL)
            {
                m_graphics->ToggleOrbitDirection();
            }
        }
        
        // Pause Rotation
        else if(m_event.key.keysym.sym == SDLK_w)
        {
            if(m_graphics != NULL)
            {
                m_graphics->TogglePauseRotation();
            }
        }
        
        // Pause Orbit
        else if(m_event.key.keysym.sym == SDLK_s)
        {
            if(m_graphics != NULL)
            {
                m_graphics->TogglePauseOrbit();
            }
        }
        
        // Pause All
        else if(m_event.key.keysym.sym == SDLK_SPACE ||
                m_event.key.keysym.sym == SDLK_p)
        {
            if(m_graphics != NULL)
            {
                m_graphics->TogglePauseAll();
            }
        }
    }
}

void Engine::Mouse()
{
    if(m_event.type == SDL_MOUSEBUTTONDOWN)
    {
        if(SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT))
        {
            if(m_graphics != NULL)
            {
                m_graphics->ToggleOrbitDirection();
            }
        }
        
        else if(SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_RIGHT))
        {
            if(m_graphics != NULL)
            {
                m_graphics->ToggleRotationDirection();
            }
        }
        
        else if(SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_MIDDLE))
        {
            if(m_graphics != NULL)
            {
                m_graphics->TogglePauseAll();
            }
        }
        
        else if(SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_X1))
        {
            if(m_graphics != NULL)
            {
                m_graphics->TogglePauseRotation();
            }
        }
        
        else if(SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_X2))
        {
            if(m_graphics != NULL)
            {
                m_graphics->TogglePauseOrbit();
            }
        }
    }
}

unsigned int Engine::getDT()
{
    long long TimeNowMillis = GetCurrentTimeMillis();
    assert(TimeNowMillis >= m_currentTimeMillis);
    unsigned int DeltaTimeMillis = (unsigned int)(TimeNowMillis - m_currentTimeMillis);
    m_currentTimeMillis = TimeNowMillis;
    return DeltaTimeMillis;
}

long long Engine::GetCurrentTimeMillis()
{
    timeval t;
    gettimeofday(&t, NULL);
    long long ret = t.tv_sec * 1000 + t.tv_usec / 1000;
    return ret;
}
