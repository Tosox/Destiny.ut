#include "Console.hpp"

void console::print(std::string text, bool newLine)
{
	std::cout << text << (newLine ? "\n" : "");
}

void console::throwWarning(std::string warning)
{
	std::cout << _F_YELLOW << warning << _F_WHITE << std::endl;
}

void console::throwError(std::string error)
{
	std::cout << _F_RED << error << _F_WHITE << std::endl;
}

void console::throwErrorAndExit(std::string error)
{
	throwError(error);
	std::cin.get();
	std::exit(EXIT_FAILURE);
}
