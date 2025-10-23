#include "pch.h"
#ifndef LAVA_CPP_DEFINED
#define LAVA_CPP_DEFINED

#include "Lava.h"

void Lava::Init(gce::Vector3f32 const& pos, float32 speed)
{
    Block::Init(pos, speed);
    // m_mesh = nullptr;
    m_mesh->SetColor(gce::Vector3f32(0.9f, 0.6f, 0.3f));
}
#endif
