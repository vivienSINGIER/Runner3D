#include "pch.h"
#ifndef CHARACTER_CPP_DEFINED
#define CHARACTER_CPP_DEFINED

#include "Character.h"

#include "Runner3D.h"

Character::Character() : BoxCollider(gce::Vector3f32(), gce::Vector3f32(0.5f, 0.5f, 0.5f)) {}

void Character::Init(gce::Vector3f32 pos) 
{
    Texture* text = new Texture("res/Obj/player.png");
    Geometry* cube = new Custom("res/Obj/player.obj");
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
    m_useMaxVelocityY = true;
    m_maxVelocities.y = 7.f;
    m_gravity = -6.0f;
    m_mass = 1.5f;
}

void Character::Update(float32 deltaTime)
{
    GameObject::Update(deltaTime);
    
    if (m_isReversed)
    {
        if (m_transform.rotation.z < 180.f)
            m_transform.rotation.z += 150 * deltaTime;
        if (m_transform.rotation.z > 180.f)
            m_transform.rotation.z = 180.f;
    }
    else
    {
        if (m_transform.rotation.z > 0.f)
            m_transform.rotation.z -= 150 * deltaTime;
        if (m_transform.rotation.z < 0.f)
            m_transform.rotation.z = 0.f;
    }
    
    if (m_isGrounded)
    {
        m_transform.rotation.x = 0.f;
        if (m_isReversed)
            m_transform.rotation.z = 180.0f;
        else
            m_transform.rotation.z = 0.0f;
        
        m_rotationSpeed = 0.0f;
    }
    
    centre = m_transform.position;
    m_transform.rotation.x = m_transform.rotation.x + deltaTime * m_rotationSpeed ;

    if (m_transform.position.y - 0.5f < 0.25f)
        m_isGrounded = false;
    if (m_transform.position.y + 0.5f > 5.25f)
        m_isGrounded = false;
    if (m_transform.position.y < -3.0f || m_transform.position.y > 8.0f)
    {
        m_isAlive = false;
        m_isActive = false;
    }

    if (m_firstReversedBlock == nullptr)
        return;
    if (m_firstReversedBlock->m_transform.position.z < m_transform.position.z)
    {
        Reverse();
    }
}

void Character::Move(int8 dir)
{
    if (m_isGrounded == false) return;
    
    gce::Vector3f32 pos = m_transform.position;
    if (pos.x + (float32)dir < 0.f || pos.x + (float32)dir > 2.f) return;
    m_transform.SetPosition({pos.x + (float32)dir, pos.y, pos.z});
}

void Character::Jump()
{
    float32 mult = (m_gravity > 0.0f) ? -1.f : 1.f;
    if (m_isGrounded)
    {
        AddForce({0.f, 6.f * mult, 0.f}, Force::IMPULSE);
        m_isGrounded = false;
        m_rotationSpeed = 200.f;
    }
}

void Character::Crouch()
{
    float32 mult = (m_gravity > 0.0f) ? -1.f : 1.f;
    AddForce({0.0f, -15.0f * mult, 0.0f}, PhysicsComponent::Force::FORCE);
}

void Character::OnCollisionEnter(Collider* pOther)
{
    float32 mult = (m_gravity > 0.0f) ? -1.f : 1.f;
    
    BoxCollider::OnCollisionEnter(pOther);
    if (pOther->GetOwner()->GetName() == "Grass")
    {
        if (pOther->GetOwner()->m_transform.position.y < m_transform.position.y && m_isReversed == false)
            m_isGrounded = true;
        if (pOther->GetOwner()->m_transform.position.y > m_transform.position.y && m_isReversed == true)
            m_isGrounded = true;
    }
    if (pOther->GetOwner()->GetName() == "JumpPad")
    {
        m_velocity.y = 0.0f;
        AddForce({0.f, 12.f * mult, 0.f}, Force::IMPULSE);
        m_isGrounded = false;
        m_rotationSpeed = 200.f;
    }
    if (pOther->GetOwner()->GetName() == "Spike")
    {
        m_isActive = false;
        m_isAlive = false;
    }
    if (pOther->GetOwner()->GetName() == "Cactus")
    {
        m_isActive = false;
        m_isAlive = false;
    }
    if (pOther->GetOwner()->GetName() == "Bush")
    {
        m_isActive = false;
        m_isAlive = false;
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
    m_isActive = true;
    m_isAlive = true;
}

void Character::Reverse()
{
    m_isReversed = !m_isReversed;
    m_firstReversedBlock = nullptr;
    m_gravity = -m_gravity;
    m_isGrounded = false;

    Runner3D* scene = dynamic_cast<Runner3D*>(m_pScene);
    if ( scene == nullptr )
        return;

    scene->RotateCamera(m_isReversed);
}

void Character::SetFirstReversedBlock(Block* block)
{
    if (m_firstReversedBlock != nullptr)
        return;
    m_firstReversedBlock = block;
}
#endif
