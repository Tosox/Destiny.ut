#pragma once

#include <Windows.h>
#include <thread>
#include <chrono>

#include "options.hpp"
#include "../helpers/Memory.hpp"
#include "../../sdk/sdk.hpp"
#include "../helpers/Console.hpp"

inline Memory g_Memory;

inline Options g_Options;

inline CClient g_Client;

inline CEngine g_Engine;

inline CBaseEntity g_LocalPlayer;