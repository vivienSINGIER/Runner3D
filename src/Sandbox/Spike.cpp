#include "pch.h"
#ifndef SPIKE_CPP_DEFINED
#define SPIKE_CPP_DEFINED

#include "Spike.h"

void Spike::Init(gce::Vector3f32 const& pos, float32 speed)
{
    Block::Init(pos, speed);
    m_mesh->SetColor(gce::Vector3f32(1.f, 0.f, 0.0f));
}
#endif
