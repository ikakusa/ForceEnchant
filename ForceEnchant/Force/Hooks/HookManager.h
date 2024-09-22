#pragma once
#include "Hooks.h"

//Hooks
#include "CommandHook/CommandHook.h"
//
class Hook;
class HookManager {
private:
	static inline std::vector<Hook*> hooks;
public:
	static void initHooks();
	static void DeleteHooks() {
		hooks.clear();
	}
};