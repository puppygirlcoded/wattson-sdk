#include <vendor/std.hpp>

void Visuals::OnUpdate()
{
	this->Fullbright();

	const auto m_arrPlayers = g_World->GetPlayerEntites();
	if (m_arrPlayers.empty())
	{
		return;
	}

	for (Player m_Player : m_arrPlayers)
	{
		if (!m_Player.GetInstance())
		{
			continue;
		}

		// TODO: Add a check for 'isAlive' iirc its a method.
		if (m_Player.GetHealth() <= 0)
		{
			continue;
		}

		if (m_Player.GetInstance() == g_Wattson->GetLocalPlayer().GetInstance())
		{
			continue;
		}

		m_Player.SetGlowing(g_Vars->Visuals.Glow);

		float m_flHeightFix = 3.4f;

		const Vector3f m_vecRenderPosition = g_RenderManager->RenderPosition() + Vector3f(0.f, m_flHeightFix, 0.f);
		const Vector3f m_vecPlayerOrigin = m_vecRenderPosition - m_Player.GetOrigin();

		Vector2f m_vecScreenPos;
		if (!g_Math->WorldToScreen(m_vecPlayerOrigin, m_vecScreenPos))
		{
			continue;
		}

		if (g_Vars->Visuals.Name)
		{
			g_Render->AddText(m_Player.GetName(), m_vecScreenPos - Vector2f(0.f, 14.f), true);
		}

		if (g_Vars->Visuals.Snaplines)
		{
			g_Render->AddLine(g_Wattson->g_Utils.m_vecScreenSize * 0.5f, m_vecScreenPos, 1.f);
		}
	}
}

void Visuals::Fullbright()
{
	static float m_flOriginalGamma = g_GameSettings->GetGamma();
	static bool m_bDidChange = false;

	if (m_bDidChange != g_Vars->Visuals.Fullbright)
	{
		if (!g_Vars->Visuals.Fullbright)
		{
			m_flOriginalGamma = std::clamp<float>(m_flOriginalGamma, 0.f, 1.f);
			g_GameSettings->SetGamma(m_flOriginalGamma);
		}

		m_bDidChange = g_Vars->Visuals.Fullbright;
	}

	if (!g_Vars->Visuals.Fullbright)
	{
		return;
	}

	// We can't set this to std::numeric_limits<float>::max() or are shadows go really fucked lol
	g_GameSettings->SetGamma(10000.f);
}