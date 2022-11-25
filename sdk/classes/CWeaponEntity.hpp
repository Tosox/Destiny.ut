#pragma once

#include <cstdint>

class CWeaponEntity
{
public:
	CWeaponEntity();
	CWeaponEntity(std::uintptr_t address);

	short getItemId();
	bool isSniper();
	bool isPistol();
	bool isKnife();
	bool isGun();
	bool isGrenade();

	friend bool operator== (const CWeaponEntity& entity1, const CWeaponEntity& entity2) { return entity1.m_Address == entity2.m_Address; }

private:
	std::uintptr_t m_Address{};
};