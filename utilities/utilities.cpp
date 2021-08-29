#include "utilities.hpp"

void utilities::set_ru_locale_translation() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
}

void utilities::attach_console() {
	AllocConsole();
	freopen("CONOUT$", "w", stdout);
}

void utilities::send_message(const char* msg) {
	std::cout << msg << std::endl;
}

void utilities::space_message() {
	std::cout << "" << std::endl;
}

int utilities::is_in_console_parameter() {
	int result;

	if (std::strstr(GetCommandLineA(), "-console"))
		result = 1;
	else
		result = 0;

	return result;
}