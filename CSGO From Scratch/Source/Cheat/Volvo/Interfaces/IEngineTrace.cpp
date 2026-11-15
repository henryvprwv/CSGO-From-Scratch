#include <Volvo/Interfaces/IEngineTrace.h>
#include <Core/Interfaces/Interfaces.h>

// https://github.com/ValveSoftware/source-sdk-2013/blob/master/src/game/client/gametrace_client.cpp

bool CGameTrace::DidHitWorld() const
{
	auto EntityList = GetInterfaces()->EntityList;
	if (!EntityList) return false;

	return Ent == EntityList->GetClientEntity(0);
}

bool CGameTrace::DidHitNonWorldEntity() const
{
	return Ent != NULL && !DidHitWorld();
}

int CGameTrace::GetEntityIndex() const
{
	if (!Ent) return -1;

	return Ent->GetIndex();
}

