#include "Movement.h"

#include <Volvo/Classes/CUserCmd.h>
#include <Volvo/Classes/CEntity.h>
#include <iostream>

Movement* GetMovement()
{
	static Movement GMovement{};
	return &GMovement;
}

void Movement::OnCreateMove(CUserCmd* Cmd)
{
	this->BunnyHop(Cmd);
	this->FastLadder(Cmd);
}

void Movement::BunnyHop(CUserCmd* Cmd)
{
    auto pLocal = CEntity::GetLocalPlayer();

	if (pLocal->GetMoveType() == MOVETYPE_LADDER) return;

    if (!(pLocal->GetFlags() & FL_ONGROUND))
        Cmd->Buttons &= ~IN_JUMP;
}

void Movement::FastLadder(CUserCmd* Cmd)
{
	auto pLocal = CEntity::GetLocalPlayer();

	bool IsOnLadder = (pLocal->GetMoveType() == MOVETYPE_LADDER);
	static bool WasOnLadder = false;

	Vector PreLadderAngles;

	if (IsOnLadder && !WasOnLadder)
		PreLadderAngles = Cmd->ViewAngles;

	if (IsOnLadder && WasOnLadder)
	{
		if (Cmd->Buttons & (IN_MOVERIGHT | IN_MOVELEFT)) return;

		Cmd->ViewAngles = { -98.f, PreLadderAngles.Y + 90.f, 0.f };

		if (Cmd->Buttons & IN_FORWARD)
			Cmd->Buttons |= IN_MOVERIGHT;

		if (Cmd->Buttons & IN_BACK)
			Cmd->Buttons |= IN_MOVELEFT;
	}

	if (!IsOnLadder && WasOnLadder)
		Cmd->ViewAngles = PreLadderAngles;

	WasOnLadder = IsOnLadder;
}