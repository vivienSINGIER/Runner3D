#include "pch.h"
#ifndef GRASS_CPP_DEFINED
#define GRASS_CPP_DEFINED

#include "Grass.h"

void Grass::Init()
{
    Block::Init();
    SetName("Grass");
    //m_mesh = nullptr;
    m_mesh->SetColor(gce::Vector3f32(0.51f, 0.87f, 0.52f));
}

void Grass::Start(uint8 col, float32 yPos)
{
    Block::Start(col, yPos);
    m_transform.position = gce::Vector3f32((float32)col, yPos, 20.f);
}
#endif
