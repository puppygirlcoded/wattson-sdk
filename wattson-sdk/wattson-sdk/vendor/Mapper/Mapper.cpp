#include <vendor/std.hpp>

bool m_bMapperHasInitialised = false;
std::map<std::string, std::string> m_mapObjects = {};

void Mapper::OnStartup()
{
	if (m_bMapperHasInitialised)
	{
		return;
	}

	// TODO: Figure out a way to find different minecraft versions and set them via here.
	EMinecraftVersions m_iMinecraftVersion = EMinecraftVersion_1_8_9;

	auto m_Minecraft189Window = FindWindowA(nullptr, "Minecraft 1.8.9");
	if (!m_Minecraft189Window)
	{
		auto m_Minecraft194Window = FindWindowA(nullptr, "Minecraft 1.9.4");
		if (!m_Minecraft194Window)
		{
			throw("Couldn't find Minecraft 1.8.9 or 1.9.4!");
			return;
		}
		else
		{
			m_iMinecraftVersion = EMinecraftVersion_1_9_4;
		}
	}
	else
	{
		m_iMinecraftVersion = EMinecraftVersion_1_8_9;
	}

	g_Console->Print("Minecraft version: %i\n", (int)m_iMinecraftVersion);
	g_Wattson->g_Utils.m_iMinecraftVersion = m_iMinecraftVersion;

	switch (m_iMinecraftVersion)
	{
	case EMinecraftVersion_1_8_9:
	{
		m_mapObjects = {
			{"net/minecraft/client/Minecraft", "ave"},
			{"getMinecraft", "A"},

			{"net/minecraft/client/multiplayer/WorldClient", "bdb"},
			{"theWorld", "f"},
			{"playerEntities", "j"},

			{"net/minecraft/client/entity/EntityPlayerSP", "bew"},
			{"thePlayer", "h"},
			{"posX", "s"},
			{"posY", "t"},
			{"posZ", "u"},
			{"getName", "e_"},

			{"net/minecraft/entity/EntityLivingBase", "pr"},
			{"getHealth", "bn"},
			{"getMaxHealth", "bu"},

			{"net/minecraft/client/renderer/entity/RenderManager", "biu"},
			{"renderManager", "aa"},
			{"renderPosX", "o"},
			{"renderPosY", "p"},
			{"renderPosZ", "q"},

			{"net/minecraft/client/renderer/ActiveRenderInfo", "auz"},
			{"PROJECTION", "c"},
			{"MODELVIEW", "b"},

			{"net/minecraft/client/settings/GameSettings", "avh"},
			{"gameSettings", "t"},
			{"gammaSetting", "aJ"},
		}; 
	}
	break;

	case EMinecraftVersion_1_9_4:
	{
		m_mapObjects = {
			{"net/minecraft/client/Minecraft", "bcd"},
			{"getMinecraft", "z"},

			{"net/minecraft/client/multiplayer/WorldClient", "bks"},
			{"theWorld", "f"},
			{"playerEntities", "i"},

			{"net/minecraft/client/entity/EntityPlayerSP", "bmr"},
			{"thePlayer", "h"},
			{"posX", "p"},
			{"posY", "q"},
			{"posZ", "r"},
			{"glowing", "as"},
			{"getName", "h_"},

			{"net/minecraft/entity/EntityLivingBase", "sa"},
			{"getHealth", "bR"},
			{"getMaxHealth", "bX"},

			{"net/minecraft/client/renderer/entity/RenderManager", "brj"},
			{"renderManager", "ac"},
			{"renderPosX", "o"},
			{"renderPosY", "p"},
			{"renderPosZ", "q"},

			{"net/minecraft/client/renderer/ActiveRenderInfo", "bby"},
			{"PROJECTION", "c"},
			{"MODELVIEW", "b"},

			{"net/minecraft/client/settings/GameSettings", "bcf"},
			{"gameSettings", "u"},
			{"gammaSetting", "ay"},
		};
	}
	break;
	}

	m_bMapperHasInitialised = true;
}

std::string Mapper::GetObsfucatedName(const std::string& UnobsfucatedName, const ENameCases& m_eNameCase)
{
	if (!m_bMapperHasInitialised || m_mapObjects.empty())
	{
		return std::string();
	}

	const auto m_Result = m_mapObjects.find(UnobsfucatedName);

	if (m_Result == m_mapObjects.end())
	{
		//g_Console->Print("Warning, couldn't find '%s' in mapper!\n", UnobsfucatedName.c_str());
		return std::string();
	}
	else
	{
		//g_Console->Print("Found '%s' from '%s'\n", m_Result->second.c_str(), UnobsfucatedName.c_str());
	}

	switch (m_eNameCase)
	{
	case ENameCaseNone:
		return m_Result->second;
		break;
	case ENameCaseL:
		return std::vformat("L{};", std::make_format_args(m_Result->second));
		break;
	case ENameCaseBracketL:
		return std::vformat("()L{};", std::make_format_args(m_Result->second));
		break;
	default:
		return m_Result->second;
	}

	// if all else fails
	return m_Result->second;
}