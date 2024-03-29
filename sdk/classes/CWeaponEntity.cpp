#include "CWeaponEntity.hpp"
#include "../src/helpers/offsets.hpp"
#include "../src/settings/globals.hpp"
#include "../structs/Definitions.hpp"

CWeaponEntity::CWeaponEntity()
{
	m_Address = 0;
}

CWeaponEntity::CWeaponEntity(std::uintptr_t address)
{
	m_Address = address;
}

bool CWeaponEntity::exists()
{
	return m_Address != NULL;
}

short CWeaponEntity::getItemId()
{
	return g_Memory.read<short>(m_Address + offsets::netvars::m_iItemDefinitionIndex);
}

bool CWeaponEntity::isSniper()
{
	const short id = getItemId();
	switch (id)
	{
	case weapon_awp:
	case weapon_g3sg1:
	case weapon_scar20:
	case weapon_ssg08:
		return true;
	default:
		return false;
	}
}

bool CWeaponEntity::isPistol()
{
	const short id = getItemId();
	switch (id)
	{
	case weapon_deagle:
	case weapon_elite:
	case weapon_fiveseven:
	case weapon_glock:
	case weapon_hkp2000:
	case weapon_usp_silencer:
	case weapon_cz75a:
	case weapon_revolver:
	case weapon_tec9:
	case weapon_p250:
		return true;
	default:
		return false;
	}
}

bool CWeaponEntity::isKnife()
{
	const short id = getItemId();
	switch (id)
	{
	case weapon_knifegg:
	case weapon_knife:
	case weapon_knife_t:
	case weapon_knife_ghost:
	case weapon_bayonet:
	case weapon_knife_css:
	case weapon_knife_flip:
	case weapon_knife_gut:
	case weapon_knife_karambit:
	case weapon_knife_m9_bayonet:
	case weapon_knife_tactical:
	case weapon_knife_falchion:
	case weapon_knife_survival_bowie:
	case weapon_knife_butterfly:
	case weapon_knife_push:
	case weapon_knife_cord:
	case weapon_knife_canis:
	case weapon_knife_ursus:
	case weapon_knife_gypsy_jackknife:
	case weapon_knife_outdoor:
	case weapon_knife_stiletto:
	case weapon_knife_widowmaker:
	case weapon_knife_skeleton:
		return true;
	default:
		return false;
	}
}

bool CWeaponEntity::isGun()
{
	const short id = getItemId();
	switch (id)
	{
	case weapon_deagle:
	case weapon_elite:
	case weapon_fiveseven:
	case weapon_glock:
	case weapon_ak47:
	case weapon_aug:
	case weapon_awp:
	case weapon_famas:
	case weapon_g3sg1:
	case weapon_galilar:
	case weapon_m249:
	case weapon_m4a1:
	case weapon_mac10:
	case weapon_p90:
	case weapon_mp5sd:
	case weapon_ump45:
	case weapon_xm1014:
	case weapon_bizon:
	case weapon_mag7:
	case weapon_negev:
	case weapon_sawedoff:
	case weapon_tec9:
	case weapon_hkp2000:
	case weapon_mp7:
	case weapon_mp9:
	case weapon_nova:
	case weapon_p250:
	case weapon_scar20:
	case weapon_sg556:
	case weapon_ssg08:
	case weapon_cz75a:
	case weapon_revolver:
	case weapon_usp_silencer:
	case weapon_m4a1_silencer:
		return true;
	default:
		return false;
	}
}

bool CWeaponEntity::isGrenade()
{
	const short id = getItemId();
	switch (id)
	{
	case weapon_hegrenade:
	case weapon_decoy:
	case weapon_molotov:
	case weapon_flashbang:
	case weapon_incgrenade:
	case weapon_smokegrenade:
		return true;
	default:
		return false;
	}
}
