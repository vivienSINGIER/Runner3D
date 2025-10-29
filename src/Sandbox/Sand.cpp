#include "pch.h"
#ifndef SAND_CPP_DEFINED
#define SAND_CPP_DEFINED

#include "Sand.h"

void Sand::Init()
{
    Block::Init();
    SetName("Sand");
    m_mesh->SetColor(gce::Vector3f32(0.9f, 0.83f, 0.52f));
}

void Sand::Start(uint8 col, float32 yPos)
{
    Block::Start(col, yPos);
    m_transform.position = gce::Vector3f32((float32)col, yPos, 20.f);
}
#endif