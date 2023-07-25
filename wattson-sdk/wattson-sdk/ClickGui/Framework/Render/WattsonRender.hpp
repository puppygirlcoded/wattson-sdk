#pragma once
#include <chrono>
#include <functional>

#include "../Math/Math.hpp"
#include "../Other/Color.hpp"

#include <imgui.h>
#include <imgui_internal.h>


class WattsonRender
{
public:
	void Begin();

	void SetActiveDrawlist(ImDrawList* m_pDrawList)
	{
		this->LastDrawList = this->DrawList;
		this->DrawList = m_pDrawList;
	}

	void ResetActiveDrawlist()
	{
		this->DrawList = this->LastDrawList;
	}

	void AddRectFilled(const Wattson::Vector2f& m_vecPosition, const Wattson::Vector2f& m_vecSize, Wattson::Color m_colColor, float m_flRounding = 0.f, int m_iDrawFlags = 0);

	void AddText(const std::string& m_sLabel, const Wattson::Vector2f& m_vecPosition, Wattson::Color m_colColor);

	void AddLine(const Wattson::Vector2f& m_vecStart, const Wattson::Vector2f& m_vecEnd, Wattson::Color m_colColor, float m_flThickness = 1.f);

	Wattson::Vector2f GetTextSize(const std::string& m_sLabel);

	Wattson::Vector2f GetMousePos();

	bool IsHoveringRect(const Wattson::Vector2f& m_vecRectStart, const Wattson::Vector2f& m_vecRectMax);

	bool MouseLeftClick();

	bool MouseLeftDown();

	Wattson::Vector2f RotationCenter();

	void RotateVerticies(float m_flRotation, std::function<void()> pItemsToRotate, Wattson::Vector2f m_vecCenter = Wattson::Vector2f(-1.f, -1.f));

	void PushClipRect(const Wattson::Vector2f& m_vecStart, const Wattson::Vector2f& m_vecEnd);

	void PopClipRect();
private:
	ImDrawList* DrawList = nullptr;
	ImDrawList* LastDrawList = nullptr;
};

inline auto g_WattsonRender = std::make_unique<WattsonRender>();
