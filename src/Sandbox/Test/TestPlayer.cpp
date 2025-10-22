#include "pch.h"
#ifndef TESTPLAYER_CPP_DEFINED
#define TESTPLAYER_CPP_DEFINED

#include "TestPlayer.h"

TestPlayer::TestPlayer() : BoxCollider(gce::Vector3f32(), gce::Vector3f32(1.0f, 1.0f, 1.0f))
{
    
}

void TestPlayer::Init()
{
    Geometry* mesh = new Cube();
    mesh->SetColor(gce::Vector3f32(0.80f, 0.0f, 0.0f));
    m_mesh = mesh;
    m_transform.SetScale(gce::Vector3f32(1.0f, 1.0f, 1.f));
    m_transform.SetPosition(gce::Vector3f32(0.0f, 15.0f, 0.0f));
    m_rigidBody = false;
    m_pOwner = this;
    m_pOwnerPhysics = this;
    m_isActiveCollider = false;

    m_useGravity = true;
    
}

void TestPlayer::Uninit()
{
}

void TestPlayer::Update(float32 deltaTime)
{
    GameObject::Update(deltaTime);
}

#endif
