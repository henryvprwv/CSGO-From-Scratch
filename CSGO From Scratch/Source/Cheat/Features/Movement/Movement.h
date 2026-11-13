#pragma once

class CUserCmd;

#include <Core/Interfaces/Interfaces.h>

class Movement
{
public:
	void OnCreateMove(CUserCmd* Cmd);

private:
	void BunnyHop(CUserCmd* Cmd);
	void FastLadder(CUserCmd* Cmd);
};

Movement* GetMovement();