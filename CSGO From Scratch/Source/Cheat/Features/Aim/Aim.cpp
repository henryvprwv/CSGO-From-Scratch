#include "Aim.h"

#include <Core/Interfaces/Interfaces.h>
#include <Volvo/Classes/CEntity.h>
#include <Volvo/Classes/CUserCmd.h>
#include <Volvo/Interfaces/IEngineTrace.h>

Aim* GetAim()
{
	static Aim GAim{};
	return &GAim;
}

void Aim::OnCreateMove(CUserCmd* Cmd)
{
	this->TriggerBot(Cmd);
}

void Aim::TriggerBot(CUserCmd* Cmd)
{
	auto pLocal = CEntity::GetLocalPlayer();

	auto EyePos = pLocal->GetEyePosition();

	Vector Forward;
	Vector::AngleVectors(Cmd->ViewAngles, &Forward, nullptr, nullptr);
	Vector End = EyePos + Forward * 5000.f;

	Ray TraceRay;
	TraceRay.Init(EyePos, End);
	CTraceFilter Filter{ pLocal };
	CGameTrace Trace;

	GetInterfaces()->Trace->TraceRay(TraceRay, MASK_SHOT, &Filter, &Trace);
	if (Trace.HitGroup == 0 || Trace.HitGroup == HITGROUP_GEAR || Trace.Ent->Immune()) return;

	Cmd->Buttons |= IN_ATTACK;
}