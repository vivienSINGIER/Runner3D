#include "pch.h"
#ifndef GRASS_CPP_DEFINED
#define GRASS_CPP_DEFINED

#include "Grass.h"

void Grass::Init(float32 speed)
{
    Block::Init(speed);
    SetName("Grass");
    //m_mesh = nullptr;
    m_mesh->SetColor(gce::Vector3f32(0.51f, 0.87f, 0.52f));
}
#endif
