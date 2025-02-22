#include "ItemEnchants.h"

EnchantResult* ItemEnchantsHook::canEnchant::handle(__int64 _this, EnchantResult* result, EnchantMentInstance* en, bool allowNonVanilla) {
	static auto oFunc = funcPtr->GetFastcall<EnchantResult*, __int64, EnchantResult*, EnchantMentInstance*, bool>();
	return oFunc(_this, result, en, true);
}