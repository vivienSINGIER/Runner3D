#include "pch.h"
#ifndef TOASTER_CPP_DEFINED
#define TOASTER_CPP_DEFINED

#include "Toaster.h"

void Toaster::Init()
{
    Block::Init();
    Texture* texture = new Texture("res/Obj/toaster.png");
    Custom* mesh = new Custom("res/Obj/toaster.obj");
    m_mesh = mesh;
    m_mesh->SetTexture(*texture);
    m_value = 20;
    size = {1.f, 0.5f, 1.f };
    centre = {m_transform.position.x, m_transform.position.y - 0.25f, m_transform.position.z};
}

void Toaster::Update(float32 deltaTime)
{
    Block::Update(deltaTime);
    centre = {m_transform.position.x, m_transform.position.y - 0.25f, m_transform.position.z};
}
void Toaster::Start(uint8 col, float32 yPos)
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