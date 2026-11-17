#include "PaintTraverse.h"

#include <Core/Cheat Manager/Cheat Manager.h>

void __stdcall PaintTraverseHook(int VGUIPannel, bool ForceRepaint, bool AllowForce)
{
	GetCheatManager()->OnPaintTraverse(VGUIPannel);

	return PaintTraverseOriginal(GetInterfaces()->Panel, VGUIPannel, ForceRepaint, AllowForce);
}