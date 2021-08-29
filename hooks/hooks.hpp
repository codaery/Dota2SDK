#pragma once
#include "../includes.hpp"

namespace hooks {
	void initialize();

	using paint_traverse_fn = void(__thiscall*)(IVPanel*, IVGuiPaintSurface*, VPANEL, bool, bool);
	using on_remove_entity_fn = CEntityInstance*(__thiscall*)(CGameEntitySystem*, CEntityInstance*, EntityHandle);
	using on_add_entity_fn = CEntityInstance*(__thiscall*)(CGameEntitySystem*, CEntityInstance*, EntityHandle);
	using create_particle_collection_fn = void*(__thiscall*)(CParticleSystemMgr*, CWeakHandle_InfoForResourceTypeIParticleSystemDefinition*,
		void*, IParticleSystemQuery*, bool, float, int);
	using set_rendering_enabled_fn = void(__thiscall*)(void*, bool);


	CEntityInstance* on_remove_entity(CGameEntitySystem*, CEntityInstance*, EntityHandle);
	CEntityInstance* on_add_entity(CGameEntitySystem*, CEntityInstance*, EntityHandle);

	void paint_traverse(IVPanel*, IVGuiPaintSurface*, VPANEL, bool, bool);
	void* create_particle_collection(CParticleSystemMgr* thisptr,
		CWeakHandle_InfoForResourceTypeIParticleSystemDefinition* info, void* unk,
		IParticleSystemQuery* query, bool bUnk, float fUnk, int iUnk);

	void set_rendering_enabled(void*, bool);
}