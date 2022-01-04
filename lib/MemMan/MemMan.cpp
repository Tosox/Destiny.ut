#include "MemMan.hpp"
#include <TlHelp32.h>
#include <iostream>
#include <iomanip>

MemMan::MemMan()
{
	handle = NULL;
}

MemMan::~MemMan()
{
	CloseHandle(handle);
}

uintptr_t MemMan::getProcess(const wchar_t* proc)
{
	HANDLE hProcessId = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	uintptr_t process = NULL;
	PROCESSENTRY32 pEntry;
	pEntry.dwSize = sizeof(pEntry);

	do
	{
		if (!_wcsicmp(pEntry.szExeFile, proc))
		{
			process = pEntry.th32ProcessID;
			CloseHandle(hProcessId);
			handle = OpenProcess(PROCESS_ALL_ACCESS, false, process);
		}

	} while (Process32Next(hProcessId, &pEntry));
	if (process != NULL) 
		return process;
	return 1;
}

uintptr_t MemMan::getModule(uintptr_t procId, const wchar_t* modName)
{
	HANDLE hModule = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, procId);
	MODULEENTRY32 mEntry{};
	mEntry.dwSize = sizeof(mEntry);

	do
	{
		if (!_wcsicmp(mEntry.szModule, modName))
		{
			CloseHandle(hModule);
			return (uintptr_t)mEntry.hModule;
		}
	} while (Module32Next(hModule, &mEntry));
	return 0;
}

uintptr_t MemMan::getAddress(uintptr_t addr, std::vector<uintptr_t> vect)
{
	for (size_t i = 0; i < vect.size(); ++i)
	{
		ReadProcessMemory(handle, (BYTE*)addr, &addr, sizeof(addr), 0);
		addr += vect[i];
	}
	return addr;
}