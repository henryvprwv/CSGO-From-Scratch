#pragma once

#include <Core/Interfaces/Interfaces.h>

using PaintTraverse = void(__thiscall*)(IPanel*, int, bool, bool);
inline PaintTraverse PaintTraverseOriginal = nullptr;

void __stdcall PaintTraverseHook(int VGUIPannel, bool ForceRepaint, bool AllowForce);