#include "includes.hpp"
#define debug_mode 1

static void start_messages(void) {
#if debug_mode 1
	utilities::attach_console();
	utilities::set_ru_locale_translation();
#else debug_mode 0
#endif
	utilities::send_message(" 'dota2 base for making hacks!");
	utilities::space_message();
	utilities::send_message(" [+] console is loaded");
}

static void end_messages(void) {
	utilities::space_message();
	utilities::send_message(" [!] press C key on your keyboard");
	if (keyboard::bind_key(key_c)) {
		utilities::send_message(" [+] keys is loaded");
	}
}

unsigned long __stdcall initialize(void* instance) {

	start_messages();
	if (utilities::is_in_console_parameter())
	{
		interfaces::initialize();
		//if (interfaces::engine->GetEngineBuildNumber() == ) { // dota version
			hooks::initialize();
		//}
		//else {
		//	utilities::space_message();
		//	utilities::send_message(" [!] dota version is outdated");
		//}
	}
	else {
		utilities::space_message();
		utilities::send_message(" [!] run dota 2 in -console parameter");
	}
	end_messages();

	return 1;
}

unsigned long __stdcall DllMain(const HMODULE ins,
	const unsigned long reason_call, int status = 1) {
	if (reason_call == 1) {
		auto thread = CreateThread(0, 0, initialize,
			ins, 0, 0);
		CloseHandle(thread);
	}

	return 1;
}