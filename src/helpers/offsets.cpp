#include <Windows.h>
#include <fstream>
#include <xor/xor.hpp>
#include <json/json.hpp>
#include "offsets.hpp"
#include "../settings/globals.hpp"

template <typename T>
void readValue(const nlohmann::json& src, T& dest)
{
	if (!src.is_null()) 
		dest = src.get<T>();
}

void offsets::InitOffsets()
{
	// Check offsets file
	std::ifstream input_file{ XorStr("offsets.json") };
	if (!input_file.good())
		throw std::invalid_argument(XorStr("Invalid offsets.json file"));

	nlohmann::json json;
	input_file >> json;

	readValue(json[XorStr("signatures")][XorStr("dwLocalPlayer")], offsets::signatures::dwLocalPlayer);
	readValue(json[XorStr("signatures")][XorStr("dwMouseEnable")], offsets::signatures::dwMouseEnable);
	readValue(json[XorStr("signatures")][XorStr("dwMouseEnablePtr")], offsets::signatures::dwMouseEnablePtr);
	readValue(json[XorStr("signatures")][XorStr("dwGlowObjectManager")], offsets::signatures::dwGlowObjectManager);
	readValue(json[XorStr("signatures")][XorStr("dwEntityList")], offsets::signatures::dwEntityList);
	readValue(json[XorStr("signatures")][XorStr("dwForceJump")], offsets::signatures::dwForceJump);
	readValue(json[XorStr("signatures")][XorStr("dwForceAttack")], offsets::signatures::dwForceAttack);
	readValue(json[XorStr("signatures")][XorStr("dwForceAttack2")], offsets::signatures::dwForceAttack2);
	readValue(json[XorStr("signatures")][XorStr("dwbSendPackets")], offsets::signatures::dwbSendPackets);
	readValue(json[XorStr("signatures")][XorStr("model_ambient_min")], offsets::signatures::model_ambient_min);
	readValue(json[XorStr("signatures")][XorStr("dwGameDir")], offsets::signatures::dwGameDir);
	readValue(json[XorStr("signatures")][XorStr("dwClientState")], offsets::signatures::dwClientState);
	readValue(json[XorStr("signatures")][XorStr("dwClientState_State")], offsets::signatures::dwClientState_State);
	readValue(json[XorStr("signatures")][XorStr("dwClientState_ViewAngles")], offsets::signatures::dwClientState_ViewAngles);
	readValue(json[XorStr("signatures")][XorStr("dwClientState_MapDirectory")], offsets::signatures::dwClientState_MapDirectory);
	readValue(json[XorStr("signatures")][XorStr("m_bDormant")], offsets::signatures::m_bDormant);

	readValue(json[XorStr("netvars")][XorStr("m_bIsDefusing")], offsets::netvars::m_bIsDefusing);
	readValue(json[XorStr("netvars")][XorStr("m_bIsScoped")], offsets::netvars::m_bIsScoped);
	readValue(json[XorStr("netvars")][XorStr("m_bSpotted")], offsets::netvars::m_bSpotted);
	readValue(json[XorStr("netvars")][XorStr("m_bSpottedByMask")], offsets::netvars::m_bSpottedByMask);
	readValue(json[XorStr("netvars")][XorStr("m_flFlashDuration")], offsets::netvars::m_flFlashDuration);
	readValue(json[XorStr("netvars")][XorStr("m_iGlowIndex")], offsets::netvars::m_iGlowIndex);
	readValue(json[XorStr("netvars")][XorStr("m_iHealth")], offsets::netvars::m_iHealth);
	readValue(json[XorStr("netvars")][XorStr("m_iTeamNum")], offsets::netvars::m_iTeamNum);
	readValue(json[XorStr("netvars")][XorStr("m_hActiveWeapon")], offsets::netvars::m_hActiveWeapon);
	readValue(json[XorStr("netvars")][XorStr("m_dwBoneMatrix")], offsets::netvars::m_dwBoneMatrix);
	readValue(json[XorStr("netvars")][XorStr("m_vecOrigin")], offsets::netvars::m_vecOrigin);
	readValue(json[XorStr("netvars")][XorStr("m_vecVelocity")], offsets::netvars::m_vecVelocity);
	readValue(json[XorStr("netvars")][XorStr("m_iItemDefinitionIndex")], offsets::netvars::m_iItemDefinitionIndex);
	readValue(json[XorStr("netvars")][XorStr("m_fFlags")], offsets::netvars::m_fFlags);
	readValue(json[XorStr("netvars")][XorStr("m_iCrosshairId")], offsets::netvars::m_iCrosshairId);
	readValue(json[XorStr("netvars")][XorStr("m_iDefaultFOV")], offsets::netvars::m_iDefaultFOV);
	readValue(json[XorStr("netvars")][XorStr("m_iShotsFired")], offsets::netvars::m_iShotsFired);
	readValue(json[XorStr("netvars")][XorStr("m_aimPunchAngle")], offsets::netvars::m_aimPunchAngle);
	readValue(json[XorStr("netvars")][XorStr("m_clrRender")], offsets::netvars::m_clrRender);
	readValue(json[XorStr("netvars")][XorStr("m_vecViewOffset")], offsets::netvars::m_vecViewOffset);
}