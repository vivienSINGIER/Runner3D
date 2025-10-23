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
    
    cam->SetPosition({5.0f, 5.0f, -5.0f});
    cam->SetRotation({30.0f, -45.0f, 0.0f});
    cam->SetFOV(gce::PI/3.0f);
    cam->SetFarPlane(500.0f);
    cam->SetNearPlane(0.001f);
    
    m_file = std::ifstream("../../res/JSON/tiles.json");
    if (m_file.is_open()) data = nlohmann::json::parse(m_file);
    int8 tile = 3; 
    if (data["Tiles"][tile]["full"] == true)
    {
        int16 totalBlocks = 12;
        int16 blocksPerRow = 3;
        for (int i = 0; i < totalBlocks; i++)
        {
            Block* block = CreateObject<Block>();
            block->Init();
            float32 x = (float32)(i % blocksPerRow);
            float32 z = (float32)(i / blocksPerRow);
            gce::Vector3f32 pos = gce::Vector3f32(x, 0.0f, z);
            block->m_transform.SetPosition(pos);
            block->SetName("Block");
        }
    }
    else
    {
        for (int i = 0; i < data["Tiles"][tile]["nbrBlock"]; i++)
        {
            Block* block1 = CreateObject<Block>();
            block1->Init();
            gce::Vector3f32 pos = gce::Vector3f32(data["Tiles"][tile]["blocks"][i]["placement"][0],
            data["Tiles"][tile]["blocks"][i]["placement"][1],
            data["Tiles"][tile]["blocks"][i]["placement"][2]);
            block1->m_transform.SetPosition(pos);
            block1->SetName("Block");
        }
    }
    
    m_player = CreateObject<Character>();
    m_player->Init({1.f, 3.f, 0.f});
    m_player->SetName("Player");

    m_playerController = new Controller();
    m_playerController->Init(m_player);
}

void Runner3D::Uninit()
{
    
}

void Runner3D::Update(float32 deltaTime)
{
    Scene::Update(deltaTime);
    m_playerController->HandleInput();
}


#endif