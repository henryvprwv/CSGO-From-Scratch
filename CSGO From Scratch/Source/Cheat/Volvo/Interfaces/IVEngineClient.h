#pragma once

#include <Utility/Memory/Memory.h>
#include <Volvo/Classes/CEntity.h>

//https://github.com/RileyKun/cstrike15_src-2019/blob/a4c7aaea259319aca272839f688a3f4d9fe1cb2c/public/cdll_int.h#L299-L874

class IVEngineClient
{
public:
	constexpr void GetScreenSize(int& H, int& W) noexcept
	{
		return GetMemory()->Call<void>(this, 5, H, W);
	}

	constexpr std::int32_t GetLocalPlayer() noexcept
	{
		return GetMemory()->Call<std::int32_t>(this, 12);
	}

	bool GetPlayerInfo(int EntNum, PlayerInfo* pInfo)
	{
		return GetMemory()->Call<bool>(this, 8, EntNum, pInfo);
	}
};