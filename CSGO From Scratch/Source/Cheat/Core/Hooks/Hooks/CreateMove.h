#pragma once

#include <Volvo/Classes/CUserCmd.h>
#include <Core/Interfaces/Interfaces.h>

using CreateMove = bool(__thiscall*)(void*, float, CUserCmd*);
inline CreateMove CreateMoveOriginal = nullptr;

bool __stdcall CreateMoveHook(float InputSampleTime, CUserCmd* Cmd);