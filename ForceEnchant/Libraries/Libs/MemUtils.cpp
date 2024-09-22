#include "MemUtils.h"
#include <Psapi.h>

void MemoryUtils::init() {
	MH_Initialize();
	isInitialized = true;
}

void MemoryUtils::restore() {
	MH_DisableHook(MH_ALL_HOOKS);
	MH_RemoveHook(MH_ALL_HOOKS);
	MH_Uninitialize();
}
uintptr_t MemoryUtils::findSig(std::string_view signature) {
    auto result = SigScanSafe(signature);
    return result.value();
} 

std::optional<uintptr_t> MemoryUtils::SigScanSafe(std::string_view signature) {
    const auto parsed = hat::parse_signature(signature);

    const auto begin = reinterpret_cast<std::byte*>(getBase());
    const auto end = begin + GetMinecraftSize();
    const auto result = hat::find_pattern(begin, end, parsed.value());

    if (!result.has_result()) return std::nullopt;
    return reinterpret_cast<uintptr_t>(result.get());
}