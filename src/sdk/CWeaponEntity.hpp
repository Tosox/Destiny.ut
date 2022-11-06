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

private:
	std::uintptr_t m_Address{};
};