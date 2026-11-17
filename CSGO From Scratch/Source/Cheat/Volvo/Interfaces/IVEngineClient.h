#pragma once

#include <Utility/Memory/Memory.h>
#include <Volvo/Classes/CEntity.h>

//https://github.com/RileyKun/cstrike15_src-2019/blob/a4c7aaea259319aca272839f688a3f4d9fe1cb2c/public/cdll_int.h#L299-L874

class IVEngineClient
{
public:
	constexpr void GetScreenSize(int& Width, int& Height) noexcept
	{
		GetMemory()->Call<void>(this, 5, &Width, &Height);
	}

	bool GetPlayerInfo(int EntNum, PlayerInfo* pInfo)
	{
		return GetMemory()->Call<bool>(this, 8, EntNum, pInfo);
	}

	constexpr std::int32_t GetLocalPlayer() noexcept
	{
		return GetMemory()->Call<std::int32_t>(this, 12);
	}

	Vector GetViewAngles() noexcept
	{
		Vector ViewAngles;
		GetMemory()->Call<void>(this, 18, &ViewAngles);
		return ViewAngles;
	}

	void SetViewAngles(Vector &ViewAngles) noexcept
	{
		GetMemory()->Call<void, Vector&>(this, 19, ViewAngles);
	}

	bool IsInGame() noexcept
	{
		return GetMemory()->Call<bool>(this, 26);
	}
};