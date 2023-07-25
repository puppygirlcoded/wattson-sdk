#pragma once
#include <string_view>

enum EMinecraftVersions 
{
	EMinecraftVersion_1_8_9,
	EMinecraftVersion_1_9_4,
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
};

inline auto g_Mapper = std::make_unique<Mapper>();