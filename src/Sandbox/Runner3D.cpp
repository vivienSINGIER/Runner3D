#include "pch.h"
#ifndef RUNNER3D_CPP_DEFINED
#define RUNNER3D_CPP_DEFINED

#include "Runner3D.h"
#include "Block.h"
#include "Grass.h"
#include "Lava.h"
#include "Spike.h"

#define SPEED 5.f
#include "Core/GameCamera.h"
#include "Core/GameManager.h"

void Runner3D::Init()
{
    m_isPaused = false;
    GameCamera* cam = GameManager::Get()->GetGameCamera();
    
    cam->SetPosition({5.0f, 5.0f, -5.0f});
    cam->SetRotation({30.0f, -45.0f, 0.0f});
    cam->SetFOV(gce::PI/3.0f);
    cam->SetFarPlane(500.0f);
    cam->SetNearPlane(0.001f);

    for (int h = 0; h < 2; h++)
    {
        for (int i = 0; i < 5; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                for (int k = 0; k < 3; k++)
                {
                    if (m_tiles[i][j][k] == 1)
                    {
                        Grass* block = CreateObject<Grass>();
                        block->Init(gce::Vector3f32(0.f, 1.f, 30.f), SPEED);
                        block->SetName("Block");
                        m_vectBlocks.PushBack(block);
                    }
                    else if (m_tiles[i][j][k] == 0)
                    {
                        Lava* block = CreateObject<Lava>();
                        block->Init(gce::Vector3f32(0.f, 1.f, 30.f), SPEED);
                        block->SetName("Block");
                        m_vectBlocks.PushBack(block);
                    }
                }
            }
        }
    }
    m_currentTile = rand() % 5;
}

void Runner3D::Uninit()
{
    
}

void Runner3D::Update(float32 deltaTime)
{
    Scene::Update(deltaTime);
    m_playerController->HandleInput();
    for (int i = 0; i < 3; ++i)
    {
        Block* last = m_lastBlockInCol[i];

        if (last == nullptr || !last->IsActive())
        {
            SpawnBlock(i);
            continue;
        }
        
        float lastFrontZ = last->m_transform.position.z + 1.f;
        float offset = 0.3f;
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
            if (m_tiles[m_currentTile][m_currentLine][col] == 1)
            {
                if (dynamic_cast<Grass*>(block))
                {
                    block->m_transform.SetPosition({(float)col, 1.f, m_spawnZ});
                    block->SetActive(true);
                    block->SetIsSpawning(true);
                    m_lastBlockInCol[col] = block;

                    if (m_currentLine == 3 && col == 2)
                    {
                        m_currentLine = 0;
                        m_currentTile = rand() % 5;
                        return;
                    }
                    if (col == 2)
                    {
                        m_currentLine++;
                    }
                    return;
                }
            }
            if (m_tiles[m_currentTile][m_currentLine][col] == 0)
            {
                if (dynamic_cast<Lava*>(block))
                {
                    block->m_transform.SetPosition({(float)col, 1.f, m_spawnZ});
                    block->SetActive(true);
                    block->SetIsSpawning(true);
                    m_lastBlockInCol[col] = block;

                    if (m_currentLine == 3 && col == 2)
                    {
                        m_currentLine = 0;
                        m_currentTile = rand() % 5;
                        return;
                    }
                    if (col == 2) m_currentLine++;
                    return;
                }
            }
        }
    }
}


#endif
