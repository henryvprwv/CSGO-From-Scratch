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
	void EdgeJump(CUserCmd* Cmd);
	void LadderBounce(CUserCmd* Cmd);
};

Movement* GetMovement();