#include "pch.h"
#ifndef BLOCK_CPP_DEFINED
#define BLOCK_CPP_DEFINED

#include "Block.h"

Block::Block() : BoxCollider(gce::Vector3f32(), gce::Vector3f32(1.0f, 1.0f, 1.f))
{
}

void Block::Init(gce::Vector3f32 const& pos, float32 speed)
{
    Geometry* mesh = new Cube();
    m_mesh = mesh;
    m_mesh->SetColor({1.f, 1.f, 1.f});
    m_transform.SetPosition(pos);
    m_transform.SetScale(gce::Vector3f32(1.0f, 1.0f, 1.f));

    m_speed = speed;
    
    m_col = (int8)pos.x;
    m_firstPos = pos;
    
    m_pOwner = this;
    
    m_rigidBody = false;
    m_isTransited = false;
    
    m_endAnim = new Chrono();
    m_startAnim = new Chrono();
}

void Block::Uninit()
{
    
}

void Block::Update(float32 deltatime)
{
    GameObject::Update(deltatime);

    if (m_isSpawning)
    {
        Start();
        return;
    }
    gce::Vector3f32 pos = m_transform.position;
    if (pos.z <= -1.f && !m_isTransited && m_isActive)
    {
        transitionTween = TweenSystem::Create(pos, 
            gce::Vector3f32(pos.x, pos.y - 1.f, pos.z - 2.f), 
            Interpolation::easingIn_linear);
        transitionTween->StartDuration(0.5f, Function::Position, &m_transform, false);
        m_isTransited = true;
        m_endAnim->Reset();
    }
    else if (m_isTransited && m_endAnim->GetElapsedTime() >= 0.5f && m_isSpawning == false)
    {
        m_isTransited = false;
        m_isActive = false;
    }
    if (!m_isTransited) m_transform.Translate(gce::Vector3f32(0.f, 0.f, -m_speed * deltatime));
}

bool Block::Start()
{
    if (m_isTransited == false)
    {
        m_isSpawning = true;
        gce::Vector3f32 pos = m_transform.position;
        transitionTween = TweenSystem::Create(
        gce::Vector3f32(pos.x, pos.y + 1.f, pos.z),
            gce::Vector3f32(pos.x, pos.y, pos.z - 2.f),
            Interpolation::easingIn_linear);
        transitionTween->StartDuration(0.5f, Function::Position, &m_transform, false);
        m_isTransited = true;
        m_startAnim->Reset();
    } 
    else if (m_startAnim->GetElapsedTime() >= 1.f && m_isTransited && m_isSpawning == true) 
    {
        m_isTransited = false;
        m_endAnim->Reset();
        m_isSpawning = false;
        return true;
    }
    return false;
}

#endif
