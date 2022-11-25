#include <Windows.h>
#include <fstream>
#include <json/json.hpp>
#include "offsets.hpp"
#include "../settings/globals.hpp"

template <typename T>
void readValue(const nlohmann::json& src, T& dest)
{
	if (!src.is_null()) 
		dest = src.get<T>();
}

void offsets::initialize()
{
	// Check offsets file
	std::ifstream input_file{ "offsets.json" };
	if (!input_file.good())
		throw std::invalid_argument("Invalid offsets.json file");

	nlohmann::json json;
	input_file >> json;

	readValue(json["signatures"]["dwLocalPlayer"], offsets::signatures::dwLocalPlayer);
	readValue(json["signatures"]["dwMouseEnable"], offsets::signatures::dwMouseEnable);
	readValue(json["signatures"]["dwMouseEnablePtr"], offsets::signatures::dwMouseEnablePtr);
	readValue(json["signatures"]["dwGlowObjectManager"], offsets::signatures::dwGlowObjectManager);
	readValue(json["signatures"]["dwEntityList"], offsets::signatures::dwEntityList);
	readValue(json["signatures"]["dwForceJump"], offsets::signatures::dwForceJump);
	readValue(json["signatures"]["dwForceAttack"], offsets::signatures::dwForceAttack);
	readValue(json["signatures"]["dwForceAttack2"], offsets::signatures::dwForceAttack2);
	readValue(json["signatures"]["model_ambient_min"], offsets::signatures::model_ambient_min);
	readValue(json["signatures"]["dwGameDir"], offsets::signatures::dwGameDir);
	readValue(json["signatures"]["dwClientState"], offsets::signatures::dwClientState);
	readValue(json["signatures"]["dwClientState_State"], offsets::signatures::dwClientState_State);
	readValue(json["signatures"]["dwClientState_ViewAngles"], offsets::signatures::dwClientState_ViewAngles);
	readValue(json["signatures"]["dwClientState_MapDirectory"], offsets::signatures::dwClientState_MapDirectory);
	readValue(json["signatures"]["m_bDormant"], offsets::signatures::m_bDormant);
	readValue(json["signatures"]["dwViewMatrix"], offsets::signatures::dwViewMatrix);

	readValue(json["netvars"]["m_bIsDefusing"], offsets::netvars::m_bIsDefusing);
	readValue(json["netvars"]["m_bIsScoped"], offsets::netvars::m_bIsScoped);
	readValue(json["netvars"]["m_bSpotted"], offsets::netvars::m_bSpotted);
	readValue(json["netvars"]["m_bSpottedByMask"], offsets::netvars::m_bSpottedByMask);
	readValue(json["netvars"]["m_flFlashDuration"], offsets::netvars::m_flFlashDuration);
	readValue(json["netvars"]["m_iGlowIndex"], offsets::netvars::m_iGlowIndex);
	readValue(json["netvars"]["m_iHealth"], offsets::netvars::m_iHealth);
	readValue(json["netvars"]["m_iTeamNum"], offsets::netvars::m_iTeamNum);
	readValue(json["netvars"]["m_hActiveWeapon"], offsets::netvars::m_hActiveWeapon);
	readValue(json["netvars"]["m_dwBoneMatrix"], offsets::netvars::m_dwBoneMatrix);
	readValue(json["netvars"]["m_vecOrigin"], offsets::netvars::m_vecOrigin);
	readValue(json["netvars"]["m_vecVelocity"], offsets::netvars::m_vecVelocity);
	readValue(json["netvars"]["m_iItemDefinitionIndex"], offsets::netvars::m_iItemDefinitionIndex);
	readValue(json["netvars"]["m_fFlags"], offsets::netvars::m_fFlags);
	readValue(json["netvars"]["m_iCrosshairId"], offsets::netvars::m_iCrosshairId);
	readValue(json["netvars"]["m_iDefaultFOV"], offsets::netvars::m_iDefaultFOV);
	readValue(json["netvars"]["m_iShotsFired"], offsets::netvars::m_iShotsFired);
	readValue(json["netvars"]["m_aimPunchAngle"], offsets::netvars::m_aimPunchAngle);
	readValue(json["netvars"]["m_clrRender"], offsets::netvars::m_clrRender);
	readValue(json["netvars"]["m_vecViewOffset"], offsets::netvars::m_vecViewOffset);
	readValue(json["netvars"]["m_nModelIndex"], offsets::netvars::m_nModelIndex);
	readValue(json["netvars"]["m_iObserverMode"], offsets::netvars::m_iObserverMode);
}