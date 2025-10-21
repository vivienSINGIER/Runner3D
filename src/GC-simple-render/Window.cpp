﻿#include "pch.h"
#include "Window.h"

#include <RenderContext.h>

#include "Camera.h"
#include "Text.h"
#include "Geometry.h"
#include "InputSystem.h"

Window::Window(std::wstring_view const title, uint32 const width, uint32 const height, int32 const type)
{
	Create(title, width, height, type);
}

Window::~Window()
{
	m_renderer.Destroy();
}

void Window::Create(std::wstring_view const title, uint32 const width, uint32 const height, int32 const type)
{
	gce::RenderContext::Init();
	gce::RenderContext::InitUI();

	m_IsShadowMapEnabled = (type & FLAG_SHADOW_PASS_OFF) == false;

	if (type & FLAG_NO_MSAA)
		gce::RenderContext::SetMSAA(gce::MSAA_COUNT::NONE);
	else if (type & FLAG_MSAA_X4)
		gce::RenderContext::SetMSAA(gce::MSAA_COUNT::MSAA_COUNT_X4);
	else if (type & FLAG_MSAA_X8)
		gce::RenderContext::SetMSAA(gce::MSAA_COUNT::MSAA_COUNT_X8);
	else
		gce::RenderContext::SetMSAA(gce::MSAA_COUNT::MSAA_COUNT_X2);

	m_window.Create(title, width, height);
	m_width = width;
	m_height = height;
	m_renderer.Init(this);

	m_window.OnWindowResizeCallBack([&](gce::Window* w)
		{
			m_renderer.ResizeCameraProj();
		});
}

void Window::Begin(Camera& camera)
{
	m_renderer.Begin3D(camera); //Begin frame
}

void Window::Draw(Geometry& geo)
{
	m_geoToDraw.push_back(&geo); //Add to a list so we can iterate for our passes
}

void Window::DrawText(Text& text)
{
	m_textToDraw.push_back(&text);
}

void Window::End()
{
	//We must delay the draw inside the End3D function to encapsulate the multiples passes
	if (m_IsShadowMapEnabled)
		RenderShadowPass();
	RenderMainPass();

	m_renderer.End3D();
	Render2DPass();

	m_geoToDraw.clear();
	m_textToDraw.clear();
}

void Window::RenderShadowPass()
{
	m_renderer.BeginShadow();

	for (Geometry* pGeo : m_geoToDraw)
		m_renderer.DrawShadowMap(pGeo->GetRenderItem());

	m_renderer.EndShadow();
}

void Window::RenderMainPass()
{
	m_window.Begin3D();

	m_window.SetCamera(m_renderer.m_pCurrentCamera->GetGCRCamera());
	for (Geometry* pGeo : m_geoToDraw)
		m_window.Draw(pGeo->GetRenderItem());

	m_window.EndDraw();
}

void Window::Render2DPass()
{
	m_window.BeginUI();

	//Get the client size to make the rect the whole screen. 
	RECT clientRect;
	GetClientRect(m_window.GetWindowHandle(), &clientRect);

	for (Text* pText : m_textToDraw)
	{
		m_window.SetActiveBrush(pText->m_brush);
		m_window.DrawTextUI(pText->m_text, *pText->m_font, gce::RectanglePosF(pText->m_position.x, pText->m_position.y - 15, clientRect.right, clientRect.bottom));
	}

	m_window.EndUI();
}

void Window::Display()
{
	m_window.Display();
	InputSystem::HandleInputs();
	m_window.Update();
}