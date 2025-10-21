#include "pch.h"
#ifndef BLOCK_CPP_DEFINED
#define BLOCK_CPP_DEFINED

#include "Block.h"

#define SPEED 2.f

Tween* transitionTween = nullptr;

Block::Block() : BoxCollider(gce::Vector3f32(), gce::Vector3f32(2.0f, 2.0f, 29.f))
{
}

void Block::Init(gce::Vector3f32 pos)
{
    Geometry* mesh = new Cube();
    mesh->SetColor(gce::Vector3f32(0.52f, 0.77f, 0.74f));
    m_mesh = mesh;
    m_transform.SetPosition(pos);
    m_transform.SetScale(gce::Vector3f32(1.0f, 1.0f, 1.f));
    m_firstPos = gce::Vector3f32(pos.x, pos.y + 1.5f, 35.f);
    m_rigidBody = false;
    m_pOwner = this;
    
    m_isTransited = false;
    m_isActive = true;
    m_transitAnim = new Chrono();
    m_transitAnim->Start();
}

void Block::Uninit()
{
    
}

void Block::Update(float32 deltatime)
{
    GameObject::Update(deltatime);
    m_transform.Translate(gce::Vector3f32(0.f, 0.f, -SPEED * deltatime));
    gce::Vector3f32 pos = m_transform.position;
    if (pos.z <= -1.25f && pos.x == 0.f && m_isTransited == false) {
        transitionTween = TweenSystem::Create( pos, gce::Vector3f32(pos.x, pos.y - SPEED, pos.z - SPEED * SPEED), Interpolation::easingIn_Quad );
        transitionTween->StartDuration(0.5f, Function::Position, m_mesh, false);
        m_isTransited = true;
        m_transitAnim->Reset();
    } if (pos.z <= -2.f && pos.x != 0.f && m_isTransited == false) {
        transitionTween = TweenSystem::Create( pos, gce::Vector3f32(pos.x, pos.y - SPEED, pos.z - SPEED * SPEED), Interpolation::easingIn_Quad );
        transitionTween->StartDuration(0.5f, Function::Position, m_mesh, false);
        m_isTransited = true;
        m_transitAnim->Reset();
    } if (m_isTransited == true && m_transitAnim->GetElapsedTime() >= 0.5f) m_isActive = false;
}

#endif
