#include <Windows.h>

enum keys {
	key_c = 0x43
};

namespace keyboard {
	int bind_key(int key);
}