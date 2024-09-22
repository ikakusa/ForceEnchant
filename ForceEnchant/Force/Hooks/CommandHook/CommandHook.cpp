#include "CommandHook.h"

bool CommandHook::ValidRange::handle(int input, int low, int high, __int64 out) {
	static auto oFunc = funcPtr->GetFastcall<bool, unsigned char, bool>();
	return true;
}