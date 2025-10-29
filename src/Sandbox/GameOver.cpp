#include "pch.h"
#ifndef GAMEOVER_CPP_DEFINED
#define GAMEOVER_CPP_DEFINED

#include "GameOver.h"
#include "Core/GameCamera.h"
#include "Core/GameManager.h"
#include "Button.h"
#include <fstream>
#include <nlohmann.hpp>

#include "Menu.h"

void GameOver::Init()
{
    m_isPaused = false;
    GameCamera* cam = GameManager::Get()->GetGameCamera();
    cam->Init(L"3D Runner", 1280, 720, CameraType::PERSPECTIVE);
    cam->SetPosition({0.0f, 0.0f, -50.0f});
    cam->SetRotation({0.0f, 0.0f, 0.0f});
    cam->SetFOV(gce::PI/3.0f);
    cam->SetFarPlane(500.0f);
    cam->SetNearPlane(0.001f);
    
    std::ifstream in("../../res/JSON/score.json");
    if (in.is_open())
    {
        nlohmann::json score;
        in >> score;
        in.close();
        
        m_score = score["score"];
        m_bestScore = score["bestScore"];
    }

    gce::Vector2i32 screenPos = GameManager::Get()->GetWindowSize();
    
    std::wstring textScore = L"My score : " + std::to_wstring(m_score);
    Text* score = CreateText(textScore);
    score->SetPosition({screenPos.x / 2.f - 125.f, 100.f});
    score->SetColor(gce::Color::White);
    
    std::wstring textBestScore = L"Best score : " + std::to_wstring(m_bestScore);
    Text* bestScore = CreateText(textBestScore);
    bestScore->SetPosition({screenPos.x / 2.f - 125.f, 200.f});
    bestScore->SetColor(gce::Color::White);

    Button* menuBtn = CreateObject<Button>();
    menuBtn->Init(L"MENU");
    menuBtn->m_transform.position = {0.0f, -12.5f, 0.0f};
    menuBtn->m_transform.scale = {30.0f, 10.0f, 1.0f};
    menuBtn->SetTextPos(-67, 200);
    menuBtn->SetName("exit");
    
}

void GameOver::Uninit()
{
    Scene::Uninit();
}


void GameOver::Update(float deltaTime)
{
    Scene::Update(deltaTime);
    if (GetKeyDown(Keyboard::ENTER))
    {
        GameManager::Get()->SetCurrentScene<Menu>();
    }
}

#endif