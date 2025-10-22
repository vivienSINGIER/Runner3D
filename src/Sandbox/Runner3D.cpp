#include "pch.h"
#ifndef RUNNER3D_CPP_DEFINED
#define RUNNER3D_CPP_DEFINED

#include "Runner3D.h"
#include "Block.h"
#include "Spike.h"

#define SPEED 5.f
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
    
    for (int i = 0; i < 120; i++)
    {
        Block* block = CreateObject<Block>();
        block->Init(gce::Vector3f32(0.f, 1.f, 30.f), SPEED);
        block->SetName("Block");
        
        m_vectBlocks.PushBack(block);
    }
}

void Runner3D::Uninit()
{
    
}

void Runner3D::Update(float32 deltaTime)
{
    Scene::Update(deltaTime);

    for (int i = 0; i < 3; ++i)
    {
        Block* last = m_lastBlockInCol[i];

        if (last == nullptr || !last->IsActive())
        {
            SpawnBlock(i);
            continue;
        }
        
        float lastFrontZ = last->m_transform.position.z + 1 / 2.f;
        float offset = 0.05f;
        if (lastFrontZ <= m_spawnZ + offset)
        {
            SpawnBlock(i);
        }
    }
}

void Runner3D::SpawnBlock(uint8 col)
{
    for (Block* block : m_vectBlocks)
    {
        if (!block->IsActive())
        {
            block->m_transform.SetPosition({(float)col, 1.f, m_spawnZ});
            block->SetActive(true);
            block->SetIsSpawning(true);

            m_lastBlockInCol[col] = block;
            return;
        }
    }
}


#endif
