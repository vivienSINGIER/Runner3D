#include "pch.h"
#ifndef CHARACTER_CPP_DEFINED
#define CHARACTER_CPP_DEFINED

#include "Character.h"

Character::Character() : BoxCollider(gce::Vector3f32(), gce::Vector3f32(0.5f, 0.5f, 0.5f)) {}

void Character::Init(gce::Vector3f32 pos) 
{
    Texture* text = new Texture("res/Obj/player.png");
    Geometry* cube = new Custom("res/Obj/playerFesse.obj");
    cube->SetTexture(*text);
    cube->SetColor(gce::Vector3f32(1.f, 1.f, 1.f));
    m_mesh = cube;
    m_mesh->SetTexture(*text);
    m_transform.SetScale(gce::Vector3f32(0.5f, 0.5f, 0.5f));
    m_transform.SetPosition(pos);
    m_rigidBody = true;
    m_pOwner = this;
    m_pOwnerPhysics = this;
    m_isActiveCollider = true;
    m_useGravity = false;
    m_useMaxVelocityZ = true;
    m_maxVelocities.z = 0.f;
    m_gravity = -5.0f;
}

void Character::Update(float32 deltaTime)
{
    GameObject::Update(deltaTime);
    if (m_isGrounded) { m_speed = 0.f; m_transform.rotation.x = 0; }
    centre = m_transform.position;
    m_transform.rotation.x = m_transform.rotation.x + deltaTime * m_speed ;
    m_transform.position.z = 0;
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
    if (pOther->GetOwner()->GetName() == "JumpPad")
    {
        AddForce({0.f, 4.f, 0.f}, Force::IMPULSE);
        m_isGrounded = false;
        m_speed = 200.f;
    }
    if (pOther->GetOwner()->GetName() == "Spike")
    {
        m_isActive = false;
    }
    if (pOther->GetOwner()->GetName() == "Cactus")
    {
        m_isActive = false;
    }
    if (pOther->GetOwner()->GetName() == "Bush")
    {
        m_isActive = false;
    }
    if (pOther->GetOwner()->GetName() == "Three")
    {
        m_isActive = false;
    }
}
void Character::Start()
{
    m_useGravity = true;
}

void Character::Respawn()
{
    m_transform.position = {1.f, 3.f, 0.f};
    m_velocity = {0.f, 0.f, 0.f};
    m_isGrounded = false;
    m_speed = 200.f;
}
#endif
