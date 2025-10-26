#include "pch.h"
#ifndef JUMPPAD_CPP_DEFINED
#define JUMPPAD_CPP_DEFINED

#include "JumpPad.h"

void JumpPad::Init(float32 speed)
{
    Block::Init(speed);
    m_name = "JumpPad";
    m_mesh->SetColor(gce::Vector3f32(0.0f, 0.87f, 0.52f));
    m_transform.SetScale({0.9f, 0.1f, 0.9f});
    size = {0.9f, 0.1f, 0.9f};
    m_isActive = true;
}

#endif
