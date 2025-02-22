#pragma once
#include <MemUtils.h>
#include "../Hooks.h"
#include "../../SDK/EnchantResult.h"

namespace ItemEnchantsHook {
	class canEnchant : public Hook {
	private:
		static inline std::unique_ptr<FuncHook> funcPtr;
	public:
		canEnchant() : Hook("ItemEnchants::canEnchant") {};
		static EnchantResult* handle(__int64 _this, EnchantResult* result, EnchantMentInstance* en, bool allowNonVanilla);
		bool Initialize() override {
			uintptr_t address = SigScan("4C 89 44 24 ?? 53 55 57 41");
			return CreateHook(funcPtr, address, handle);
		}
	};
}