#include "pch.h"
#ifndef RUNNER3D_CPP_DEFINED
#define RUNNER3D_CPP_DEFINED

#include "Runner3D.h"
#include "Block.h"
#include "Grass.h"
#include "Lava.h"
#include "JumpPad.h"
#include "Spike.h"
#include "Cactus.h"
#include "Tile.h"

#define SPEED 5.f
#include "Bush.h"
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
    
    m_player = CreateObject<Character>();
    m_player->Init({1.f, 3.f, 0.f});
    m_player->SetName("Player");

    m_playerController = new Controller();
    m_playerController->Init(m_player);
    for (int i = 0; i < 100; i++)
    {
        Block* block = CreateObject<Grass>();
        block->Init(5.f);
        block->SetName("Block");
        m_vectBlocks.PushBack(block);
    }

    m_firstBlock = m_vectBlocks[0];

    for (int i = 0; i < 30; i++)
    {
        Block* block = CreateObject<Lava>();
        block->Init(5.f);
        block->SetName("Block");
        m_vectBlocks.PushBack(block);
    }

    for (int i = 0; i < 5; i++)
    {
        Block* block = CreateObject<Spike>();
        block->Init(5.f);
        block->SetName("Spike");
        m_vectObject.PushBack(block);
    }

    for (int i = 0; i < 5; i++)
    {
        Block* block = CreateObject<Cactus>();
        block->Init(5.f);
        block->SetName("Cactus");
        m_vectObject.PushBack(block);
    }

    for (int i = 0; i < 5; i++)
    {
        Block* block = CreateObject<Bush>();
        block->Init(5.f);
        block->SetName("Bush");
        m_vectObject.PushBack(block);
    }
    
    InitTiles();
    m_currentTile = 3;
}

void Runner3D::Uninit()
{
    
}

void Runner3D::Update(float32 deltaTime)
{ 
    Scene::Update(deltaTime);
    m_playerController->HandleInput();

    if (m_firstBlock->m_transform.position.z < m_player->m_transform.position.z)
        m_player->Start();
    
    Tile* tile = m_vectTiles[m_currentTile];
    if (tile->m_currentRow > 5)
    {
        m_currentTile = rand() % 5;
        m_vectTiles[m_currentTile]->m_currentRow = 0;
    }
    
    Block* last = m_lastBlockInCol;

    if (last == nullptr || !last->IsActive())
    {
        HandleTileSpawn();
        return;
    }
    
    float lastFrontZ = last->m_transform.position.z + .95f;
    if (lastFrontZ <= 20.f)
    {
        HandleTileSpawn();
    }

}

void Runner3D::HandleTileSpawn()
{
    int8 colIndex = 0;
    int8 tileIndex = 0;
    Tile* tile = m_vectTiles[m_currentTile];

    if (tile->m_isPlain)
    {
        for (int i = 0; i < 3; i++)
        {
            SpawnBlock<Grass>(i);
        }
        tile->m_currentRow++;
        return;
    }
    
    while (colIndex < 3)
    {
        if (tileIndex >= tile->m_floorPos.size()) break;
        
        gce::Vector3f32 pos = tile->m_floorPos[tileIndex];
        
        if (pos.z < (float32)tile->m_currentRow)
        {
            tileIndex++;
            continue;
        }

        if (pos == gce::Vector3f32((float32)colIndex, 0.0f, (float32)tile->m_currentRow) )
        {
            for (gce::Vector3f32 objPos : tile->m_objectPos)
            {
                if (pos == objPos)
                {
                    SpawnObj(colIndex);
                    break;
                }
            }
            SpawnBlock<Grass>(colIndex);
            colIndex++;
            tileIndex++;
        }
        else
        {
            SpawnBlock<Lava>(colIndex);
            colIndex++;
        }

    }

    tile->m_currentRow++;
}

template <class BlockClass>
void Runner3D::SpawnBlock(uint8 col)
{
    if (std::is_base_of<Block, BlockClass>::value == false ) return;

    Block* selected = nullptr;
    
    for (Block* block : m_vectBlocks)
    {
        if (block->IsActive()) continue;

        BlockClass* casted = dynamic_cast<BlockClass*>(block);
        if (casted == nullptr) continue;
        
        selected = block;
        break;
    }

    if (selected != nullptr)
    {
        selected->Start(col);
        if (col == 0) m_lastBlockInCol = selected;
    }
}

void Runner3D::SpawnObj(uint8 col)
{
    int8 random = rand() % 3;
    
    for (Block* obj : m_vectObject)
    {
        if (obj->IsActive()) continue;

        Block* casted = nullptr;
        switch (random)
        {
        case 0:
            casted = dynamic_cast<Cactus*>(obj);
            break;
        case 1:
            casted = dynamic_cast<Bush*>(obj);
            break;
        case 2:
            casted = dynamic_cast<Spike*>(obj);
            break;
        }

        if (casted == nullptr) continue;
        casted->Start(col);
        return;
    }
}

void Runner3D::InitTiles()
{
    int nbrTiles = 6;
    for (int8 i = 0; i < nbrTiles; i++)
    {
        Tile* tile = new Tile();
        tile->Init(i, L"../../res/JSON/tiles.json");
        m_vectTiles.push_back(tile);
    }
}


#endif
