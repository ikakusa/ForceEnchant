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
			uintptr_t address = SigScan("48 89 5C 24 ?? 48 89 74 24 ?? 55 57 41 56 48 8D 6C 24 B9 48 81 EC ?? ?? ?? ?? 49 8B D9");
			return CreateHook(funcPtr, address, handle);
		}
	};
}