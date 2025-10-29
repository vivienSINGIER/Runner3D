#include "pch.h"
#ifndef JUMPPAD_CPP_DEFINED
#define JUMPPAD_CPP_DEFINED

#include "JumpPad.h"

void JumpPad::Init()
{
    Block::Init();
    m_name = "JumpPad";
    m_mesh->SetColor(gce::Vector3f32(0.0f, 0.87f, 0.52f));
    m_transform.SetScale({0.9f, 0.1f, 0.9f});
    size = {0.9f, 0.1f, 0.9f};

    m_isTrigger = true;
    m_value = 15;
}   

void JumpPad::Start(uint8 col, float32 yPos)
{
    Block::Start(col, yPos);
    if (yPos == 5.0f)
        yPos -= 0.5f;
    else
        yPos += 0.5f;
    
    m_transform.position = gce::Vector3f32((float32)col, yPos, 20.f);
}

#endif
