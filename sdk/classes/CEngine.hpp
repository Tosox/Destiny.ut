#pragma once

#include <cstdint>
#include "../structs/Vector2.hpp"

class CEngine
{
public:
	bool isConnected();
	const char* getGameDirectory();
	const char* getMapDirectory();
	int getModelAmbientMin();
	int getClientState_State();
	std::uintptr_t getClientState();
	Vector2 getClientStateViewAngles();

	void setModelAmbientMin(int value);
	void setClientStateViewAngles(Vector2& value);

	inline CEngine& operator= (const std::uintptr_t& address) { m_Address = address; return *this; }
	friend std::uintptr_t operator+ (const CEngine& entity, const std::uintptr_t& offset) { return entity.m_Address + offset; }

private:
	std::uintptr_t m_Address{};
};