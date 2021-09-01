an internal base paste for make hacks on dota2, written in c++                                                                                                                            
language: ![c++](https://github.com/carterjwasd/dota2_cheat/blob/main/c%2B%2B.jpg)

```cpp

engine = static_cast<IEngineClient*>(get_interface("engine.dll", "Source2EngineToClient001"));
panel = static_cast<IVPanel*>(get_interface("vgui2.dll", "VGUI_Panel010"));
particle_mgr = static_cast<CParticleSystemMgr*>(get_interface("particles.dll", "ParticleSystemMgr003"));
input_system = static_cast<IInputSystem*>(get_interface("inputsystem.dll", "InputSystemVersion001"));

auto* const client = get_interface("client.dll", "Source2Client002");
auto* vmt_slot = *(uintptr_t**)client + 25;
const auto address_start = *vmt_slot + 3;
entity = *reinterpret_cast<CGameEntitySystem**>((address_start + *(uint32_t*)(address_start)+4));

```
