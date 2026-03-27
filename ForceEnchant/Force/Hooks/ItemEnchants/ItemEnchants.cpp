#include "ItemEnchants.h"

EnchantResult* ItemEnchantsHook::canEnchant::handle(__int64 _this, EnchantResult* result, EnchantMentInstance* en, bool allowNonVanilla) {
	static auto oFunc = funcPtr->GetFastcall<EnchantResult*, __int64, EnchantResult*, EnchantMentInstance*, bool>();
	return oFunc(_this, result, en, true);
}

bool EnchantUtilsHook::applyEnchant::handle(__int64 itemStackBase, unsigned char type, int level, bool allowNonVanilla) {
	static auto oFunc = funcPtr->GetFastcall<bool, __int64, unsigned char, int, bool>();
	return oFunc(itemStackBase, type, level, true);
}