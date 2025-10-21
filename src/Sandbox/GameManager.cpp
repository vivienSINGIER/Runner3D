#include "pch.h"
#ifndef GAME_MANAGER_CPP_DEFINED
#define GAME_MANAGER_CPP_DEFINED

#include "GameManager.h"

#include "Scene.h"
#include <stdlib.h>
#include <time.h>

GameManager* GameManager::s_pInstance = nullptr;

GameManager::GameManager() : chrono()
{
    
}

GameManager::~GameManager()
{
    for (Scene* scene : m_scenes)
    {
        delete scene;
    }
    m_scenes.clear();
}

GameManager* GameManager::Get()
{
    if (s_pInstance == nullptr)
        s_pInstance = new GameManager();

    return s_pInstance;
}

void GameManager::Init(std::wstring_view title, uint32 width, uint32 height)
{
    m_pWindow = new Window(title, width, height);
    
    camera = new Camera(CameraType::PERSPECTIVE);
    camera->SetPosition({0.0f, 20.0f, -20.0f});
    camera->SetRotation({45.0f, 0.0f, 0.0f});
    camera->SetFOV(gce::PI/4.0f);
    camera->SetFarPlane(500.0f);
    camera->SetNearPlane(0.001f);

    srand(time(NULL));
}

void GameManager::GameLoop()
{
    chrono.Start();
    while (m_pWindow->IsOpen())
    {
        m_deltatime = chrono.Reset();

        if (m_pCurrentScene == nullptr) continue;
        
        m_pWindow->Begin(*camera);
        m_pCurrentScene->Draw(m_pWindow);
        m_pWindow->End();

        m_pWindow->Display();
        
        if (m_pCurrentScene->m_isPaused == false) m_physicsSystem.PhysicsUpdate();
        m_pCurrentScene->Update(m_deltatime);
    }
}

float32 GameManager::Deltatime() { return m_deltatime; }

Window* GameManager::GetWindow() { return m_pWindow;   }

#endif
