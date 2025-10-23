#include "pch.h"
#ifndef CHARACTER_CPP_DEFINED
#define CHARACTER_CPP_DEFINED

#include "Character.h"

Character::Character() : BoxCollider(gce::Vector3f32(), gce::Vector3f32(0.75f, 0.75f, 0.75f)) {}

void Character::Init(gce::Vector3f32 pos) 
{
    Geometry* cube = new Cube();
    cube->SetColor(gce::Vector3f32(1.f, 1.f, 1.f));
    m_mesh = cube;
    
    m_transform.SetScale(gce::Vector3f32(0.75f, 0.75f, 0.75f));
    m_transform.SetPosition(pos);
    
    m_rigidBody = true;
    
    m_pOwner = this;
    m_pOwnerPhysics = this;
    m_isActiveCollider = true;
    
    m_useGravity = true;
    m_gravity = -9.81f;
}

void Character::Update(float32 deltaTime)
{
    GameObject::Update(deltaTime);
    centre = m_transform.position;
}

void Character::Move(int8 dir)
{
    gce::Vector3f32 pos = m_transform.position;
    if (pos.x + (float32)dir < 0.f || pos.x + (float32)dir > 2.f) return;
    m_transform.SetPosition({pos.x + (float32)dir, pos.y, pos.z});
}

void Character::Jump()
{
    AddForce({0.f, 2.f, 0.f}, Force::IMPULSE);
}

#endif
