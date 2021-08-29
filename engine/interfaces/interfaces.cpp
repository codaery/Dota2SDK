#include "interfaces.hpp"

IEngineClient* interfaces::engine = 0;
IInputSystem* interfaces::input_system = 0;
IVPanel* interfaces::panel = 0;
CParticleSystemMgr* interfaces::particle_mgr = 0;
CGameEntitySystem* interfaces::entity = 0;
IDirect3DDevice9* interfaces::directx = 0;

inline void* get_interface(const char* library_name, const char* interface_name)
{
	const auto module_handle = GetModuleHandle(library_name);
	const auto adress = GetProcAddress(module_handle, "CreateInterface");
	CreateInterfaceFn create_interface = reinterpret_cast<CreateInterfaceFn>(adress);

	auto return_code = 0;
	auto* module_name = create_interface(interface_name, &return_code);

	return module_name;
}

void interfaces::initialize() {

	engine = static_cast<IEngineClient*>(get_interface("engine.dll", "Source2EngineToClient001"));
	panel = static_cast<IVPanel*>(get_interface("vgui2.dll", "VGUI_Panel010"));
	particle_mgr = static_cast<CParticleSystemMgr*>(get_interface("particles.dll", "ParticleSystemMgr003"));
	input_system = static_cast<IInputSystem*>(get_interface("inputsystem.dll", "InputSystemVersion001"));

	auto* const client = get_interface("client.dll", "Source2Client002");
	auto* vmt_slot = *(uintptr_t**)client + 25;
	const auto address_start = *vmt_slot + 3;
	entity = *reinterpret_cast<CGameEntitySystem**>((address_start + *(uint32_t*)(address_start)+4));

	utilities::send_message("[+] interfaces is loaded");
}