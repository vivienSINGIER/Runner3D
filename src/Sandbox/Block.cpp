#include "pch.h"
#ifndef BLOCK_CPP_DEFINED
#define BLOCK_CPP_DEFINED

#include "Block.h"

Block::Block() : BoxCollider(gce::Vector3f32(), gce::Vector3f32(1.0f, 1.0f, 1.f))
{
    Geometry* mesh = new Cube();
    mesh->SetColor(gce::Vector3f32(0.52f, 0.77f, 0.74f));
    m_mesh = mesh;
    m_transform.SetScale(gce::Vector3f32(1.0f, 1.0f, 1.f));
    m_rigidBody = false;
    m_pOwner = this;
}

void Block::Init()
{
}

void Block::Uninit()
{
    
}

void Block::Update(float32 deltatime)
{
    GameObject::Update(deltatime);
}

#endif
