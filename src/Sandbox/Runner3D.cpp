#include "pch.h"
#ifndef RUNNER3D_CPP_DEFINED
#define RUNNER3D_CPP_DEFINED

#include "Runner3D.h"
#include "Block.h"
#include "Core/GameCamera.h"
#include "Core/GameManager.h"

void Runner3D::Init()
{
    m_isPaused = false;
    GameCamera* cam = GameManager::Get()->GetGameCamera();
    
    cam->SetPosition({0.0f, 20.0f, -20.0f});
    cam->SetRotation({45.0f, 0.0f, 0.0f});
    cam->SetPosition({5.0f, 5.0f, -5.0f});
    cam->SetRotation({30.0f, -45.0f, 0.0f});
    cam->SetFOV(gce::PI/4.0f);
    cam->SetFarPlane(500.0f);
    cam->SetNearPlane(0.001f);
    
    for (int i = 0; i < 10; i++)
    {
        Block* block1 = CreateObject<Block>();
        block1->Init();
        block1->m_transform.SetPosition(gce::Vector3f32(0.0f, 0.0f, (float32)i));
        block1->SetName("Block");

        Block* block2 = CreateObject<Block>();
        block2->Init();
        block2->m_transform.SetPosition(gce::Vector3f32(-1.0f, 0.0f, (float32)i));
        block2->SetName("Block");
        
        Block* block3 = new Block();
        block3 = CreateObject<Block>();
        block3->Init();
        block3->m_transform.SetPosition(gce::Vector3f32(-2.0f, 0.0f,(float32)i));
        block3->SetName("Block");
    }
}

void Runner3D::Uninit()
{
    
}

void Runner3D::Update(float32 deltaTime)
{
    Scene::Update(deltaTime);
}


#endif