#include "application.h"
#include "renderables.h"

#include <raylib.h>

#include "physicalworld.h"


Application::Application(){}


Application::~Application()
{
    for (auto renderable : m_renderables)
    {
        delete renderable;
        renderable = nullptr;
    }

    for (auto updateable : m_updateables)
    {
        delete updateable;
        updateable = nullptr;
    }
}


void Application::Initialize(int winW, int winH) {
    InitWindow(winW, winH, "Space Lander");
    InitAudioDevice();

    SetTargetFPS(60);
    // rlImGuiSetup(true);

    // -----------------------------------------
    // Instantiate World Objects
    // -----------------------------------------
    auto* mars = new MarsWorld();
    m_updateables.push_back(mars);
    m_renderables.push_back(mars);
}


void Application::Run()
{
    while (!WindowShouldClose())
    {
        Update(GetFrameTime());
        Render();
    }

    Shutdown();
}


void Application::Update(float dt)
{
    for (auto updateable : m_updateables)
    {
        updateable->Update(dt);
    }
}


void Application::Render()
{
    BeginDrawing();

    ClearBackground(RAYWHITE);

    for (const auto renderable : m_renderables)
    {
        renderable->Render();
    }

    DrawText("This is a raylib example", 10, 40, 20, DARKGRAY);

    DrawFPS(10, 10);

    EndDrawing();
}


void Application::Shutdown()
{
    CloseAudioDevice();
    CloseWindow();          // Close window and OpenGL context
}