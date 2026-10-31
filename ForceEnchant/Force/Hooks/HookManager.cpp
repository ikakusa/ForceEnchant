#include "HookManager.h"
static char origBytes_canEnchant_isCompatible[6];
/*
 if ( !(*(unsigned __int8 (__fastcall **)(_QWORD))(**(_QWORD **)(xmmword_12971C00 + 8 * v6) + 8LL))(*(_QWORD *)(xmmword_12971C00 + 8 * v6)) )
		goto LABEL_21;

上の処理です
while文の中に入っています
goto文でresultにConflictのid(1)を入れています
*/

///26.60
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