#pragma once
#include <string_view>

enum EMinecraftVersions 
{
	Vanilla_1_8_9,
	Lunar_1_8_9,
	Vanilla_1_9_4,
	Lunar_1_9_4,
};

enum ENameCases
{
	ENameCaseNone = 0,
	ENameCaseL,
	ENameCaseBracketL
};
class Mapper
{
public:
	void OnStartup();
	std::string GetObsfucatedName(const std::string& UnobsfucatedName, const ENameCases& m_eNameCase = ENameCaseNone);

	EMinecraftVersions m_iMinecraftVersion;
};

inline auto g_Mapper = std::make_unique<Mapper>();