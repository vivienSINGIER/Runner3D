#include "pch.h"
#ifndef BUSH_CPP_DEFINED
#define BUSH_CPP_DEFINED

#include "Bush.h"

void Bush::Init(float32 speed)
{
    Block::Init(speed);
    Texture* texture = new Texture("res/Obj/bush.png");
    Custom* mesh = new Custom("res/Obj/bush.obj");
    m_mesh = mesh;
    m_mesh->SetTexture(*texture);
    m_value = 20;
}

void Bush::Start(uint8 col)
{
    Block::Start(col);
    m_transform.position = gce::Vector3f32((float32)col, 0.90f, 20.f);
}


#endif