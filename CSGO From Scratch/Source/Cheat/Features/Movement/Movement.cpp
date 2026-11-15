#include "Movement.h"

#include <Volvo/Classes/CUserCmd.h>
#include <Volvo/Classes/CEntity.h>
#include <Volvo/Interfaces/IEngineTrace.h>
#include <Core/Interfaces/Interfaces.h>
#include <iostream>

Movement* GetMovement()
{
	static Movement GMovement{};
	return &GMovement;
}

void Movement::OnCreateMove(CUserCmd* Cmd)
{
	this->EdgeJump(Cmd);
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
	static Vector PreLadderAngles;

	if (IsOnLadder && !WasOnLadder)
		PreLadderAngles = Cmd->ViewAngles;

	if (IsOnLadder && WasOnLadder)
	{
		if (Cmd->Buttons & (IN_MOVERIGHT | IN_MOVELEFT)) return;

		Vector ViewAngles = { -89.f, PreLadderAngles.Y + 90.f, 0.f };
		ViewAngles.Clamp();

		Cmd->ViewAngles = ViewAngles;

		if (Cmd->Buttons & IN_FORWARD)
			Cmd->Buttons |= IN_MOVERIGHT;

		if (Cmd->Buttons & IN_BACK)
			Cmd->Buttons |= IN_MOVELEFT;
	}

	if (!IsOnLadder && WasOnLadder)
		Cmd->ViewAngles = PreLadderAngles;

	WasOnLadder = IsOnLadder;
}

void Movement::EdgeJump(CUserCmd* Cmd)
{
	auto pLocal = CEntity::GetLocalPlayer();

	if (pLocal->GetMoveType() == MOVETYPE_LADDER) return;

	const Vector& LocalPos = pLocal->GetAbsOrigin();

	int Offset = 10;

	Vector TracePoints[4]
	{
		{ LocalPos.X - Offset, LocalPos.Y - Offset, LocalPos.Z - 30.f }, // back left
		{ LocalPos.X + Offset, LocalPos.Y - Offset, LocalPos.Z - 30.f }, // front left
		{ LocalPos.X - Offset, LocalPos.Y + Offset, LocalPos.Z - 30.f }, // back right
		{ LocalPos.X + Offset, LocalPos.Y + Offset, LocalPos.Z - 30.f }, // back left
	};

	int PointsInAir = 0;

	for (int i = 0; i < 4; i++)
	{
		CGameTrace Trace;
		Ray TraceRay;
		TraceRay.Init(LocalPos, TracePoints[i]);
		CTraceFilter Filter{ pLocal };
		constexpr unsigned int Mask = CONTENTS_SOLID | CONTENTS_MOVEABLE | CONTENTS_PLAYERCLIP | CONTENTS_GRATE;

		GetInterfaces()->Trace->TraceRay(TraceRay, Mask, &Filter, &Trace);
		//std::cout << Trace.DidHit() << "\n";
		if (!Trace.DidHit())
			PointsInAir++;
	}

	if (PointsInAir == 4)
		Cmd->Buttons |= IN_JUMP;
}