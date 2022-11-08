#pragma once

#include <Windows.h>
#include <iostream>

inline std::ostream& _F_YELLOW(std::ostream& stream)
{
    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hStdout, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
    return stream;
}

inline std::ostream& _F_RED(std::ostream& stream)
{
    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hStdout, FOREGROUND_RED | FOREGROUND_INTENSITY);
    return stream;
}

inline std::ostream& _F_WHITE(std::ostream& stream)
{
    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hStdout, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    return stream;
}

namespace console
{
	void print(std::string text, bool newLine = true);
    void throwWarning(std::string warning);
    void throwError(std::string error);
	void throwErrorAndExit(std::string error);
}