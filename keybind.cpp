#include "keybind.h"

int keyboard::bind_key(int key) {
	const auto async_key = GetAsyncKeyState(key);
	int result;

	if (async_key)
		result = 1;
	else
		result = 0;

	return result;
	
}
