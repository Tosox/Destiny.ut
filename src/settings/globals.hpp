#pragma once

#include <Windows.h>
#include <MemMan/MemMan.hpp>
#include "options.hpp"
#include "../sdk/CClient.hpp"
#include "../sdk/CEngine.hpp"
#include "../sdk/CBaseEntity.hpp"

extern MemMan* g_Mem;

extern Options g_Options;

extern CClient g_Client;

extern CEngine g_Engine;

extern CBaseEntity g_LocalPlayer;