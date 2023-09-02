#include <vendor/std.hpp>

bool m_bMapperHasInitialised = false;
std::map<std::string, std::string> m_mapObjects = {};

void Mapper::OnStartup()
{
	if (m_bMapperHasInitialised)
	{
		return;
	}

	//Find our window (LWJGL is the window class name).
	HWND hwnd = FindWindowA("LWJGL", NULL);

	//Getting the window title name.
	char title[256];
	GetWindowText(hwnd, title, sizeof(title));

	//Check if 1.8.9!
	bool Version1_8_9 = std::strstr(title, "1.8.9") != nullptr;
	//Check if Lunar Or Not.
	bool VersionLunar = std::strstr(title, "Lunar Client") != nullptr;

	//Set The Version.
	m_iMinecraftVersion = Version1_8_9 ? (VersionLunar ? Lunar_1_8_9 : Vanilla_1_8_9) : (VersionLunar ? Lunar_1_9_4 : Vanilla_1_9_4);

	g_Console->Print("Minecraft version: %i\n", (int)m_iMinecraftVersion);
	g_Wattson->g_Utils.m_iMinecraftVersion = m_iMinecraftVersion;

	switch (m_iMinecraftVersion)
	{
	case Vanilla_1_8_9:
	{
		m_mapObjects = {
			{"net/minecraft/client/Minecraft", "ave"},
			{"getMinecraft", "A"},
			{"rightClickDelayTimer", "ap"},

			{"net/minecraft/client/multiplayer/WorldClient", "bdb"},
			{"theWorld", "f"},
			{"playerEntities", "j"},

			{"net/minecraft/client/entity/EntityPlayerSP", "bew"},
			{"thePlayer", "h"},
			{"posX", "s"},
			{"posY", "t"},
			{"posZ", "u"},
			{"lastTickPosX", "P"},
			{"lastTickPosY", "Q"},
			{"lastTickPosZ", "R"},
			{"getName", "e_"},
			{"height", "K"},
			{"isInvisible", "ax"},
			{"motionX", "v"},
			{"motionY", "w"},
			{"motionZ", "x"},
			{"hurtResistantTime", "Z"},
			{"inventory", "bi"},

			{"net/minecraft/entity/player/InventoryPlayer", "wm"},
			{"currentItem", "c"},
			{"itemStack", "a"},
			{"getStackInSlot", "a"},

			{"net/minecraft/item/Item", "zw"},

			{"net/minecraft/item/ItemStack", "zx"},
			{"getItem", "b"},
			{"net/minecraft/item/ItemBlock", "yo"},
			{"net/minecraft/item/ItemEnderPearl", "zk"},
			{"net/minecraft/item/ItemSword", "aay"},
			{"net/minecraft/item/ItemAxe", "yl"},
			{"net/minecraft/item/ItemTool", "za"},

			{"net/minecraft/entity/EntityLivingBase", "pr"},
			{"getHealth", "bn"},
			{"getMaxHealth", "bu"},
			{"moveForward", "ba"},
			{"moveStrafing", "aZ"},

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

	case Lunar_1_8_9:
	{
		m_mapObjects = {
			{"net/minecraft/client/Minecraft", "net/minecraft/client/Minecraft"},
			{"getMinecraft", "getMinecraft"},

			{"net/minecraft/client/multiplayer/WorldClient", "net/minecraft/client/multiplayer/WorldClient"},
			{"theWorld", "theWorld"},
			{"playerEntities", "playerEntities"},

			{"net/minecraft/client/entity/EntityPlayerSP", "net/minecraft/client/entity/EntityPlayerSP"},
			{"thePlayer", "thePlayer"},
			{"posX", "posX"},
			{"posY", "posY"},
			{"posZ", "posZ"},
			{"lastTickPosX", "lastTickPosX"},
			{"lastTickPosY", "lastTickPosY"},
			{"lastTickPosZ", "lastTickPosZ"},
			{"getName", "getName"},
			{"height", "height"},
			{"isInvisible", "isInvisible"},

			{"net/minecraft/entity/EntityLivingBase", "net/minecraft/entity/EntityLivingBase"},
			{"getHealth", "getHealth"},
			{"getMaxHealth", "getMaxHealth"},

			{"net/minecraft/client/renderer/entity/RenderManager", "net/minecraft/client/renderer/entity/RenderManager"},
			{"renderManager", "renderManager"},
			{"renderPosX", "renderPosX"},
			{"renderPosY", "renderPosY"},
			{"renderPosZ", "renderPosZ"},

			{"net/minecraft/client/renderer/ActiveRenderInfo", "net/minecraft/client/renderer/ActiveRenderInfo"},
			{"PROJECTION", "PROJECTION"},
			{"MODELVIEW", "MODELVIEW"},

			{"net/minecraft/client/settings/GameSettings", "net/minecraft/client/settings/GameSettings"},
			{"gameSettings", "gameSettings"},
			{"gammaSetting", "gammaSetting"},
		};
	}
	break;

	case Vanilla_1_9_4:
	{
		m_mapObjects = {
			{"net/minecraft/client/Minecraft", "bcd"},
			{"getMinecraft", "z"},
			{"rightClickDelayTimer", "as"},

			{"net/minecraft/client/multiplayer/WorldClient", "bks"},
			{"theWorld", "f"},
			{"playerEntities", "i"},

			{"net/minecraft/client/entity/EntityPlayerSP", "bmr"},
			{"thePlayer", "h"},
			{"posX", "p"},
			{"posY", "q"},
			{"posZ", "r"},
			{"lastTickPosX", "M"},
			{"lastTickPosY", "N"},
			{"lastTickPosZ", "O"},
			{"glowing", "as"},
			{"getName", "h_"},
			{"height", "H"},
			{"isInvisible", "aN"},
			{"motionX", "s"},
			{"motionY", "t"},
			{"motionZ", "u"},
			{"hurtResistantTime", "W"},
			{"inventory", "bs"},

			{"net/minecraft/entity/player/InventoryPlayer", "zi"},
			{"currentItem", "d"},
			{"itemStack", "h"},
			{"getStackInSlot", "a"},

			{"net/minecraft/item/Item", "ado"},

			{"net/minecraft/item/ItemStack", "adq"},
			{"getItem", "b"},
			{"net/minecraft/item/ItemBlock", "acc"},
			{"net/minecraft/item/ItemEnderPearl", "adc"},
			{"net/minecraft/item/ItemSword", "aex"},
			{"net/minecraft/item/ItemTool", "acr"},
			{"net/minecraft/item/ItemAxe", "abz"},

			{"net/minecraft/entity/EntityLivingBase", "sa"},
			{"getHealth", "bR"},
			{"getMaxHealth", "bX"},
			{"moveForward", "bf"},
			{"moveStrafing", "be"},

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

		break;

	case Lunar_1_9_4:
	{
		m_mapObjects = {
			{"net/minecraft/client/Minecraft", "net/minecraft/client/Minecraft"},
			{"getMinecraft", "getMinecraft"},

			{"net/minecraft/client/multiplayer/WorldClient", "net/minecraft/client/multiplayer/WorldClient"},
			{"theWorld", "theWorld"},
			{"playerEntities", "playerEntities"},

			{"net/minecraft/client/entity/EntityPlayerSP", "net/minecraft/client/entity/EntityPlayerSP"},
			{"thePlayer", "thePlayer"},
			{"posX", "posX"},
			{"posY", "posY"},
			{"posZ", "posZ"},
			{"lastTickPosX", "lastTickPosX"},
			{"lastTickPosY", "lastTickPosY"},
			{"lastTickPosZ", "lastTickPosZ"},
			{"glowing", "glowing"},
			{"getName", "getName"},
			{"height", "height"},
			{"isInvisible", "isInvisible"},

			{"net/minecraft/entity/EntityLivingBase", "net/minecraft/entity/EntityLivingBase"},
			{"getHealth", "getHealth"},
			{"getMaxHealth", "getMaxHealth"},

			{"net/minecraft/client/renderer/entity/RenderManager", "net/minecraft/client/renderer/entity/RenderManager"},
			{"renderManager", "renderManager"},
			{"renderPosX", "renderPosX"},
			{"renderPosY", "renderPosY"},
			{"renderPosZ", "renderPosZ"},

			{"net/minecraft/client/renderer/ActiveRenderInfo", "net/minecraft/client/renderer/ActiveRenderInfo"},
			{"PROJECTION", "PROJECTION"},
			{"MODELVIEW", "MODELVIEW"},

			{"net/minecraft/client/settings/GameSettings", "net/minecraft/client/settings/GameSettings"},
			{"gameSettings", "gameSettings"},
			{"gammaSetting", "gammaSetting"},
		};
	}
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

	std::map<std::string, std::string>::iterator m_Result = m_mapObjects.find(UnobsfucatedName);

	if (m_Result == m_mapObjects.end())
	{
		g_Console->Print("Warning, couldn't find '%s' in mapper!\n", UnobsfucatedName.c_str());
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