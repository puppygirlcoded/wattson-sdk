#include "WattsonRender.hpp"
#include "../Other/Utils.hpp"


void WattsonRender::Begin()
{
	this->DrawList = ImGui::GetBackgroundDrawList();
}

void WattsonRender::AddRectFilled(const Wattson::Vector2f& m_vecPosition, const Wattson::Vector2f& m_vecSize, Wattson::Color m_colColor, float m_flRounding)
{
	this->DrawList->AddRectFilled(ImVec2(m_vecPosition.x, m_vecPosition.y), ImVec2(m_vecPosition.x + m_vecSize.x, m_vecPosition.y + m_vecSize.y), ImColor(m_colColor.r, m_colColor.g, m_colColor.b, m_colColor.a), m_flRounding);
}

void WattsonRender::AddText(const std::string& m_sLabel, const Wattson::Vector2f& m_vecPosition, Wattson::Color m_colColor)
{
	this->DrawList->AddText(ImVec2(m_vecPosition.x, m_vecPosition.y), ImColor(m_colColor.r, m_colColor.g, m_colColor.b, m_colColor.a), m_sLabel.data());
}

void WattsonRender::AddLine(const Wattson::Vector2f& m_vecStart, const Wattson::Vector2f& m_vecEnd, Wattson::Color m_colColor, float m_flThickness)
{
	this->DrawList->AddLine({ m_vecStart.x, m_vecStart.y }, { m_vecEnd.x, m_vecEnd.y }, ImColor(m_colColor.r, m_colColor.g, m_colColor.b, m_colColor.a), m_flThickness);
}

Wattson::Vector2f WattsonRender::GetTextSize(const std::string& m_sLabel)
{
	ImVec2 m_vecTextSize = ImGui::CalcTextSize(m_sLabel.data());

	return Wattson::Vector2f(m_vecTextSize.x, m_vecTextSize.y);
}

Wattson::Vector2f WattsonRender::GetMousePos()
{
	return Wattson::Vector2f(ImGui::GetIO().MousePos.x, ImGui::GetIO().MousePos.y);
}

bool WattsonRender::IsHoveringRect(const Wattson::Vector2f& m_vecRectStart, const Wattson::Vector2f& m_vecRectMax)
{
	return ImGui::IsMouseHoveringRect({ m_vecRectStart.x, m_vecRectStart.y },
		{ m_vecRectStart.x + m_vecRectMax.x, m_vecRectStart.y + m_vecRectMax.y }, false);
}

bool WattsonRender::MouseLeftClick()
{
	return ImGui::IsMouseClicked(Mouse1);
}

bool WattsonRender::MouseLeftDown()
{
	return ImGui::IsMouseDown(Mouse1);
}

int m_iStartIdx;
Wattson::Vector2f WattsonRender::RotationCenter() {
	ImVec2 l{ FLT_MAX, FLT_MAX }, u{ -FLT_MAX, -FLT_MAX }; // bounds

	const auto& buf = ImGui::GetBackgroundDrawList()->VtxBuffer;
	for (int i = m_iStartIdx; i < buf.Size; i++)
		l = ImMin(l, buf[i].pos), u = ImMax(u, buf[i].pos);

	return Wattson::Vector2f{ (l.x + u.x) / 2, (l.y + u.y) / 2 }; // or use _ClipRectStack?
}

void WattsonRender::RotateVerticies(float m_flRotation, std::function<void()> pItemsToRotate, Wattson::Vector2f m_vecCenter) {


	m_iStartIdx = this->DrawList->VtxBuffer.Size;
	m_flRotation *= IM_PI * 2.f;

	pItemsToRotate();

	float s = ImSin(m_flRotation), c = ImCos(m_flRotation);
	if (m_vecCenter.x == -1.f && m_vecCenter.y == -1.f)
	{
		m_vecCenter = RotationCenter();
	}
	const auto m_vecRotatedCenter = ImVec2(ImRotate(m_vecCenter.ConvertToImVec2(), s, c).x - m_vecCenter.x,
		ImRotate(m_vecCenter.ConvertToImVec2(), s, c).y - m_vecCenter.y);

	m_vecCenter = Wattson::Vector2f(m_vecRotatedCenter.x, m_vecRotatedCenter.y);

	auto& buf = this->DrawList->VtxBuffer;
	for (int i = m_iStartIdx; i < buf.Size; i++)
	{
		buf[i].pos = ImVec2(ImRotate(buf[i].pos, s, c).x - m_vecCenter.x,
			ImRotate(buf[i].pos, s, c).y - m_vecCenter.y);
	}
}

void WattsonRender::PushClipRect(const Wattson::Vector2f& m_vecStart, const Wattson::Vector2f& m_vecEnd)
{
	this->DrawList->PushClipRect(m_vecStart.ConvertToImVec2(), (m_vecStart + m_vecEnd).ConvertToImVec2(), true);
}

void WattsonRender::PopClipRect()
{
	this->DrawList->PopClipRect();
}

