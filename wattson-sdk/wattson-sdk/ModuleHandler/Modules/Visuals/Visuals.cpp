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
		
		if (g_Java->Enviroment->IsSameObject(g_Wattson->GetLocalPlayer().GetInstance(), m_Player.GetInstance()))
		{
			continue;
		}

		m_Player.SetGlowing(g_Vars->Visuals.Glow);

		float m_flHeightFix = 3.4f;
		float m_flHeight = m_Player.GetHeight() + 0.2f;

		const Vector3f m_vecRenderPosition = g_RenderManager->RenderPosition() + Vector3f(0.f, m_flHeightFix, 0.f);
		const Vector3f m_vecPlayerOrigin = m_vecRenderPosition - m_Player.GetOrigin();
		const Vector3f m_vecPlayerHeadOrigin = m_vecRenderPosition - m_Player.GetOrigin() - Vector3f(0.f, m_flHeight, 0.f);

		Vector2f m_vecScreenOrigin;
		Vector2f m_vecScreenHeadOrigin;
		if (!g_Math->WorldToScreen(m_vecPlayerOrigin, m_vecScreenOrigin) || 
			!g_Math->WorldToScreen(m_vecPlayerHeadOrigin, m_vecScreenHeadOrigin))
		{
			continue;
		}

		const float m_flBoxHeight = m_vecScreenHeadOrigin.y - m_vecScreenOrigin.y;
		Vector4f m_vecBoundingBox = Vector4f(
			m_vecScreenHeadOrigin.x - (m_flBoxHeight / 4.f),
			m_vecScreenHeadOrigin.y - m_flBoxHeight,
			m_flBoxHeight / 2.f,
			m_flBoxHeight
		);

		if (g_Vars->Visuals.Name)
		{
			g_Render->AddText(m_Player.GetName(), Vector2f(m_vecBoundingBox.x + m_vecBoundingBox.z / 2.f, m_vecBoundingBox.y + m_vecBoundingBox.w) - Vector2f(0.f, 19.f), Wattson::Color(255, 255, 255), true);
		}

		if (g_Vars->Visuals.Box)
		{
			g_Render->AddRect({ m_vecBoundingBox.x, m_vecBoundingBox.y }, { m_vecBoundingBox.z, m_vecBoundingBox.w }, Wattson::Color(255, 255, 255), 1.f);
		}

		if (g_Vars->Visuals.Health)
		{
			const std::string m_sHealth = std::vformat("{:.0f}/{:.0f}", std::make_format_args(m_Player.GetHealth(), m_Player.GetMaxHealth()));
			const float m_flHealth = m_Player.GetHealth() / m_Player.GetMaxHealth();

			g_Render->AddText(m_sHealth, { m_vecBoundingBox.x + m_vecBoundingBox.z / 2.f, m_vecBoundingBox.y - 18.f }, Wattson::Color(255, 125, 125).Lerp(Wattson::Color(125, 255, 125), m_flHealth), true);
		}

		if (g_Vars->Visuals.Snaplines)
		{
			g_Render->AddLine(g_Wattson->g_Utils.m_vecScreenSize * 0.5f, 
				Vector2f(m_vecBoundingBox.x + m_vecBoundingBox.z / 2.f, m_vecBoundingBox.y), Wattson::Color(255, 255, 255), 1.f);
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

	// We can't set this to std::numeric_limits<float>::max() or our shadows go really fucked lol
	g_GameSettings->SetGamma(10000.f);
}