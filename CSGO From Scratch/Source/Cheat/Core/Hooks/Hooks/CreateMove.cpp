#include "CreateMove.h"

#include <Core/Cheat Manager/Cheat Manager.h>
#include <iostream>

bool __stdcall CreateMoveHook(float InputSampleTime, CUserCmd* Cmd)
{
	GetCheatManager()->OnCreateMove(Cmd);

	return CreateMoveOriginal(GetInterfaces()->ClientModeS, InputSampleTime, Cmd);
}