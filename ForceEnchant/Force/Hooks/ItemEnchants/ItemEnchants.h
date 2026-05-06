#pragma once
#include <MemUtils.h>
#include "../Hooks.h"
#include "../../SDK/EnchantResult.h"

//EnchantCommand::executeのstring failedNamesの少し上にあります
// シグネチャが__int64 a1, __int64 a2, char a3, int a4, unsigned __int8 a5の物がすぐ上にあります
// そこに飛びます
// __int64 a1, __int64 a2, _QWORD *a3, char a4のシグネチャの関数 (a1, a2, v8, a5) 的な感じで呼び出してるに飛びます
// シグネチャがint *a1, __int64 a2, unsigned __int64 a3, unsigned __int8 a4 (&v11[40], a1, *a3, v4) 的な感じで呼び出してる
// 上の関数はすぐ上にあります
// その関数がItemEnchants::canEnchant
namespace ItemEnchantsHook {
	class canEnchant : public Hook {
	private:
		static inline std::unique_ptr<FuncHook> funcPtr;
	public:
		canEnchant() : Hook("ItemEnchants::canEnchant") {};
		static EnchantResult* handle(__int64 _this, EnchantResult* result, EnchantMentInstance* en, bool allowNonVanilla);
		bool Initialize() override {
			uintptr_t address = SigScan("41 57 41 56 41 55 41 54 56 57 53 48 83 EC 20 4C 89 C7 48 89 D6 40"); //26.20
			return CreateHook(funcPtr, address, handle);
		}
	};
}