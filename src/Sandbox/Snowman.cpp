#include "pch.h"
#ifndef SNOWMAN_CPP_DEFINED
#define SNOWMAN_CPP_DEFINED

#include "Snowman.h"

void Snowman::Init()
{
    Block::Init();
    Texture* text = new Texture("res/Obj/snowman.png");
    Custom* mesh = new Custom("res/Obj/snowman.obj");
    m_mesh = mesh;
    m_mesh->SetTexture(*text);
    m_transform.scale = {1.f, 1.5f, 1.f};
    size = {1.f, 1.5f, 1.f};
    m_transform.rotation.y = 180.0f;
    centre = m_transform.position;
}

void Snowman::Start(uint8 col, float32 yPos)
{
    Block::Start(col, yPos);
    if (yPos == 5.0f)
        yPos -= 1.25f;
    else
        yPos += 1.25f;
    
    m_transform.position = gce::Vector3f32((float32)col, yPos, 20.f);
    if (yPos == 3.75f) {
        m_transform.rotation.z = 180.0f;
    }
    else
        m_transform.rotation.z = 0.f;
}
#endif
