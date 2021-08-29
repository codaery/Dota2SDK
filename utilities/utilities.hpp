#pragma once
#include "../includes.hpp"

namespace utilities {
	void set_ru_locale_translation();
	void attach_console();
	void send_message(const char* msg);
	void space_message();

	int is_in_console_parameter();
}