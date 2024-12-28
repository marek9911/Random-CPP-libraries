#pragma once
#include <string>
#include <algorithm>

#ifndef _MSC_VER
#error "This library is only compatible with MSVC"
#endif

// Calling convention
enum class CConv : size_t
{
	Cdecl,
	Stdcall,
	Thiscall,
	Fastcall,
	Vectorcall
};

namespace memory
{
	template <typename R, typename... A>
	struct RemoveCallConv
	{
		using Type = R(*)(A...);
	};

	#ifndef _WIN64 
	template <typename R, typename... A>
	struct RemoveCallConv<R(__cdecl*)(A...)>
	{
		using Type = R(*)(A...);
	};

	template <typename R, typename... A>
	struct RemoveCallConv<R(__stdcall*)(A...)>
	{
		using Type = R(*)(A...);
	};

	template <typename R, typename... A>
	struct RemoveCallConv<R(__thiscall*)(A...)>
	{
		using Type = R(*)(A...);
	};

	template <typename R, typename... A>
	struct RemoveCallConv<R(__fastcall*)(A...)>
	{
		using Type = R(*)(A...);
	};
	#endif
	
	template <typename R, typename... A>
	struct RemoveCallConv<R(__vectorcall*)(A...)>
	{
		using Type = R(*)(A...);
	};

	// Removes calling convention from function pointer
	template <typename R, typename... A>
	using RemoveCallConvT = typename RemoveCallConv<R, A...>::Type;

	struct PageInfo
	{
		void* region;
		size_t size;
		unsigned long pageProtection;
	};

	// RAII-style mechanism for unlocking and restoring memory regions within scope block
	class RegionUnlocker
	{
		public:
			RegionUnlocker(void* region, size_t size);
			~RegionUnlocker();
			const PageInfo pageInfo;
	};

	// Unlocks memory region for writing
	PageInfo UnlockRegion(void* region, size_t size);

	// Restores memory region protection
	void RestoreRegion(const PageInfo& pageInfo);
	
	// Returns base address of application
	void* GetBaseAddress();

	// Writes to an address that may have read only access, returns a pointer to the end of written memory (destination + size) 
	void* Write(void* destination, const void* source, size_t size);
	void* Write(void* destination, const std::string& string);
	void* Write(void* destination, const std::wstring& string);

	// Fills memory that may have read only access with specified value, returns a pointer to the end of written memory (destination + size)
	void* Fill(void* destination, uint8_t value, size_t size);
	
	// Return hex dump of address as string (uppercase two digits separated with spaces)
	std::string HexDump(const void* destination, size_t size);
	std::wstring HexDumpW(const void* destination, size_t size);

	// Returns true if given address is readable
	bool CheckReadableAddress(const void* address);

	// Returns true if given address is writable
	bool CheckWritableAddress(const void* address);

	// Returns T with address of base + offset
	template <typename T = void*>
	T Offset(size_t offset) {
		uintptr_t addr = reinterpret_cast<uintptr_t>(GetBaseAddress()) + offset;
		return (T)addr; // C-style cast needed here
	}

	// Returns address of given function or class function as void*
	template <typename Func>
	void* FuncAddr(Func function) requires (std::is_function_v<std::remove_pointer_t<Func>> || std::is_member_function_pointer_v<Func>) {
		return *reinterpret_cast<void**>(&function);
	}
	
	// Write elements memory consecutively to address that may have read only access
	template <typename... Args>
	void* WriteElements(void* destination, const Args&... args) requires (sizeof...(args) > 0) {
		void* destStep = destination;
		((destStep = Write(destStep, &args, sizeof(args))), ...);
		return destStep;
	}

	// Fill values to an address that may have read only access
	template <typename T>
	void* FillType(void* destination, T value, size_t numOfValues) {
		RegionUnlocker reg(destination, numOfValues * sizeof(T));
		return std::fill_n(reinterpret_cast<T*>(destination), numOfValues, value);
	}

	// Calls an arbitrary function at given address
	template <typename RetType = void, CConv callingConvention = CConv::Cdecl, typename... Args>
	RetType Call(void* functionAddress, Args... args) {
		if constexpr (callingConvention == CConv::Thiscall) {
			static_assert(sizeof...(Args) > 0, "Thiscall calling convention requires at least 1 argument: this pointer");
		}

		using FuncType = std::tuple_element_t<std::to_underlying(callingConvention), std::tuple<
			RetType(__cdecl*)(Args...),
			RetType(__stdcall*)(Args...),
			RetType(__thiscall*)(Args...),
			RetType(__fastcall*)(Args...),
			RetType(__vectorcall*)(Args...)
		>>;

		FuncType func = reinterpret_cast<FuncType>(functionAddress);
		return func(args...);
	}

	template <typename FuncSig, typename RetType, typename... Args>
	class FuncPtrBase {};

	template <typename FuncSig, typename RetType, typename... Args>
	class FuncPtrBase<FuncSig, RetType(Args...)>
	{
		public:
			FuncPtrBase(void* funcAddr)
			: funcPtr(reinterpret_cast<FuncSig>(funcAddr)) {}

			RetType operator()(Args... args) {
				return this->funcPtr(args...);
			}

			const FuncSig funcPtr;
	};

	// Wrapper for custom type function pointers
	template <typename FuncSig>
	using FuncPtr = FuncPtrBase<FuncSig, std::remove_pointer_t<RemoveCallConvT<FuncSig>>>;
};

#define _MEM_PAD_CONCAT(a, b) a##b
#define _MEM_PAD_CONCAT_EXPAND(a, b) _MEM_PAD_CONCAT(a, b)
#define _MEM_PAD_RAND_NAME _MEM_PAD_CONCAT_EXPAND(memPad, __COUNTER__)

// Pads a memory inside struct/class (use other versions of MEM_PAD to make the padded memory private inside public/protected/private access)
#define MEM_PAD(bytes) uint8_t _MEM_PAD_RAND_NAME[bytes]
#define MEM_PAD_PUB(bytes) private: MEM_PAD(bytes); public:
#define MEM_PAD_PROT(bytes) private: MEM_PAD(bytes); protected:
#define MEM_PAD_PRIV(bytes) private: MEM_PAD(bytes); private:

// Please use memory::Offset() instead
#define OFFSET(_type, _offset) (::memory::Offset<_type>((uintptr_t)(_offset)))

// Auto size adapter for passing bytes inside string to memory::Write()
#define STR_BYTES(str) (str), (sizeof(str) - 1)
