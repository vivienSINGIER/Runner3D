#include "pch.h"
#ifndef THREE_CPP_DEFINED
#define THREE_CPP_DEFINED

#include "Three.h"

void Three::Init(float32 speed)
{
    Block::Init(speed);
    Texture* text = new Texture("res/Obj/three.png");
    Custom* mesh = new Custom("res/Obj/three.obj");
    m_mesh = mesh;
    m_mesh->SetTexture(*text);
    m_transform.scale = {1.f, 1.5f, 1.f};
    size = {1.f, 1.5f, 1.f};
    centre = m_transform.position;
}

void Three::Start(uint8 col)
{
    Block::Start(col);
    m_transform.position = gce::Vector3f32((float32)col, 1.25f, 20.f);
}
#endif
