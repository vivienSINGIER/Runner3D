#include "pch.h"
#ifndef LAVA_CPP_DEFINED
#define LAVA_CPP_DEFINED

#include "Lava.h"

void Lava::Init(float32 speed)
{
    Block::Init(speed);
    m_mesh = nullptr;
    size = {0.0f, 0.0f, 0.0f};
}
#endif
