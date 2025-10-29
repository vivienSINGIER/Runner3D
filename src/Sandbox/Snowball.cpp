#include "pch.h"
#ifndef SNOWBALL_CPP_DEFINED
#define SNOWBALL_CPP_DEFINED

#include "Snowball.h"

void Snowball::Init()
{
    Block::Init();
    IcoSphere* mesh = new IcoSphere();
    m_mesh = mesh;
    m_mesh->SetColor({1.f, 1.f, 1.f});
    m_value = 20;
}

void Snowball::Start(uint8 col, float32 yPos)
{
    Block::Start(col, yPos);
    if (yPos == 5.0f)
        yPos -= 0.90f;
    else
        yPos += 0.90f;
    
    m_transform.position = gce::Vector3f32((float32)col, yPos, 20.f);
    if (yPos == 4.1f)
        m_transform.rotation.x = 180.f;
    else
        m_transform.rotation.x = 0.f;
}


#endif