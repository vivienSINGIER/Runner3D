#include "pch.h"
#ifndef CHARACTER_CPP_DEFINED
#define CHARACTER_CPP_DEFINED

#include "Character.h"

Character::Character() : BoxCollider(gce::Vector3f32(), gce::Vector3f32(0.5f, 0.5f, 0.5f)) {}

void Character::Init(gce::Vector3f32 pos) 
{
    Geometry* cube = new Cube();
    cube->SetColor(gce::Vector3f32(1.f, 1.f, 1.f));
    m_mesh = cube;
    m_transform.SetScale(gce::Vector3f32(0.5f, 0.5f, 0.5f));
    m_transform.SetPosition(pos);
    m_rigidBody = true;
    m_pOwner = this;
    m_pOwnerPhysics = this;
    m_isActiveCollider = true;
    m_useGravity = false;
    m_gravity = -4.981f;
}

void Character::Update(float32 deltaTime)
{
    GameObject::Update(deltaTime);
    if (m_isGrounded) { m_speed = 0.f; m_transform.rotation.x = 0; }
    centre = m_transform.position;
    m_transform.rotation.x = m_transform.rotation.x + deltaTime * m_speed ;
}

void Character::Move(int8 dir)
{
    gce::Vector3f32 pos = m_transform.position;
    if (pos.x + (float32)dir < 0.f || pos.x + (float32)dir > 2.f) return;
    m_transform.SetPosition({pos.x + (float32)dir, pos.y, pos.z});
}

void Character::Jump()
{
    if (m_isGrounded)
    {
        AddForce({0.f, 4.f, 0.f}, Force::IMPULSE);
        m_isGrounded = false;
        m_speed = 200.f;
    }
}

void Character::OnCollisionEnter(Collider* pOther)
{
    BoxCollider::OnCollisionEnter(pOther);
    if (pOther->GetOwner()->GetName() == "Block")
    {
        if (pOther->GetOwner()->m_transform.position.y < m_transform.position.y) m_isGrounded = true;
    }
}

void Character::Start()
{
    m_useGravity = true;
}

#endif
