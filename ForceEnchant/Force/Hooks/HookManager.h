#pragma once
#include "Hooks.h"

//Hooks
#include "CommandHook/CommandHook.h"
#include "ItemEnchants/ItemEnchants.h"
//
class Hook;
class HookManager {
private:
	std::vector<Hook*> hooks;
	HookManager() {};
public:
	HookManager(const HookManager&) = delete;
	HookManager& operator=(const HookManager&) = delete;
	~HookManager() {
		DeleteHooks();
	}

	static HookManager& getInstance() {
		static HookManager instance;
		return instance;
	}
	static void initHooks();
	static void DeleteHooks();
};