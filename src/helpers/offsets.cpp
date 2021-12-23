#include <Windows.h>
#include <fstream>
#include <xor/xor.hpp>
#include <json/json.hpp>
#include "offsets.hpp"
#include "../settings/globals.hpp"

template <typename T>
static void read_value(const nlohmann::json& src, T& dest)
{
	if (src.is_null()) return;

	dest = src.get<T>();
}

void offsets::InitOffsets()
{
	std::ifstream input_file{ XorStr("offsets.json") };
	if (!input_file.good())
		throw std::invalid_argument(XorStr("Invalid offsets.json file"));

	nlohmann::json json;
	input_file >> json;

	read_value(json[XorStr("signatures")][XorStr("dwLocalPlayer")], offsets::signatures::dwLocalPlayer);
	read_value(json[XorStr("signatures")][XorStr("dwMouseEnable")], offsets::signatures::dwMouseEnable);
	read_value(json[XorStr("signatures")][XorStr("dwMouseEnablePtr")], offsets::signatures::dwMouseEnablePtr);
	read_value(json[XorStr("signatures")][XorStr("dwGlowObjectManager")], offsets::signatures::dwGlowObjectManager);
	read_value(json[XorStr("signatures")][XorStr("dwEntityList")], offsets::signatures::dwEntityList);
	read_value(json[XorStr("signatures")][XorStr("dwForceJump")], offsets::signatures::dwForceJump);
	read_value(json[XorStr("signatures")][XorStr("dwForceAttack")], offsets::signatures::dwForceAttack);
	read_value(json[XorStr("signatures")][XorStr("dwForceAttack2")], offsets::signatures::dwForceAttack2);
	read_value(json[XorStr("signatures")][XorStr("dwbSendPackets")], offsets::signatures::dwbSendPackets);
	read_value(json[XorStr("signatures")][XorStr("model_ambient_min")], offsets::signatures::model_ambient_min);
	read_value(json[XorStr("signatures")][XorStr("dwClientState")], offsets::signatures::dwClientState);
	read_value(json[XorStr("signatures")][XorStr("dwClientState_State")], offsets::signatures::dwClientState_State);
	read_value(json[XorStr("signatures")][XorStr("dwClientState_ViewAngles")], offsets::signatures::dwClientState_ViewAngles);
	read_value(json[XorStr("signatures")][XorStr("m_bDormant")], offsets::signatures::m_bDormant);

	read_value(json[XorStr("netvars")][XorStr("m_bIsDefusing")], offsets::netvars::m_bIsDefusing);
	read_value(json[XorStr("netvars")][XorStr("m_bIsScoped")], offsets::netvars::m_bIsScoped);
	read_value(json[XorStr("netvars")][XorStr("m_bSpotted")], offsets::netvars::m_bSpotted);
	read_value(json[XorStr("netvars")][XorStr("m_bSpottedByMask")], offsets::netvars::m_bSpottedByMask);
	read_value(json[XorStr("netvars")][XorStr("m_flFlashDuration")], offsets::netvars::m_flFlashDuration);
	read_value(json[XorStr("netvars")][XorStr("m_iGlowIndex")], offsets::netvars::m_iGlowIndex);
	read_value(json[XorStr("netvars")][XorStr("m_iHealth")], offsets::netvars::m_iHealth);
	read_value(json[XorStr("netvars")][XorStr("m_iTeamNum")], offsets::netvars::m_iTeamNum);
	read_value(json[XorStr("netvars")][XorStr("m_hActiveWeapon")], offsets::netvars::m_hActiveWeapon);
	read_value(json[XorStr("netvars")][XorStr("m_dwBoneMatrix")], offsets::netvars::m_dwBoneMatrix);
	read_value(json[XorStr("netvars")][XorStr("m_vecOrigin")], offsets::netvars::m_vecOrigin);
	read_value(json[XorStr("netvars")][XorStr("m_vecVelocity")], offsets::netvars::m_vecVelocity);
	read_value(json[XorStr("netvars")][XorStr("m_iItemDefinitionIndex")], offsets::netvars::m_iItemDefinitionIndex);
	read_value(json[XorStr("netvars")][XorStr("m_fFlags")], offsets::netvars::m_fFlags);
	read_value(json[XorStr("netvars")][XorStr("m_iCrosshairId")], offsets::netvars::m_iCrosshairId);
	read_value(json[XorStr("netvars")][XorStr("m_iDefaultFOV")], offsets::netvars::m_iDefaultFOV);
	read_value(json[XorStr("netvars")][XorStr("m_iShotsFired")], offsets::netvars::m_iShotsFired);
	read_value(json[XorStr("netvars")][XorStr("m_aimPunchAngle")], offsets::netvars::m_aimPunchAngle);
	read_value(json[XorStr("netvars")][XorStr("m_clrRender")], offsets::netvars::m_clrRender);
	read_value(json[XorStr("netvars")][XorStr("m_vecViewOffset")], offsets::netvars::m_vecViewOffset);
}