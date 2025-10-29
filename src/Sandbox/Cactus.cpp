#include "pch.h"
#ifndef CACTUS_CPP_DEFINED
#define CACTUS_CPP_DEFINED

#include "Cactus.h"

void Cactus::Init()
{
    Block::Init();
    Custom* mesh = new Custom("res/Obj/cactus.obj");
    m_mesh = mesh;
    m_mesh->SetColor({0.f, 0.8f, 0.f});
    m_transform.scale = {1.f, 1.5f, 1.f};
    m_transform.rotation = {0.f, 90.f, 0.f};
    size = {1.f, 1.5f, 1.f};
    centre = m_transform.position;
    m_value = 25;
}

void Cactus::Start(uint8 col, float32 yPos)
{
    Block::Start(col, yPos);
    if (yPos == 5.0f)
        yPos -= 1.25f;
    else
        yPos += 1.25f;
    
    m_transform.position = gce::Vector3f32((float32)col, yPos, 20.f);
    if (yPos == 3.75f)
        m_transform.rotation.x = 180.0f;
    else
        m_transform.rotation.x = 0.f;
}


#endif
