#include "pch.h"
#ifndef CACTUS_CPP_DEFINED
#define CACTUS_CPP_DEFINED

#include "Cactus.h"

void Cactus::Init(float32 speed)
{
    Block::Init(speed);
    Custom* mesh = new Custom("res/Obj/cactus.obj");
    m_mesh = mesh;
    m_mesh->SetColor({0.f, 0.8f, 0.f});
    m_transform.scale = {1.f, 1.5f, 1.f};
    m_transform.rotation = {0.f, 90.f, 0.f};
    size = {1.f, 1.5f, 1.f};
    centre = m_transform.position;
}

void Cactus::Start(uint8 col)
{
    Block::Start(col);
    m_transform.position = gce::Vector3f32((float32)col, 1.25f, 20.f);
}


#endif
