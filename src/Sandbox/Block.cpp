 #include "pch.h"
#ifndef BLOCK_CPP_DEFINED
#define BLOCK_CPP_DEFINED

#include "Block.h"

#include "Core/GameManager.h"

 Block::Block() : BoxCollider(gce::Vector3f32(), gce::Vector3f32(1.0f, 1.0f, 1.f))
{
}

void Block::Init(float32 speed)
{
    Geometry* mesh = new Cube();
    m_mesh = mesh;
    m_mesh->SetColor({1.f, 1.f, 1.f});
    m_transform.SetPosition({0.0f, 0.0f, 0.0f});
    m_transform.SetScale(gce::Vector3f32(1.0f, 1.0f, 1.f));

    m_speed = speed;
    
    m_pOwner = this;
    m_rigidBody = false;
    m_isActive = false;
    m_isActiveCollider = false;
}

void Block::Uninit()
{
    
}

void Block::Update(float32 deltatime)
{
    GameObject::Update(deltatime);
    centre = m_transform.position;
    
    gce::Vector3f32 pos = m_transform.position;
    if (pos.z <= -3.f)
    {
        m_isActive = false;
    }
    else
        m_transform.Translate(gce::Vector3f32(0.f, 0.f, -m_speed * deltatime));
}

void Block::Start(uint8 col)
{
    m_transform.position = gce::Vector3f32((float32)col, 0.f, 20.f);
    m_isActive = true;
}

#endif
