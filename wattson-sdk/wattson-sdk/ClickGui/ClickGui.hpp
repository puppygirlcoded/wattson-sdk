#pragma once

class ClickGui
{
public:
	void InitClickGui();

	void OnSwapBuffers();

	void Destroy();

	void SwitchToggleState()
	{
		m_bIsOpen = !m_bIsOpen;
	}

	bool GetToggleState()
	{
		return m_bIsOpen;
	}
private:
	bool m_bIsOpen = false;
};

inline auto g_ClickGui = std::make_unique<ClickGui>();