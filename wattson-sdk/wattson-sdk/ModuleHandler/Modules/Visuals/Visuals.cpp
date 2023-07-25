#include <vendor/std.hpp>

void Visuals::OnUpdate()
{
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