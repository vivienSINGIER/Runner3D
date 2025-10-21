#include "pch.h"
#ifndef RUNNER3D_CPP_DEFINED
#define RUNNER3D_CPP_DEFINED

#include "Runner3D.h"
#include "Block.h"

void Runner3D::Init()
{
    m_isPaused = false;
    for (int i = 0; i < 30; i++)
    {
        Block* block1 = CreateObject<Block>();
        block1->Init(gce::Vector3f32(-1.0f, 0.0f, 3 + (float32)i));
        block1->
        block1->SetName("Block");

        Block* block2 = CreateObject<Block>();
        block2->Init();
        block2->m_transform.SetPosition(gce::Vector3f32(0.0f, 0.0f, 3 + (float32)i));
        block2->SetName("Block");
        
        Block* block3 = new Block();
        block3 = CreateObject<Block>();
        block3->Init();
        block3->m_transform.SetPosition(gce::Vector3f32(1.0f, 0.0f,3 + (float32)i));
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