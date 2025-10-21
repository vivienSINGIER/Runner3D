﻿#pragma once
#include <string>

#include "Font.h"
#include "Window.h"

#define PROVIDE_DEFAULT_FONT

class Text
{
public:
	Text() = default;
	Text(std::wstring const& text, gce::Font const* font = nullptr)
	{
#ifdef PROVIDE_DEFAULT_FONT
		if (font == nullptr)
			font = new gce::Font(L"Arial");
#endif
		m_text = text;
		m_font = font;
	}
	Text(Text const& other) = delete;
	Text(Text&& other) noexcept = delete;

	Text& operator=(Text const& other) = delete;
	Text& operator=(Text&&) = delete;

	~Text() = default;

	void SetText(std::wstring const& text) { m_text = text; }
	void SetColor(gce::Color const& color) { m_brush.SetColor(color); }
	void SetOpacity(float32 opacity) { m_brush.SetOpacity(opacity); }
	void SetPosition(gce::Vector2f32 const& pos) { m_position = pos; };
	void SetFont(const gce::Font* font) { m_font = font; }

private:
	gce::Font const* m_font{};
	gce::ColorBrush m_brush = gce::ColorBrush(gce::Color::Red, 1.0f);
	std::wstring m_text;

	gce::Vector2f32 m_position{ 0.0f, 0.0f };

	friend class Window;
};