#pragma once

#include <Windows.h>
#include "Vector.hpp"

class CEngine
{
public:
	bool IsConnected();
	bool GetSendPackets();
	char* GetGameDirectory();
	char* GetMapDirectory();
	int GetModelAmbientMin();
	int GetClientState_State();
	uintptr_t Get();
	uintptr_t GetClientState();
	Vector2 GetClientState_ViewAngles();

	void Set(uintptr_t val);
	void SetModelAmbientMin(int val);
	void SetSendPackets(bool val);
	void SetClientState_ViewAngles(Vector2& val);

private:
	uintptr_t addr;
};