#include "HookManager.h"
void HookManager::initHooks() {
	hooks.push_back(new CommandHook::ValidRange());

	for (auto hook : hooks) {
		hook->Initialize();
		MH_EnableHook(MH_ALL_HOOKS);
	}
}