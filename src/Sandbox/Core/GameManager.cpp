#include "pch.h"
#ifndef GAME_MANAGER_CPP_DEFINED
#define GAME_MANAGER_CPP_DEFINED

#include "GameManager.h"

#include "Scene.h"
#include <stdlib.h>
#include <time.h>

#include "GameCamera.h"
#include "Tween.hpp"

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
    m_pGameCamera = new GameCamera();
    m_windowSize = gce::Vector2i32(width, height);
    m_pGameCamera->Init(title, width, height);

    srand(time(NULL));
}

void GameManager::GameLoop()
{
    chrono.Start();
    while (m_pGameCamera->IsWindowOpen() && m_isOpen)
    {
        m_deltatime = chrono.Reset();

        if (m_pCurrentScene == nullptr) continue;

        // Render logic
        m_pGameCamera->Begin();
        m_pCurrentScene->Draw(m_pGameCamera);
        m_pGameCamera->End();

        m_pGameCamera->Display();

        // Update logic
        if (m_pCurrentScene->m_isPaused == false) m_physicsSystem.PhysicsUpdate(m_deltatime);
        m_pCurrentScene->Update(m_deltatime);
        
        TweenSystem::Update(m_deltatime);

    }
    m_pCurrentScene->Uninit();
    return;
}

float32 GameManager::Deltatime() { return m_deltatime; }

Window* GameManager::GetWindow() { return m_pGameCamera->GetWindow(); }

#endif
