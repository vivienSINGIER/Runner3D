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
    m_pOwnerPhysics = this;
    m_useGravity = false;
    m_rigidBody = false;
    m_isActive = false;
    m_isActiveCollider = false;

    m_useMaxVelocityZ = true;
    m_maxVelocities.z = 5.0f;
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
        AddForce({0.0f, 0.0f, -5.0f}, PhysicsComponent::Force::IMPULSE);
}

void Block::Start(uint8 col)
{
    m_isActive = true;
}

#endif
