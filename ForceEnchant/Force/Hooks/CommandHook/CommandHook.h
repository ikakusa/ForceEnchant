#pragma once
#include <MemUtils.h>
#include "../Hooks.h"

//search: commands.enchant.invalidLeve -> EnchantCommand::execute
// è„Ç…çsÇ≠Ç∆ifï∂Ç… command::validRange
//
namespace CommandHook {
	class ValidRange : public Hook {
	private:
		static inline std::unique_ptr<FuncHook> funcPtr;
	public:
		ValidRange() : Hook("Command::ValidRange") {};
		static bool handle(int input, int low, int high, __int64 out);
		bool Initialize() override {
			uintptr_t address = SigScan("55 41 57 41 56 41 55 41 54 56 57 53 48 81 EC D8 00 00 00 48 8D AC 24 80 00 00 00 48 C7 45 50 FE FF FF FF 4C 89 CE 39"); //26.60
			return CreateHook(funcPtr, address, handle);
		}
	};
}