#pragma once

#include <Windows.h>
#include <cstdint>
#include <vector>

class Memory
{
public:
	template <typename T>
	inline T read(std::uintptr_t address)
	{
		T value{};
		ReadProcessMemory(m_Handle, reinterpret_cast<BYTE**>(address), &value, sizeof value, nullptr);
		return value;
	}

	template <typename T>
	inline void write(std::uintptr_t address, T value)
	{
		WriteProcessMemory(m_Handle, reinterpret_cast<BYTE**>(address), &value, sizeof value, nullptr);
	}

	std::uintptr_t getProcess(const char* process);
	std::uintptr_t getModule(std::uintptr_t processId, const char* module);
	std::uintptr_t getAddress(std::uintptr_t address, std::vector<std::uintptr_t> offsets);

private:
	HANDLE m_Handle{};
};
