#pragma once
#include "../../includes.hpp"

namespace interfaces {
	extern IEngineClient* engine;
	extern IInputSystem* input_system;
	extern IVPanel* panel;
	extern IDirect3DDevice9* directx;
	extern CParticleSystemMgr* particle_mgr;
	extern CGameEntitySystem* entity;

	void initialize();
}