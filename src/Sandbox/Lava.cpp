#include "pch.h"
#ifndef LAVA_CPP_DEFINED
#define LAVA_CPP_DEFINED

#include "Lava.h"

void Lava::Init()
{
    Block::Init();
    m_mesh = nullptr;
    size = {0.0f, 0.0f, 0.0f};

    m_value = 0;
}

void Lava::Start(uint8 col, float yPos)
{
    Block::Start(col, yPos);
    m_transform.position = gce::Vector3f32((float32)col, yPos, 20.f);
}
#endif
