#include "Util.h"
#include <Windows.h>

uintptr_t readPointerOffset(uintptr_t ptr, std::vector<unsigned int> offsets, bool offsetBase)
{
	uintptr_t addr = ptr;
	if (addr == 0)
		return 0;
	if (offsetBase) {
		HMODULE gamebase = GetModuleHandle(NULL);
		addr += reinterpret_cast<DWORD>(gamebase);
	}
	for (unsigned int i = 0; i < offsets.size(); ++i)
	{
		addr = *(uintptr_t*)addr;

		if (addr == 0)
			return 0;
		addr += offsets[i];
	}
	return addr;
}

std::string getLastLine(std::ifstream& in)
{
	std::string line;
	while (in >> std::ws&& std::getline(in, line)) // skip empty lines
		;

	return line;
}