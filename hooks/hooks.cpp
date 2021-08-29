#include "hooks.hpp"
#include <vector>

hooks::paint_traverse_fn original_paint_traverse;
hooks::on_remove_entity_fn original_on_remove_entity;
hooks::on_add_entity_fn original_on_add_entity;
hooks::create_particle_collection_fn original_create_particle_collection;
hooks::set_rendering_enabled_fn original_set_rendering_enabled;

std::vector<CEntityInstance*> heroes;

inline unsigned int get_virtual(void* _class, unsigned int index) { 
	return static_cast<unsigned int>((*static_cast<int**>(_class))[index]); 
}

CEntityInstance* hooks::on_remove_entity(CGameEntitySystem* ecx, CEntityInstance* ptr, EntityHandle index) {
	const char* typeName = ptr->SchemaDynamicBinding()->bindingName;

	if (strstr(typeName, "DOTA_Unit_Hero"))
	{
		for (size_t i = heroes.size(); i-- > 0;)
		{
			if (heroes[i] == ptr)
			{
				heroes.erase(heroes.begin() + i);
				printf("[+] on_remove_entity: %s\n", typeName);
				break;
			}
		}
	}

	return original_on_remove_entity(ecx, ptr, index);
}

CEntityInstance* hooks::on_add_entity(CGameEntitySystem* ecx, CEntityInstance* ptr, EntityHandle index) {
	auto ret = original_on_add_entity(ecx, ptr, index);
	const char* typeName = ptr->SchemaDynamicBinding()->bindingName;

	if (strstr(typeName, "DOTA_Unit_Hero"))
	{
		auto alreadyExists = false;
		for (auto hero : heroes)
		{
			if (typeName == hero->SchemaDynamicBinding()->bindingName)
			{
				alreadyExists = true;
				break;
			}
		}

		if (!alreadyExists)
		{
			heroes.push_back(ptr);
			printf("[+] on_add_entity: %s\n", typeName);
		}
	}

	return ret;
}

void hooks::paint_traverse(IVPanel* ecx, IVGuiPaintSurface* surface, VPANEL vpanel, bool force_repaint, bool allow_force) {
	original_paint_traverse(ecx, surface, vpanel, force_repaint, allow_force);

	for (const auto hero : heroes)
	{
		if (hero->CanBeSeenByTeam(DOTA_TEAM_RADIANT) && hero->CanBeSeenByTeam(DOTA_TEAM_DIRE))
			hero->DrawEntityDebugOverlays(ABSBOX);
	}
}

void* hooks::create_particle_collection(CParticleSystemMgr* thisptr,
	CWeakHandle_InfoForResourceTypeIParticleSystemDefinition* info, void* unk,
	IParticleSystemQuery* query, bool bUnk, float fUnk, int iUnk) {
	void* particle_collection = original_create_particle_collection(
		thisptr, info, unk, query, bUnk, fUnk, iUnk);

	return particle_collection;
}

void hooks::set_rendering_enabled(void* thisptr, bool state) {
	original_set_rendering_enabled(thisptr, true);
}

void hooks::initialize() {
	const auto paint_traverse_index = reinterpret_cast<void*>(get_virtual(interfaces::panel, 55));
	const auto add_entity_index = reinterpret_cast<void*>(get_virtual(interfaces::entity, 14));
	const auto remove_entity_index = reinterpret_cast<void*>(get_virtual(interfaces::entity, 15));
	const auto create_particle_collection_index = reinterpret_cast<void*>(get_virtual(interfaces::particle_mgr, 17));

	if (MH_Initialize() != MH_OK)
		throw std::runtime_error("[!] failed to initialize minhook.");

	if (MH_CreateHook(paint_traverse_index, &paint_traverse, reinterpret_cast<void**>(&original_paint_traverse)) != MH_OK)
		throw std::runtime_error("[!] failed to initialize paint_traverse.");

	if (MH_CreateHook(add_entity_index, &on_add_entity, reinterpret_cast<void**>(&original_on_add_entity)) != MH_OK)
		throw std::runtime_error("[!] failed to initialize add_entity.");

	if (MH_CreateHook(remove_entity_index, &on_remove_entity, reinterpret_cast<void**>(&original_on_remove_entity)) != MH_OK)
		throw std::runtime_error("[!] failed to initialize remove_emtity.");

	if (MH_CreateHook(create_particle_collection_index, &create_particle_collection, reinterpret_cast<void**>(&original_create_particle_collection)) != MH_OK)
		throw std::runtime_error("[!] failed to initialize create_particle_collection.");

	if (MH_EnableHook(MH_ALL_HOOKS) != MH_OK)
		throw std::runtime_error("[!] failed to enable hooks.");

	utilities::send_message(" [+] hooks is loaded");

}