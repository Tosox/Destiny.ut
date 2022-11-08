#pragma warning(disable: 6001)

#include "Memory.hpp"

#include <TlHelp32.h>
#include <iomanip>
#include <iostream>

std::uintptr_t Memory::getProcess(const char* process)
{
	const HANDLE toolHelp = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

	PROCESSENTRY32 processEntry{};
	processEntry.dwSize = sizeof processEntry;

	while (Process32Next(toolHelp, &processEntry))
	{
		if (_stricmp(processEntry.szExeFile, process) == 0)
		{
			CloseHandle(toolHelp);
			const std::uintptr_t processId = processEntry.th32ProcessID;
			m_Handle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, processId);
			return processId;
		}
	}

	return NULL;
}

std::uintptr_t Memory::getModule(std::uintptr_t processId, const char* module)
{
	const HANDLE toolHelp = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, processId);

	MODULEENTRY32 moduleEntry{};
	moduleEntry.dwSize = sizeof moduleEntry;

	while (Module32Next(toolHelp, &moduleEntry))
	{
		if (_stricmp(moduleEntry.szModule, module) == 0)
		{
			CloseHandle(toolHelp);
			return reinterpret_cast<std::uintptr_t>(moduleEntry.hModule);
		}
	}

	return NULL;
}

std::uintptr_t Memory::getAddress(std::uintptr_t address, std::vector<std::uintptr_t> offsets)
{
	for (std::size_t i = 0; i < offsets.size(); ++i)
	{
		ReadProcessMemory(m_Handle, reinterpret_cast<BYTE*>(address), &address, sizeof address, nullptr);
		address += offsets[i];
	}

	return address;
}
