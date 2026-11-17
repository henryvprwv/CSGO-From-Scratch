#pragma once

#include <Utility/Memory/Memory.h>

// https://github.com/ValveSoftware/source-sdk-2013/blob/e1f1fd42271805072f052051c26c21caa2c87b04/src/public/vgui/IPanel.h#L90

class IPanel
{
public:
	constexpr const char* GetName(std::uint32_t Panel) noexcept
	{
		return GetMemory()->Call<const char*>(this, 36, Panel);
	}
};