#pragma once

#include <Utility/Memory/Memory.h>

//https://github.com/RileyKun/cstrike15_src-2019/blob/a4c7aaea259319aca272839f688a3f4d9fe1cb2c/public/cdll_int.h#L299-L874

class IVEngineClient
{
public:
	constexpr std::int32_t GetLocalPlayer() noexcept
	{
		return GetMemory()->Call<std::int32_t>(this, 12);
	}
};