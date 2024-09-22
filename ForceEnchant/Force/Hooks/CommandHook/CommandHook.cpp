#include "CommandHook.h"

bool CommandHook::ValidRange::handle(int input, int low, int high, __int64 out) {
	static auto oFunc = funcPtr->GetFastcall<bool, int, int, int, __int64>();
	return true;
}