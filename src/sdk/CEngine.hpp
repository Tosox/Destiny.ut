#pragma once

#include <Windows.h>
#include "Vector.hpp"

class CEngine
{
public:
	bool IsConnected();
	bool GetSendPackets();
	int GetModelAmbientMin();
	int GetClientState_State();
	uintptr_t Get();
	uintptr_t GetClientState();
	Vector2 GetClientState_ViewAngles();

	void Set(const uintptr_t addr);
	void SetModelAmbientMin(const int val);
	void SetSendPackets(const bool val);
	void SetClientState_ViewAngles(const Vector2& val);

private:
	uintptr_t addr;
};