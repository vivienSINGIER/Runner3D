#include "pch.h"
#ifndef GAMECAMERA_CPP_DEFINED
#define GAMECAMERA_CPP_DEFINED

#include "GameCamera.h"

GameCamera::GameCamera()
{
    
}

GameCamera::~GameCamera()
{
    UnInit();
}

void GameCamera::Init(std::wstring_view title, uint32 width, uint32 height, CameraType type)
{
    m_pWindow = new Window(title, width, height);
    
    m_pCamera = new Camera(type);
    m_pCamera->SetPosition({0.0f, 20.0f, -20.0f});
    m_pCamera->SetRotation({45.0f, 0.0f, 0.0f});
    m_pCamera->SetFOV(gce::PI/4.0f);
    m_pCamera->SetFarPlane(500.0f);
    m_pCamera->SetNearPlane(0.001f);
}

void GameCamera::UnInit()
{
    delete m_pWindow;
    delete m_pCamera;
}

void GameCamera::Draw(Geometry& geometry)
{
    if (m_pWindow == nullptr) return;
    m_pWindow->Draw(geometry);
}

void GameCamera::DrawText(Text& text)
{
    if (m_pWindow == nullptr) return;
    m_pWindow->DrawText(text);
}

void GameCamera::Begin()
{
    if (m_pWindow == nullptr) return;
    if (m_pCamera == nullptr) return;
    m_pWindow->Begin(*m_pCamera);
}

void GameCamera::End()
{
    if (m_pWindow == nullptr) return;
    m_pWindow->End();
}

void GameCamera::Display()
{
    if (m_pWindow == nullptr) return;
    m_pWindow->Display();
}

bool GameCamera::IsWindowOpen()
{
    if (m_pWindow == nullptr) return false;
    return m_pWindow->IsOpen();
}

gce::Vector3f32 GameCamera::GetPosition()
{
    if (m_pCamera == nullptr) return gce::Vector3f32();
    return m_pCamera->GetPosition();
}

gce::Vector3f32 GameCamera::GetRotation()
{
    if (m_pCamera == nullptr) return gce::Vector3f32();
    return m_pCamera->GetRotation();
}

void GameCamera::SetPosition(gce::Vector3f32 const& position)
{
    if (m_pCamera == nullptr) return;
    m_pCamera->SetPosition(position);
}

void GameCamera::SetRotation(gce::Vector3f32 const& rotation)
{
    if (m_pCamera == nullptr) return;
    m_pCamera->SetRotation(rotation);
}

void GameCamera::SetFOV(float32 fov)
{
    if (m_pCamera == nullptr) return;
    m_pCamera->SetFOV(fov);
}

void GameCamera::SetNearPlane(float32 nearPlane)
{
    if (m_pCamera == nullptr) return;
    m_pCamera->SetNearPlane(nearPlane);
}

void GameCamera::SetFarPlane(float32 farPlane)
{
    if (m_pCamera == nullptr) return;
    m_pCamera->SetFarPlane(farPlane);
}

#endif
