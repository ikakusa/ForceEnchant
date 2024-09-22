#include "ItemEnchants.h"

EnchantResult* ItemEnchantsHook::canEnchant::handle(__int64 _this, EnchantResult* result, __int64 en, bool allowNonVanilla) {
	static auto oFunc = funcPtr->GetFastcall<EnchantResult*, __int64, EnchantResult*, __int64, bool>();
	return oFunc(_this, result, en, true);
}