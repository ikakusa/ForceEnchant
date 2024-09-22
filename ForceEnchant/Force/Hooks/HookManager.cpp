#include "HookManager.h"
void HookManager::initHooks() {
	hooks.push_back(new CommandHook::ValidRange());
	hooks.push_back(new ItemEnchantsHook::canEnchant());

	for (auto hook : hooks) {
		hook->Initialize();
		MH_EnableHook(MH_ALL_HOOKS);
	}
}