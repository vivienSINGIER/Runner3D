#include "pch.h"
#ifndef MENU_CPP_DEFINED
#define MENU_CPP_DEFINED

#include "Menu.h"

#include "Block.h"
#include "Grass.h"
#include "Core/GameCamera.h"
#include "Core/GameManager.h"

void Menu::Init()
{
    m_isPaused = false;
    GameCamera* cam = new GameCamera();
    cam->Init(L"3D Runner", 1280, 720, CameraType::ORTHOGRAPHIC);
    cam->SetPosition({5.0f, 5.0f, -5.0f});
    cam->SetRotation({30.0f, -45.0f, 0.0f});
    cam->SetFOV(gce::PI/3.0f);
    cam->SetFarPlane(500.0f);
    cam->SetNearPlane(0.001f);
    GameManager::Get()->SetGameCamera(cam);

    Block* block = CreateObject<Grass>();
    block->Init(5.f);
    block->m_transform.position = {0.0f, 0.0f, 0.0f};
}

void Menu::Uninit()
{
}

void Menu::Update(float32 deltaTime)
{
    Scene::Update(deltaTime);
    
}


#endif