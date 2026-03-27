#include "HookManager.h"
void HookManager::initHooks() {
	hooks.push_back(new CommandHook::ValidRange());
	hooks.push_back(new ItemEnchantsHook::canEnchant());
	hooks.push_back(new EnchantUtilsHook::applyEnchant());

	for (auto hook : hooks) {
		hook->Initialize();
		MH_EnableHook(MH_ALL_HOOKS);
	}
}