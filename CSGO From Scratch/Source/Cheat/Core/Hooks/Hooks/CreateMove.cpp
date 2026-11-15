#include "CreateMove.h"

#include <Core/Cheat Manager/Cheat Manager.h>
#include <iostream>

bool __stdcall CreateMoveHook(float InputSampleTime, CUserCmd* Cmd)
{
	if (!Cmd || !Cmd->CommandNumber)
		return CreateMoveOriginal(GetInterfaces()->ClientModeS, InputSampleTime, Cmd);

	GetCheatManager()->OnCreateMove(Cmd);

	return false;
}