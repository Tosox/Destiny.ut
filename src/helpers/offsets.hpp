#pragma once

#include <Windows.h>

namespace offsets
{
	namespace signatures
	{
		inline DWORD dwLocalPlayer;
		inline DWORD dwMouseEnable;
		inline DWORD dwMouseEnablePtr;
		inline DWORD dwGlowObjectManager;
		inline DWORD dwEntityList;
		inline DWORD dwForceJump;
		inline DWORD dwForceAttack;
		inline DWORD dwForceAttack2;
		inline DWORD dwbSendPackets;
		inline DWORD model_ambient_min;
		inline DWORD dwClientState;
		inline DWORD dwClientState_State;
		inline DWORD dwClientState_ViewAngles;
		inline DWORD m_bDormant;
	}
	namespace netvars
	{
		inline DWORD m_bIsDefusing;
		inline DWORD m_bIsScoped;
		inline DWORD m_bSpotted;
		inline DWORD m_bSpottedByMask;
		inline DWORD m_flFlashDuration;
		inline DWORD m_iGlowIndex;
		inline DWORD m_iHealth;
		inline DWORD m_iTeamNum;
		inline DWORD m_hActiveWeapon;
		inline DWORD m_dwBoneMatrix;
		inline DWORD m_vecOrigin;
		inline DWORD m_vecVelocity;
		inline DWORD m_iItemDefinitionIndex;
		inline DWORD m_fFlags;
		inline DWORD m_iCrosshairId;
		inline DWORD m_iDefaultFOV;
		inline DWORD m_iShotsFired;
		inline DWORD m_aimPunchAngle;
		inline DWORD m_clrRender;
		inline DWORD m_vecViewOffset;
	}

	void InitOffsets();
}