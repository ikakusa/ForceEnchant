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
			uintptr_t address = SigScan("55 56 57 48 81 EC C0 00 00 00 48 8D AC 24 80 00 00 00 48 C7 45 38 FE FF FF FF 4C 89 CE 89"); //26.20
			return CreateHook(funcPtr, address, handle);
		}
	};
}