#include "pch.h"
#ifndef RUNNER3D_CPP_DEFINED
#define RUNNER3D_CPP_DEFINED

#include "Runner3D.h"
#include "Block.h"
#include "Spike.h"

void Runner3D::Init()
{
    m_isPaused = false;
    for (int i = 0; i < 120; i++)
    {
        Block* block = CreateObject<Block>();
        block->Init(gce::Vector3f32(0.f, 1.f, 30.f));
        block->SetName("Block");
        
        m_vectBlocks.PushBack(block);
    }
    
    /*Spike* spike = CreateObject<Spike>();
    spike->Init(gce::Vector3f32(1.0f, 1.0f,3 + 29.f));
    spike->SetName("Spike");

    
    Spike* spike2 = CreateObject<Spike>();
    spike2->Init(gce::Vector3f32(-1.0f, 1.0f,3 + 2.f));
    spike2->SetName("Spike");*/
    
}

void Runner3D::Uninit()
{
    
}

void Runner3D::Update(float32 deltaTime)
{
    Scene::Update(deltaTime);
    for (int i = 0; i < 3; i++)
    {
        if (m_createBlock[i] == nullptr)
        {
            SpawnBlock(i);
            continue;
        }
        if (m_createBlock[i]->Start() == true && m_createBlock[i]->m_transform.position.z <= 30.f - 0.5f)
        {
            m_createBlock[i] = nullptr;
        }
    }
}

void Runner3D::SpawnBlock(uint8 col)
{
    for (Block* block : m_vectBlocks)
    {
        if (block->IsActive() == false)
        {
            block->m_transform.SetPosition({(float32)col, 1.f, 30.f});
            block->SetActive(true);
            m_createBlock[col] = block;
            return;
        }
        
    }
}


#endif
