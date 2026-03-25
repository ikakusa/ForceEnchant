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
			uintptr_t address = SigScan("48 89 5C 24 08 48 89 74 24 10 48 89 7C 24 18 55 48 8D 6C 24 A9 48 81 EC A0 00 00 00 49"); //26.10
			return CreateHook(funcPtr, address, handle);
		}
	};
}