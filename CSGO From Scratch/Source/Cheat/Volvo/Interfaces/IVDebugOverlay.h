#pragma once

#include <Utility/Memory/Memory.h>
#include <Volvo/Classes/Vector.h>

// https://github.com/RileyKun/cstrike15_src-2019/blob/main/public/engine/ivdebugoverlay.h

class IVDebugOverlay
{
public:
	int ScreenPosition(const Vector& Point, Vector& Screen)
	{
		return GetMemory()->Call<int>(this, 13, &Point, &Screen);
	}
};