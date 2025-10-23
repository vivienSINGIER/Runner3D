#include "pch.h"
#ifndef SPIKE_CPP_DEFINED
#define SPIKE_CPP_DEFINED

#include "Spike.h"

void Spike::Init(float32 speed)
{
    Block::Init(speed);
    m_mesh->SetColor(gce::Vector3f32(1.f, 0.f, 0.0f));
}
#endif
