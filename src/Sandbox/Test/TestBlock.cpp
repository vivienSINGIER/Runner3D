#include "pch.h"
#ifndef TESTBLOCK_CPP_DEFINED
#define TESTBLOCK_CPP_DEFINED

#include "TestBlock.h"

TestBlock::TestBlock() : BoxCollider(gce::Vector3f32(), gce::Vector3f32(1.0f, 1.0f, 1.f))
{
    
}

void TestBlock::Init()
{
    Geometry* mesh = new Cube();
    mesh->SetColor(gce::Vector3f32(0.52f, 0.77f, 0.74f));
    m_mesh = mesh;
    m_transform.SetScale(gce::Vector3f32(1.0f, 1.0f, 1.f));
    m_rigidBody = false;
    m_pOwner = this;
    m_isActiveCollider = false;

    
}

void TestBlock::Uninit()
{
    
}

void TestBlock::Update(float32 deltaTime)
{
    GameObject::Update(deltaTime);
}


#endif
