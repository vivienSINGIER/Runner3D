#include "pch.h"
#ifndef GAMEOBJECT_CPP_DEFINED
#define GAMEOBJECT_CPP_DEFINED

#include "GameObject.h"

#include "GameCamera.h"
#include "GC-simple-render/Window.h"

GameObject::GameObject() : m_name("") {}

GameObject::~GameObject()
{
    
}

void GameObject::Update(float32 deltatime)
{
    // Update the mesh's transform from the object's transform
    if (m_mesh == nullptr) return;
    m_mesh->SetPosition(m_transform.position);
    m_mesh->SetScale(m_transform.scale);
    m_mesh->SetRotation(m_transform.rotation);
}

void GameObject::Render(GameCamera* pGameCamera)
{
    if (m_mesh == nullptr) return;
    pGameCamera->Draw(*m_mesh);
}

void GameObject::ToDestroy()
{
    toDestroy = true;
}

void GameObject::SetName(std::string newName)
{
    m_name = newName;
}

#endif
