#pragma once

#include "options.hpp"
#include "../helpers/Memory.hpp"
#include "../sdk/CClient.hpp"
#include "../sdk/CEngine.hpp"
#include "../sdk/CBaseEntity.hpp"
#include "../helpers/Console.hpp"

inline Memory g_Memory;

inline Options g_Options;

inline CClient g_Client;

inline CEngine g_Engine;

inline CBaseEntity g_LocalPlayer;