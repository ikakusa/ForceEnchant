#pragma once
#include <MemUtils.h>
#include "../Hooks.h"

namespace CommandHook {
	class ValidRange : public Hook {
	private:
		static inline std::unique_ptr<FuncHook> funcPtr;
	public:
		ValidRange() : Hook("Command::ValidRange") {};
		static bool handle(int input, int low, int high, __int64 out);
		bool Initialize() override {
			uintptr_t address = SigScan("40 55 53 56 57 41 56 48 8D 6C 24 C9 48 81 EC ?? ?? ?? ?? 49 8B D9 41");
			return CreateHook(funcPtr, address, handle);
		}
	};
}