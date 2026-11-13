#include "Memory.h"

Memory* GetMemory()
{
	static Memory GMemory{};
	return &GMemory;
}
