#include "pch.h"
#ifndef SPIKE_CPP_DEFINED
#define SPIKE_CPP_DEFINED

#include "Spike.h"

void Spike::Init(float32 speed)
{
    Block::Init(speed);
    SetName("Spike");
    m_mesh->SetColor(gce::Vector3f32(0.6f, 0.0f, 0.0f));

    size = gce::Vector3f32(1.0f, 1.0f, 1.0f);
}
#endif
