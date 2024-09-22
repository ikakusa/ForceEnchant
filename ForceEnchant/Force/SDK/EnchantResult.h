#pragma once
#include <MemUtils.h>

class EnchantMentInstance {
public:
	BUILD_ACCESS(int, enchantType, 0x0);
};

class EnchantResult {
public:
	BUILD_ACCESS(int, enchantResultType, 0x0);
	BUILD_ACCESS(int, enchantId, 0x8);
	BUILD_ACCESS(int, level, 0x10);
};