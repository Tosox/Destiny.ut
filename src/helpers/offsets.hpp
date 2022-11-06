#pragma once

#include <cstdint>

namespace offsets
{
	namespace signatures
	{
		inline std::uintptr_t dwLocalPlayer;
		inline std::uintptr_t dwMouseEnable;
		inline std::uintptr_t dwMouseEnablePtr;
		inline std::uintptr_t dwGlowObjectManager;
		inline std::uintptr_t dwEntityList;
		inline std::uintptr_t dwForceJump;
		inline std::uintptr_t dwForceAttack;
		inline std::uintptr_t dwForceAttack2;
		inline std::uintptr_t model_ambient_min;
		inline std::uintptr_t dwGameDir;
		inline std::uintptr_t dwClientState;
		inline std::uintptr_t dwClientState_State;
		inline std::uintptr_t dwClientState_ViewAngles;
		inline std::uintptr_t dwClientState_MapDirectory;
		inline std::uintptr_t m_bDormant;
	}
	namespace netvars
	{
		inline std::uintptr_t m_bIsDefusing;
		inline std::uintptr_t m_bIsScoped;
		inline std::uintptr_t m_bSpotted;
		inline std::uintptr_t m_bSpottedByMask;
		inline std::uintptr_t m_flFlashDuration;
		inline std::uintptr_t m_iGlowIndex;
		inline std::uintptr_t m_iHealth;
		inline std::uintptr_t m_iTeamNum;
		inline std::uintptr_t m_hActiveWeapon;
		inline std::uintptr_t m_dwBoneMatrix;
		inline std::uintptr_t m_vecOrigin;
		inline std::uintptr_t m_vecVelocity;
		inline std::uintptr_t m_iItemDefinitionIndex;
		inline std::uintptr_t m_fFlags;
		inline std::uintptr_t m_iCrosshairId;
		inline std::uintptr_t m_iDefaultFOV;
		inline std::uintptr_t m_iShotsFired;
		inline std::uintptr_t m_aimPunchAngle;
		inline std::uintptr_t m_clrRender;
		inline std::uintptr_t m_vecViewOffset;
	}

	void initilize();
}