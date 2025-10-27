#include "pch.h"
#ifndef SPIKE_CPP_DEFINED
#define SPIKE_CPP_DEFINED

#include "Spike.h"

void Spike::Init(float32 speed)
{
    Block::Init(speed);
    SetName("Spike");

    size = gce::Vector3f32(1.0f, 1.0f, 1.0f);
    Custom* mesh = new Custom("res/Obj/pike.obj");
    m_mesh = mesh;
    m_transform.scale = {0.75f, 0.75f, 0.75f};
    m_mesh->SetColor(gce::Vector3f32(0.1f, 0.1f, 0.1f));

    m_value = 20;
}

void Spike::Start(uint8 col)
{
    Block::Start(col);
    m_transform.position = gce::Vector3f32((float32)col, 0.75f, 20.f);
}
#endif
