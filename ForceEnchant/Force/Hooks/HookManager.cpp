#include "HookManager.h"
static char origBytes_canEnchant_isCompatible[6];
static uintptr_t isCompatible_addr = SigScan("0F 84 8C 00 00 00 49 FF C7"); //ItemEnchants::canEnchantの中のif文のjmp命令
void HookManager::initHooks() {
	hooks.push_back(new CommandHook::ValidRange());
	hooks.push_back(new ItemEnchantsHook::canEnchant());

	copyBytes((void*)isCompatible_addr, (void*)origBytes_canEnchant_isCompatible, 6);
	nopBytes((void*)isCompatible_addr, 6);

	for (auto hook : hooks) {
		hook->Initialize();
		MH_EnableHook(MH_ALL_HOOKS);
	}
}

void HookManager::DeleteHooks() {
	patchBytes((void*)isCompatible_addr, (void*)origBytes_canEnchant_isCompatible, 6);
	hooks.clear();
}