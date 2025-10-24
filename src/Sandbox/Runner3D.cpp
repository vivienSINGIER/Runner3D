#include "pch.h"
#ifndef RUNNER3D_CPP_DEFINED
#define RUNNER3D_CPP_DEFINED

#include "Runner3D.h"
#include "Block.h"
#include "Grass.h"
#include "Lava.h"
#include "Spike.h"
#include "Tile.h"

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

    m_player = CreateObject<Character>();
    m_player->Init({1.f, 2.f, 0.f});
    m_player->SetName("Player");

    m_playerController = new Controller();
    m_playerController->Init(m_player);
    for (int i = 0; i < 100; i++)
    {
        Block* block = CreateObject<Grass>();
        block->Init(5.f);
        m_vectBlocks.PushBack(block);
    }

    m_firstBlock = m_vectBlocks[0];

    for (int i = 0; i < 30; i++)
    {
        Block* block = CreateObject<Lava>();
        block->Init(5.f);
        m_vectBlocks.PushBack(block);
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
    if (tile->m_currentRow > 3)
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
    
    float lastFrontZ = last->m_transform.position.z + 1.f;
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

void Runner3D::InitTiles()
{
    Tile* tile1 = new Tile();
    tile1->AddObject({ 1.0f, 0.0f, 0.0f }, Tile::ObjectType::Floor);
    
    tile1->AddObject({ 0.0f, 0.0f, 1.0f }, Tile::ObjectType::Floor);
    tile1->AddObject({ 1.0f, 0.0f, 1.0f }, Tile::ObjectType::Floor);
    tile1->AddObject({ 2.0f, 0.0f, 1.0f }, Tile::ObjectType::Floor);
    
    tile1->AddObject({ 0.0f, 0.0f, 2.0f }, Tile::ObjectType::Floor);
    tile1->AddObject({ 2.0f, 0.0f, 2.0f }, Tile::ObjectType::Floor);
    
    tile1->AddObject({ 0.0f, 0.0f, 3.0f }, Tile::ObjectType::Floor);
    tile1->AddObject({ 1.0f, 0.0f, 3.0f }, Tile::ObjectType::Floor);
    tile1->AddObject({ 2.0f, 0.0f, 3.0f }, Tile::ObjectType::Floor);
    m_vectTiles.push_back(tile1);

    Tile* tile2 = new Tile();
    tile2->AddObject({ 0.0f, 0.0f, 0.0f }, Tile::ObjectType::Floor);
    tile2->AddObject({ 0.0f, 0.0f, 1.0f }, Tile::ObjectType::Floor);
    tile2->AddObject({ 0.0f, 0.0f, 2.0f }, Tile::ObjectType::Floor);
    
    tile2->AddObject({ 0.0f, 0.0f, 3.0f }, Tile::ObjectType::Floor);
    tile2->AddObject({ 1.0f, 0.0f, 3.0f }, Tile::ObjectType::Floor);
    tile2->AddObject({ 2.0f, 0.0f, 3.0f }, Tile::ObjectType::Floor);
    m_vectTiles.push_back(tile2);

    Tile* tile3 = new Tile();
    tile3->AddObject({ 2.0f, 0.0f, 0.0f }, Tile::ObjectType::Floor);
    tile3->AddObject({ 2.0f, 0.0f, 1.0f }, Tile::ObjectType::Floor);
    tile3->AddObject({ 2.0f, 0.0f, 2.0f }, Tile::ObjectType::Floor);
   
    tile3->AddObject({ 0.0f, 0.0f, 3.0f }, Tile::ObjectType::Floor);
    tile3->AddObject({ 1.0f, 0.0f, 3.0f }, Tile::ObjectType::Floor);
    tile3->AddObject({ 2.0f, 0.0f, 3.0f }, Tile::ObjectType::Floor);
    m_vectTiles.push_back(tile3);

    Tile* tile4 = new Tile();
    tile4->m_isPlain = true;
    m_vectTiles.push_back(tile4);

    Tile* tile5 = new Tile();
    tile5->AddObject({ 0.0f, 0.0f, 0.0f }, Tile::ObjectType::Floor);
    tile5->AddObject({ 2.0f, 0.0f, 0.0f }, Tile::ObjectType::Floor);

    tile5->AddObject({ 0.0f, 0.0f, 1.0f }, Tile::ObjectType::Floor);
    tile5->AddObject({ 2.0f, 0.0f, 1.0f }, Tile::ObjectType::Floor);

    tile5->AddObject({ 0.0f, 0.0f, 2.0f }, Tile::ObjectType::Floor);
    tile5->AddObject({ 2.0f, 0.0f, 2.0f }, Tile::ObjectType::Floor);

    tile5->AddObject({ 0.0f, 0.0f, 3.0f }, Tile::ObjectType::Floor);
    tile5->AddObject({ 2.0f, 0.0f, 3.0f }, Tile::ObjectType::Floor);
    m_vectTiles.push_back(tile5);
}


#endif
