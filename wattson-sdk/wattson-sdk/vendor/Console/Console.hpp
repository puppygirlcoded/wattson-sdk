#pragma once
#include <chrono>

class Console 
{
public:
	void Setup(const std::string& m_sConsoleTitle);

	template <typename ... Args>
	void Print(char const* const m_sFormat, Args const& ... m_tArgs) {
#ifdef _DEBUG
		printf(m_sFormat, m_tArgs ...);
#endif
	}

	void Destroy();
};

inline auto g_Console = std::make_unique<Console>();