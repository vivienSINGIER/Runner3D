#include "pch.h"
#ifndef TESTSCENE_CPP_DEFINED
#define TESTSCENE_CPP_DEFINED

#include "TestScene.h"
#include "TestBlock.h"
#include "TestPlayer.h"

void TestScene::Init()
{
    m_isPaused = false;
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            TestBlock* block1 = CreateObject<TestBlock>();
            block1->Init();
            block1->m_transform.SetPosition(gce::Vector3f32(5.0f - (float32)j, 0.0f, 5.0f - (float32)i));
            block1->SetName("TestBlock");   
        }
    }

    CreateObject<TestPlayer>()->Init();
}

void TestScene::Uninit()
{
    
}

void TestScene::Update(float32 deltaTime)
{
    Scene::Update(deltaTime);
}

#endif
