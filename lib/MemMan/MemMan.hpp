#pragma once

#include <Windows.h>
#include <vector>

class MemMan
{
private:
	HANDLE handle;

public:
	MemMan();
	~MemMan();

	template <typename T> T read(uintptr_t addr)
	{
		T val{};
		ReadProcessMemory(handle, (LPBYTE*)addr, &val, sizeof(val), NULL);
		return val;
	}
	template <typename T> T write(uintptr_t addr, T val)
	{
		WriteProcessMemory(handle, (LPBYTE*)addr, &val, sizeof(val), NULL);
		return val;
	}

	uintptr_t getProcess(const wchar_t*);
	uintptr_t getModule(uintptr_t, const wchar_t*);
	uintptr_t getAddress(uintptr_t, std::vector<uintptr_t>);
};