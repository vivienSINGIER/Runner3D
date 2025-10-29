#include "pch.h"
#ifndef BUSH_CPP_DEFINED
#define BUSH_CPP_DEFINED

#include "Bush.h"

void Bush::Init()
{
    Block::Init();
    Texture* texture = new Texture("res/Obj/bush.png");
    Custom* mesh = new Custom("res/Obj/bush.obj");
    m_mesh = mesh;
    m_mesh->SetTexture(*texture);
    m_value = 20;
}

void Bush::Start(uint8 col, float32 yPos)
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