#include "pch.h"
#ifndef LAVA_CPP_DEFINED
#define LAVA_CPP_DEFINED

#include "Lava.h"

void Lava::Init(float32 speed)
{
    Block::Init(speed);
    // m_mesh = nullptr;
    m_mesh->SetColor(gce::Vector3f32(1.f, 0.f, 0.0f));
}
#endif
