#include "pch.h"
#ifndef BUTTON_CPP_DEFINED
#define BUTTON_CPP_DEFINED

#include "Button.h"

#include "Core/GameCamera.h"
#include "Core/GameManager.h"

void Button::Init(std::wstring const& text)
{
    Cube* btn = new Cube();
    m_mesh = btn;
    m_isActive = true;
    m_text = new Text(text);
    m_text->SetColor(gce::Color::White);
}

void Button::Update(float32 deltaTime)
{
    GameObject::Update(deltaTime);
    GameManager::Get()->GetGameCamera()->DrawText(*m_text);
}

void Button::SetTextPos(int32 x, int32 y)
{
    gce::Vector2i32 screenPos = GameManager::Get()->GetWindowSize();
    m_text->SetPosition({m_transform.position.x + screenPos.x / 2 + x, m_transform.position.y + screenPos.y / 2 + y});
}

#endif
