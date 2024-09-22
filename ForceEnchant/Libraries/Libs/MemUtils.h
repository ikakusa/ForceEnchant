#pragma once
#include <MinHook/MinHook.h>
#include <memory>
#include <Psapi.h>
#include <libhat.hpp>
#include <string>
#include "xorstr.hpp"
class FuncHook;
class MemoryUtils {
private:
	static uintptr_t getBase() {
		static uintptr_t mc = reinterpret_cast<uintptr_t>(GetModuleHandleA("Minecraft.Windows.exe"));
		return mc;
	}
	static unsigned long GetMinecraftSize() {
		HMODULE base = GetModuleHandleA("Minecraft.Windows.exe");
		if (!base) return 0;

		MODULEINFO moduleInfo;
		if (!GetModuleInformation(GetCurrentProcess(), base, &moduleInfo, sizeof(MODULEINFO))) return 0;
		return moduleInfo.SizeOfImage;
	}

	static uintptr_t SlideAddress(uintptr_t offset) { return getBase() + offset; }
	static std::optional<uintptr_t> SigScanSafe(std::string_view signature);
public:
	static inline bool isInitialized = false;
	static void init();
	static void restore();

#define INRANGE(x, a, b) (x >= a && x <= b)
#define GET_BYTE(x) (GET_BITS(x[0]) << 4 | GET_BITS(x[1]))
#define GET_BITS(x) (INRANGE((x & (~0x20)), 'A', 'F') ? ((x & (~0x20)) - 'A' + 0xa) : (INRANGE(x, '0', '9') ? x - '0' : 0))
public:
	static uintptr_t findSig(std::string_view signature);
	static uintptr_t** getVtable(const char* szSignature, int offset) {
		uintptr_t** signatureOffset = 0x0;
		if (signatureOffset == 0x0) {
			uintptr_t sigOffset = findSig(szSignature);
			if (sigOffset != 0x0) {
				int finalOffset = *reinterpret_cast<int*>((sigOffset + offset));
				signatureOffset = reinterpret_cast<uintptr_t**>(sigOffset + finalOffset + 7);
				return signatureOffset;
			}
		}
		return 0u;
	}
	template <typename TRet, typename... TArgs>
	static inline auto* getFunc(uintptr_t origFunc) {
		using Fn = TRet(__fastcall*)(TArgs...);
		return reinterpret_cast<Fn>(origFunc);
	};
};

class FuncHook {
public:
	void* funcPtr;
	void* funcReal;
	bool valid;

	FuncHook(uintptr_t func, void* hooked) {
		funcPtr = reinterpret_cast<void*>(func);

		MH_STATUS ret = MH_CreateHook(funcPtr, hooked, &funcReal);
		valid = (ret == MH_OK);
		if (ret == MH_OK && (__int64)funcPtr > 10) {
		}
	};

	~FuncHook() {
		Restore();
	}

	void Restore() {
		if (funcPtr != nullptr)
			MH_DisableHook(funcPtr);
	}

	bool isValid() {
		return valid;
	}

	template <typename TRet, typename... TArgs>
	inline auto* GetFastcall() {
		using Fn = TRet(__fastcall*)(TArgs...);
		return reinterpret_cast<Fn>(funcReal);
	};
};

#pragma region DirectClassAccess

template <typename Ret, typename Type>
Ret& DirectAccess(Type* type, size_t offset) {
	union {
		size_t raw;
		Type* source;
		Ret* target;
	} u;
	u.source = type;
	u.raw += offset;
	return *u.target;
}

#define AS_FIELD(type, name, fn) __declspec(property(get = fn, put = set##name)) type name
#define DEF_FIELD_RW(type, name) __declspec(property(get = get##name, put = set##name)) type name

#define FAKE_FIELD(type, name)                                                                                       \
AS_FIELD(type, name, get##name);                                                                                     \
type get##name()

#define BUILD_ACCESS(type, name, offset)                                                                             \
AS_FIELD(type, name, get##name);                                                                                     \
type get##name() const { return DirectAccess<type>(this, offset); }												 \
void set##name(type v) const { DirectAccess<type>(this, offset) = v; }

#pragma endregion

__forceinline static bool CreateHook(std::unique_ptr<FuncHook>& breh, uintptr_t func, void* hooked, bool first = false) {
	breh = std::make_unique<FuncHook>(func, hooked);
	if (!first) return &breh;
	return breh->isValid();
}

__forceinline static uintptr_t getBaseAddress() {
	static const auto rangeStart = (uintptr_t)GetModuleHandleA("Minecraft.Windows.exe");
	return rangeStart;
}

template <unsigned int IIdx, typename TRet, typename... TArgs>
__forceinline static auto CallVFunc(void* thisptr, TArgs... argList) -> TRet {
	using Fn = TRet(__thiscall*)(void*, decltype(argList)...);
	return (*static_cast<Fn**>(thisptr))[IIdx](thisptr, argList...);
}

static __forceinline void nopBytes(void* dst, unsigned int size) {
	if (dst == nullptr) return;
	DWORD oldprotect;
	if (!VirtualProtect(dst, size, PAGE_EXECUTE_READWRITE, &oldprotect)) return;
	memset(dst, 0x90, size);
	if (!VirtualProtect(dst, size, oldprotect, &oldprotect)) return;
}
static __forceinline void copyBytes(void* src, void* dst, unsigned int size) {
	if (dst == nullptr || src == nullptr) return;
	DWORD oldprotect;
	if (!VirtualProtect(src, size, PAGE_EXECUTE_READWRITE, &oldprotect)) return;
	memcpy(dst, src, size);
	if (!VirtualProtect(src, size, oldprotect, &oldprotect)) return;
}
static __forceinline void patchBytes(void* dst, void* src, unsigned int size) {
	if (dst == nullptr || src == nullptr) return;
	DWORD oldprotect;
	if (!VirtualProtect(dst, size, PAGE_EXECUTE_READWRITE, &oldprotect)) return;
	memcpy(dst, src, size);
	if (!VirtualProtect(dst, size, oldprotect, &oldprotect)) return;
}
template <typename TRet, typename... TArgs>
static __forceinline TRet CallFunc(uintptr_t address, TArgs... args) {
	auto oFunc = MemoryUtils::getFunc<TRet, TArgs...>(address);
	return oFunc(args...);
}

#define SigScan(sig) MemoryUtils::findSig(xorstr_(sig))
#define ScanVtable(sig, offset) MemoryUtils::getVtable(xorstr_(sig), offset)