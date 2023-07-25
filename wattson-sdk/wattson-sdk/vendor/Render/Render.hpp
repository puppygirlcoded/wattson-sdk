#pragma once
#include <chrono>
#include <shared_mutex>
#include <any>
#include <deque>

#include <vendor/Math/Vector2f.hpp>

enum EDrawTypes
{
	EDrawTypeNone = 0,
	EDrawTypeLine,
	EDrawTypeText,
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
	float m_flThickness = 1.f;
};

struct TextDrawObject
{
	std::string m_sLabel = {};
	Vector2f m_vecPosition = {};
	bool m_bCenter = false;
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

	void AddText(const std::string m_sLabel, const Vector2f& m_vecPosition, bool m_bCenter = false)
	{
		this->m_dDrawData.emplace_back(EDrawTypeText, std::make_any<TextDrawObject>(m_sLabel, m_vecPosition, m_bCenter));
	}

	void AddLine(const Vector2f& m_vecStart, const Vector2f& m_vecEnd, float m_flThickness)
	{
		this->m_dDrawData.emplace_back(EDrawTypeLine, std::make_any<LineDrawObject>(m_vecStart, m_vecEnd, m_flThickness));
	}
private:
	std::deque< DrawObject > m_dDrawData = { };
	std::deque< DrawObject > m_dThreadedDrawData = { };
	std::shared_mutex m_smMutex = { };
};

inline auto g_Render = std::make_unique<Render>();