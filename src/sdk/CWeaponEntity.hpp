#pragma once

#include <cstdint>

class CWeaponEntity
{
public:
	int getItemId();
	bool isSniper();
	bool isPistol();
	bool isKnife();
	bool isGun();
	bool isGrenade();

	friend bool operator! (const CWeaponEntity& entity) { return entity.m_Address == NULL; };

private:
	std::uintptr_t m_Address{};
};