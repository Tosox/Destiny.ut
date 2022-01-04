#pragma once

#include <Windows.h>

class CWeaponEntity
{
public:
	int GetItemId();
	bool IsSniper();
	bool IsPistol();
	bool IsKnife();
	bool IsGun();
	bool IsGrenade();

private:
	uintptr_t addr;
};