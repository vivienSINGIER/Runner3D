#include "pch.h"
#ifndef SNOW_CPP_DEFINED
#define SNOW_CPP_DEFINED

#include "Snow.h"

void Snow::Init()
{
    Block::Init();
    SetName("Snow");
    m_mesh->SetColor(gce::Vector3f32(1.0f, 1.0f, 1.0f));
}

void Snow::Start(uint8 col, float32 yPos)
{
    Block::Start(col, yPos);
    m_transform.position = gce::Vector3f32((float32)col, yPos, 20.f);
}
#endif