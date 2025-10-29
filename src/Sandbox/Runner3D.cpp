#include "pch.h"
#ifndef RUNNER3D_CPP_DEFINED
#define RUNNER3D_CPP_DEFINED

#include "Runner3D.h"

#include <LightManager.h>

#include "Block.h"
#include "Grass.h"
#include "Lava.h"
#include "JumpPad.h"
#include "Spike.h"
#include "Cactus.h"
#include "Tile.h"
#include "Bush.h"
#include "GameOver.h"
#include "Three.h"
#include "Core/GameCamera.h"
#include "Core/GameManager.h"

void Runner3D::Init()
{
    m_isPaused = false;
    GameCamera* cam = GameManager::Get()->GetGameCamera();
    cam->SetPosition({6.0f, 5.0f, -4.0f});
    cam->SetRotation({30.0f, -45.0f, 0.0f});
    cam->SetFOV(gce::PI/3.0f);
    cam->SetFarPlane(500.0f);
    cam->SetNearPlane(0.001f);

    m_isReversed = false;

    // Adds lights to light up the upside down portions
    Light light = Light::CreatePointLight(
        {0.0f, 0.0f, 0.0f},
        {1.0f, 1.0f, 1.0f, 1.0f},
        100.0f, 1.0f, 1.0f);
    light.AddLight(light);

    Light light2 = Light::CreatePointLight(
        {0.0f, 0.0f, 10.0f},
        {1.0f, 1.0f, 1.0f, 1.0f},
        100.0f, 1.0f, 1.0f);
    light.AddLight(light2);

    Light light3 = Light::CreatePointLight(
        {0.0f, 0.0f, 20.0f},
        {1.0f, 1.0f, 1.0f, 1.0f},
        100.0f, 1.0f, 1.0f);
    light.AddLight(light3);
    
    m_scoreText = CreateText(L"Score : 0");
    m_scoreText->SetPosition({20.0f, 20.0f});
    m_scoreText->SetColor(gce::Color(0, 0, 0, 255));
    
    m_player = CreateObject<Character>();
    m_player->Init({1.f, 3.f, 0.f});
    m_player->SetName("Player");
    
    m_playerController = new Controller();
    m_playerController->Init(m_player);

    // Creates all the needed blocks and objects for the game in advance
    for (int i = 0; i < 100; i++)
    {
        Block* block = CreateObject<Grass>();
        block->Init();
        m_vectBlocks.PushBack(block);
    }

    m_firstBlock = m_vectBlocks[0];

    for (int i = 0; i < 30; i++)
    {
        Block* block = CreateObject<Lava>();
        block->Init();
        m_vectBlocks.PushBack(block);
    }

    for (int i = 0; i < 5; i++)
    {
        Block* block = CreateObject<Spike>();
        block->Init();
        block->SetName("Spike");
        m_vectObject.PushBack(block);
    }

    for (int i = 0; i < 5; i++)
    {
        Block* block = CreateObject<Cactus>();
        block->Init();
        block->SetName("Cactus");
        m_vectObject.PushBack(block);
    }

    for (int i = 0; i < 5; i++)
    {
        Block* block = CreateObject<Bush>();
        block->Init();
        block->SetName("Bush");
        m_vectObject.PushBack(block);
    }

    for (int i = 0; i < 5; i++)
    {
        Block* block = CreateObject<Three>();
        block->Init();
        block->SetName("Three");
        m_vectObject.PushBack(block);
    }

    for (int i = 0; i < 5; i++)
    {
        Block* block = CreateObject<JumpPad>();
        block->Init();
        block->SetName("JumpPad");
        m_vectObject.PushBack(block);
    }
    
    InitTiles();
    m_currentTile = 3;
}

void Runner3D::Uninit()
{
    Scene::Uninit();
    delete m_playerController;
    
    m_vectBlocks.Clear();
    m_vectObject.Clear();
    m_vectTiles.Clear();
    m_score = 0;
}

void Runner3D::Update(float32 deltaTime)
{ 
    Scene::Update(deltaTime);
    m_playerController->HandleInput();

    // Text Update
    std::wstring newText = L"Score : ";
    newText.append(std::to_wstring(m_score));
    m_scoreText->SetText(newText);

    // Increases the game's speed relative to the current score
    if (m_score > m_scoreLimit)
    {
        m_scoreLimit += 500;
        m_speed *= 1.02f;
        for (Block* block : m_vectBlocks)
        {
            block->SetSpeed(m_speed);
        }
        for (Block* block : m_vectObject)
        {
            block->SetSpeed(m_speed);
        }

        float32 factor = m_speed / 5.0f;
        m_player->UpdateFromSpeed(factor);

        m_objectOdds -= 3;
        if (m_objectOdds < 8) m_objectOdds = 8;
    }

    // Handles the starting position
    if (m_firstBlock->m_transform.position.z < m_player->m_transform.position.z)
        m_player->Start();

    // Handle the spawning of the tiles line by line
    Tile* tile = m_vectTiles[m_currentTile];
    if (tile->m_currentRow > 5)
    {
        if (m_tileCount < 2)
            m_currentTile = 3;
        else
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

    // Swap scenes when the player dies
    if (m_player->IsActive() == false)
    {
        WriteScore();
        GameManager::Get()->SetCurrentScene<GameOver>();
    }
}

void Runner3D::AddScore(int32 score)
{
    if (m_player->GetIsAlive() == true)
        m_score += score;
}

void Runner3D::RotateCamera(int8 dir)
{
    GameCamera* cam = GameManager::Get()->GetGameCamera();
    
    cam->SetPosition({5.0f, 5.0f - 5.0f * (float32)dir, -5.0f});
    cam->SetRotation({30.0f - 60.0f * (float32)dir, -45.0f, 0.0f});
}

void Runner3D::HandleTileSpawn()
{
    int8 colIndex = 0;
    int8 tileIndex = 0;
    Tile* tile = m_vectTiles[m_currentTile];

    if ( tile->m_currentRow == 0 )
    {
        m_tileCount++;
        if (m_tileCount > 8)
        {
            int r = rand() % 2;
            if (r == 0)
            {
                m_tileCount = 0;
                m_isReversing = true;
                m_isReversed = !m_isReversed;

                m_currentTile = 3;
                m_vectTiles[m_currentTile]->m_currentRow = 0;
            }
        }
    }

    
    if (tile->m_isPlain)
    {
        for (int i = 0; i < 3; i++)
        {
            SpawnBlock<Grass>(i);
        }
        tile->m_currentRow++;
        return;
    }

    // Spawns a row of blocks and objects according to the tile's mapping
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

    // Checks if there is an innactive block to use for the next one
    
    Block* selected = nullptr;

    float32 yPos = (m_isReversed) ? 5.0f : 0.0f;
    
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
        selected->Start(col, yPos);
        if (col == 0) m_lastBlockInCol = selected;

        if (m_isReversing == true)
        {
            m_player->SetFirstReversedBlock(selected);
            m_isReversing = false;
        }
    }
}

void Runner3D::SpawnObj(uint8 col)
{
    // Choose for next placed object/obstacle
    
    int8 random = rand() % m_objectOdds;

    float32 yPos = (m_isReversed) ? 5.0f : 0.0f;
    
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
        case 3:
            casted = dynamic_cast<JumpPad*>(obj);
            break;
        case 4:
            casted = dynamic_cast<Three*>(obj);
            break;
        }

        if (casted == nullptr) continue;
        casted->Start(col, yPos);
        return;
    }
}

void Runner3D::InitTiles()
{
    // Reads a json file to init tile mappings
    
    int nbrTiles = 6;
    for (int8 i = 0; i < nbrTiles; i++)
    {
        Tile* tile = new Tile();
        tile->Init(i, L"../../res/JSON/tiles.json");
        m_vectTiles.PushBack(tile);
    }

    Tile* tile = new Tile();
    tile->m_isDownToUp = true;

    Tile* tile2 = new Tile();
    tile->m_isUpToDown = true;
}

void Runner3D::WriteScore()
{
    // Saves the best score inside of a json file
    
    std::ifstream in("../../res/JSON/score.json");
    if (in.is_open())
    {
        nlohmann::json personnes;
        in >> personnes;
        in.close();
    
        personnes["score"] = m_score;

        if (personnes["bestScore"] < m_score) personnes["bestScore"] = m_score;

        std::ofstream out("../../res/JSON/score.json");
        if (out.is_open())
        {
            out << personnes.dump(3);
            out.close();
        }
    }
}

#endif
