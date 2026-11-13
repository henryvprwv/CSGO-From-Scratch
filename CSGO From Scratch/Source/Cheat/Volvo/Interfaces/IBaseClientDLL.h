#pragma once

#include <Utility/Memory/Memory.h>
#include <Volvo/Classes/CClientClass.h>

class IBaseClientDLL
{
public:
	constexpr CClientClass* GetAllClasses() noexcept
	{
		return GetMemory()->Call<CClientClass*>(this, 8);
	}
}; 