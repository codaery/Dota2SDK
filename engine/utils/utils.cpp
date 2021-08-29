#include "utils.h"
#include <tlhelp32.h>

auto get_module_size(const char* m)
{
	HANDLE hSnap;
	auto processID = GetCurrentProcessId();
	MODULEENTRY32 xModule;
	hSnap = CreateToolhelp32Snapshot(8, processID);
	xModule.dwSize = sizeof(MODULEENTRY32);
	if (Module32First(hSnap, &xModule))
	{
		while (Module32Next(hSnap, &xModule))
		{
			if (!strncmp((char*)xModule.szModule, m, 8))
			{
				CloseHandle(hSnap);
				return (DWORD)xModule.modBaseSize;
			}
		}
	}
	CloseHandle(hSnap);
	return (DWORD)0;
};

bool get_library_info(const char* library, uintptr_t* address, size_t* size)
{
	* address = (uintptr_t)GetModuleHandleA(library);
	*size = get_module_size(library);
	return *address && *size;
}

bool utils::world_to_screen(const Vector& spot, int& xOut, int& yOut, const matrix& vMatrix) {

    float w;
    float x, y;
    x = vMatrix[0][0] * spot[0] + vMatrix[0][1] * spot[1] + vMatrix[0][2] * spot[2] + vMatrix[0][3];
    y = vMatrix[1][0] * spot[0] + vMatrix[1][1] * spot[1] + vMatrix[1][2] * spot[2] + vMatrix[1][3];
    w = vMatrix[3][0] * spot[0] + vMatrix[3][1] * spot[1] + vMatrix[3][2] * spot[2] + vMatrix[3][3];

    bool behind;
    if (w < 0.001f)
    {
        behind = true;
    }
    else
    {
        behind = false;
        float invw = 1.0f / w;
        x *= invw;
        y *= invw;
    }

    xOut = (int)x;
    yOut = (int)y;

    return behind;
}

std::uint8_t* utils::pattern_scan(char* module_name, const char* signature) {
	static auto pattern_to_byte = [](const char* pattern) {
		auto bytes = std::vector<int>{};
		auto start = const_cast<char*>(pattern);
		auto end = const_cast<char*>(pattern) + strlen(pattern);

		for (auto current = start; current < end; ++current)
		{
			if (*current == '?')
			{
				++current;
				if (*current == '?')
					++current;
				bytes.push_back(-1);
			}
			else
			{
				bytes.push_back(strtoul(current, &current, 16));
			}
		}
		return bytes;
	};

	uintptr_t moduleptr = 0;
	size_t sizeOfImage = 0;

	get_library_info(module_name, &moduleptr, &sizeOfImage);

	auto patternBytes = pattern_to_byte(signature);
	auto scanBytes = reinterpret_cast<std::uint8_t*>(moduleptr);

	auto s = patternBytes.size();
	auto d = patternBytes.data();

	for (auto i = 0ul; i < sizeOfImage - s; ++i)
	{
		bool found = true;
		for (auto j = 0ul; j < s; ++j)
		{
			if (scanBytes[i + j] != d[j] && d[j] != -1)
			{
				found = false;
				break;
			}
		}
		if (found)
		{
			return &scanBytes[i];
		}
	}
	return nullptr;
}