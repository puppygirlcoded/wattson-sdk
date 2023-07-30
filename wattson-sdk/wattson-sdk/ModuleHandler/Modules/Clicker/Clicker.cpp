#include <vendor/std.hpp>
#include <random>

__forceinline void PreciceSleep(double m_dSeconds)
{
	m_dSeconds /= 1000.;

	while (m_dSeconds > 5e-3)
	{
		auto start = std::chrono::high_resolution_clock::now();
		std::this_thread::sleep_for(std::chrono::milliseconds(1));
		auto end = std::chrono::high_resolution_clock::now();

		auto observed = (end - start).count() / 1e9;
		m_dSeconds -= observed;
	}

	auto start = std::chrono::high_resolution_clock::now();
	while ((std::chrono::high_resolution_clock::now() - start).count() / 1e9 < m_dSeconds);
}

void Clicker::OnUpdate()
{
	if (!g_Vars->Clicker.Enabled)
	{
		return;
	}

	if (!(GetAsyncKeyState(VK_LBUTTON) & 0x8000))
	{
		return;
	}

	if (GetForegroundWindow() != g_Wattson->g_Utils.m_pGameWindow || g_ClickGui->GetToggleState())
	{
		return;
	}

	auto Inventory = g_Wattson->GetLocalPlayer().GetInventory();
	if (!Inventory.GetInstance())
	{
		return;
	}

	auto ActiveSlot = Inventory.GetItemFromSlot(Inventory.GetActiveSlot());
	if (!ActiveSlot.GetInstance())
	{
		return;
	}

	if (!ActiveSlot.IsWeapon())
	{
		return;
	}

	// add a check for GuiScreen->IsInventoryOpen, g_Wattson->IsMenuItemOpen().
	auto RandomInt = [&](const int m_iMin, const int m_iMax) -> int 
	{
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<> distrib(m_iMin, m_iMax);
		return distrib(gen);
	};

	int m_iMin = g_Vars->Clicker.MinimumCPS;
	int m_iMax = g_Vars->Clicker.MaximumCPS;

	if (m_iMin > m_iMax)
	{
		m_iMin = m_iMax;
	}

	this->m_iNextCPS = RandomInt(m_iMin, m_iMax);

	std::thread([&] {
		float m_flDelay = static_cast<float>(1000 / this->m_iNextCPS) / 2.f;
		PreciceSleep((double)m_flDelay);
		g_Input->Click(EMouseInputTypes::EMouseInputTypeDown, EMouseButtons::EMouseButtonLeft);
		PreciceSleep((double)m_flDelay);
		g_Input->Click(EMouseInputTypes::EMouseInputTypeUp, EMouseButtons::EMouseButtonLeft);
		PreciceSleep((double)m_flDelay);

		std::this_thread::sleep_for(std::chrono::milliseconds(5));
	}).detach();
}