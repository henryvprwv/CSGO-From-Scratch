#pragma once
#include <cstdint>

class Memory
{
public:
	template <typename Return, typename ... Arguments>
	constexpr Return Call(void* Vmt, const std::uint32_t Index, Arguments ... Args) noexcept
	{
		if (!Vmt) return Return{};
		using Function = Return(__thiscall*)(void*, decltype(Args)...);
		return (*static_cast<Function**>(Vmt))[Index](Vmt, Args...);
	}


	constexpr void* Get(void* Vmt, const std::uint32_t Index) noexcept
	{
		return (*static_cast<void***>(Vmt))[Index];
	}
};

Memory* GetMemory();