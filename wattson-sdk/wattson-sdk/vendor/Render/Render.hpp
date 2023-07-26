#pragma once
#include <chrono>
#include <shared_mutex>
#include <any>
#include <deque>

#include <vendor/Math/Vector2f.hpp>
#include <ClickGui/Framework/Other/Color.hpp>

enum EDrawTypes
{
	EDrawTypeNone = 0,
	EDrawTypeLine,
	EDrawTypeText,
	EDrawTypeRect,
	EDrawTypeRectFill,
};

struct DrawObject
{
	DrawObject(const EDrawTypes m_eType, std::any&& m_oObject) : m_Type(m_eType), m_Object(std::move(m_oObject)) {}

	EDrawTypes m_Type = EDrawTypeNone;
	std::any m_Object = {};
};

struct LineDrawObject
{
	Vector2f m_vecStart = {};
	Vector2f m_vecEnd = {};
	Wattson::Color m_colColor = {};
	float m_flThickness = 1.f;
};

struct TextDrawObject
{
	std::string m_sLabel = {};
	Vector2f m_vecPosition = {};
	Wattson::Color m_colColor = {};
	bool m_bCenter = false;
};

struct RectDrawObject
{
	Vector2f m_vecPosition = {};
	Vector2f m_vecSize = {};
	Wattson::Color m_colColor = {};
	float m_flThickness = 1.f;
};

class Render
{
public:
	void OnSwapBuffers();

	void Swap()
	{
		std::unique_lock<std::shared_mutex> Lock(this->m_smMutex);
		this->m_dDrawData.swap(this->m_dThreadedDrawData);
	}

	void Clear()
	{
		if (!this->m_dDrawData.empty())
		{
			this->m_dDrawData.clear();
		}
	}

	void AddText(const std::string m_sLabel, const Vector2f& m_vecPosition, Wattson::Color m_colColor, bool m_bCenter = false)
	{
		this->m_dDrawData.emplace_back(EDrawTypeText, std::make_any<TextDrawObject>(m_sLabel, m_vecPosition, m_colColor, m_bCenter));
	}

	void AddLine(const Vector2f& m_vecStart, const Vector2f& m_vecEnd, Wattson::Color m_colColor, float m_flThickness)
	{
		this->m_dDrawData.emplace_back(EDrawTypeLine, std::make_any<LineDrawObject>(m_vecStart, m_vecEnd, m_colColor, m_flThickness));
	}

	void AddRect(const Vector2f& m_vecPosition, const Vector2f& m_vecSize, Wattson::Color m_colColor, float m_flThickness = 1.f)
	{
		this->m_dDrawData.emplace_back(EDrawTypeRect, std::make_any<RectDrawObject>(m_vecPosition, m_vecSize, m_colColor, m_flThickness));
	}
	
	void AddRectFilled(const Vector2f& m_vecPosition, const Vector2f& m_vecSize, Wattson::Color m_colColor)
	{
		this->m_dDrawData.emplace_back(EDrawTypeRectFill, std::make_any<RectDrawObject>(m_vecPosition, m_vecSize, m_colColor));
	}
private:
	std::deque< DrawObject > m_dDrawData = { };
	std::deque< DrawObject > m_dThreadedDrawData = { };
	std::shared_mutex m_smMutex = { };
};

inline auto g_Render = std::make_unique<Render>();