#include "CEngine.hpp"
#include "../src/helpers/offsets.hpp"
#include "../src/settings/globals.hpp"

#include <array>

bool CEngine::isConnected()
{
	return getClientState_State() == 6;
}

const char* CEngine::getGameDirectory()
{
	return g_Memory.read<std::array<char, 0x120>>(m_Address + offsets::signatures::dwGameDir).data();
}

const char* CEngine::getMapDirectory()
{
	return g_Memory.read<std::array<char, 0x120>>(getClientState() + offsets::signatures::dwClientState_MapDirectory).data();
}

int CEngine::getModelAmbientMin()
{
	return g_Memory.read<int>(m_Address + offsets::signatures::model_ambient_min);
}

int CEngine::getClientState_State()
{
	return g_Memory.read<int>(getClientState() + offsets::signatures::dwClientState_State);
}

std::uintptr_t CEngine::getClientState()
{
	return g_Memory.read<std::uintptr_t>(m_Address + offsets::signatures::dwClientState);
}

Vector2 CEngine::getClientStateViewAngles()
{
	return g_Memory.read<Vector2>(getClientState() + offsets::signatures::dwClientState_ViewAngles);
}

void CEngine::setModelAmbientMin(int value)
{
	g_Memory.write<int>(m_Address + offsets::signatures::model_ambient_min, value);
}

void CEngine::setClientStateViewAngles(Vector2& value)
{
	g_Memory.write<Vector2>(getClientState() + offsets::signatures::dwClientState_ViewAngles, value);
}
