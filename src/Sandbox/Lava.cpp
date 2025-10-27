#include "pch.h"
#ifndef LAVA_CPP_DEFINED
#define LAVA_CPP_DEFINED

#include "Lava.h"

void Lava::Init(float32 speed)
{
    Block::Init(speed);
    m_mesh = nullptr;
    size = {0.0f, 0.0f, 0.0f};

    m_value = 0;
}

void Lava::Start(uint8 col)
{
    Block::Start(col);
    m_transform.position = gce::Vector3f32((float32)col, 0.f, 20.f);
}
#endif
