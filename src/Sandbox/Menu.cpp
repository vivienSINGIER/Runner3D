#include "pch.h"
#ifndef MENU_CPP_DEFINED
#define MENU_CPP_DEFINED

#include "Menu.h"

#include "Button.h"
#include "Core/GameCamera.h"
#include "Core/GameManager.h"
#include "Runner3D.h"
#include <nlohmann.hpp>

void Menu::Init()
{
    m_isPaused = false;
    GameCamera* cam = GameManager::Get()->GetGameCamera();
    cam->Init(L"3D Runner", 1280, 720, CameraType::PERSPECTIVE);
    cam->SetPosition({0.0f, 0.0f, -50.0f});
    cam->SetRotation({0.0f, 0.0f, 0.0f});
    cam->SetFOV(gce::PI/3.0f);
    cam->SetFarPlane(500.0f);
    cam->SetNearPlane(0.001f);

    
    Button* playBtn = CreateObject<Button>();
    playBtn->Init(L"PLAY");
    playBtn->m_transform.position = {0.0f, 0.0f, 0.0f};
    playBtn->m_transform.scale = {30.0f, 10.0f, 1.0f};
    playBtn->SetTextPos(-70, -37);
    playBtn->SetName("play");
    m_vectButtons.PushBack(playBtn);

    m_selectedBtn = playBtn;
    
    Button* exitBtn = CreateObject<Button>();
    exitBtn->Init(L"EXIT");
    exitBtn->m_transform.position = {0.0f, -12.5f, 0.0f};
    exitBtn->m_transform.scale = {30.0f, 10.0f, 1.0f};
    exitBtn->SetTextPos(-67, 200);
    exitBtn->SetName("exit");
    m_vectButtons.PushBack(exitBtn);

    Text* titleText = CreateText(L"POLY RUN");
    titleText->SetPosition({830, 200});
    titleText->SetColor(gce::Color::White);
}

void Menu::Uninit()
{
    Scene::Uninit();
    m_vectButtons.Clear();
}

void Menu::Update(float32 deltaTime)
{
    Scene::Update(deltaTime);

    // Handle button selection
    if (GetKeyDown(Keyboard::UP_ARROW))
    {
        m_indexBtn++;
        m_selectedBtn->UnSelect();
    } if (GetKeyDown(Keyboard::DOWN_ARROW))
    {
        m_indexBtn--;
        m_selectedBtn->UnSelect();
    }
    if (m_indexBtn == m_vectButtons.Size()) { m_indexBtn = 0; }
    if (m_indexBtn == -1) {m_indexBtn = m_vectButtons.Size() - 1;}
    m_selectedBtn = m_vectButtons[m_indexBtn];

    if (m_selectedBtn != nullptr)
    {
        m_selectedBtn->Select();
        if (GetKeyDown(Keyboard::ENTER))
        {
            if (m_selectedBtn->GetName() == "play") {GameManager::Get()->SetCurrentScene<Runner3D>(); return;}
            if (m_selectedBtn->GetName() == "exit") {GameManager::Get()->CloseWindow(); return;}
        }
    }

}


#endif