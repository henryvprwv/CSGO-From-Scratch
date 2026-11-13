#include "Cheat Manager.h"

#include <cstdio>
#include <iostream>

#include <MinHook/Include/MinHook.h>
#include <Core/Interfaces/Interfaces.h>
#include <Core/Hooks/HookManager.h>
#include <Core/NetVars/NetVars.h>
#include <Volvo/Classes/CEntity.h>

#include <Features/Movement/Movement.h>

CheatManager* GetCheatManager()
{
	static CheatManager GCheatManager{};
	return &GCheatManager;
}

bool CheatManager::OnInit()
{
	if (MH_Initialize() != MH_OK) return false;

	if (!AllocConsole()) return false;
	SetConsoleTitleA("Hi");
	FILE* Stream = nullptr;
	freopen_s(&Stream, "CONOUT$", "w", stdout);
	freopen_s(&Stream, "CONOUT$", "w", stderr);
	freopen_s(&Stream, "CONIN$", "r", stdin);

	if (!GetInterfaces()->Setup()) return false;
	GetNetVars()->Setup();
	if (!GetHookManager()->OnInit()) return false;

	return true;
}

void CheatManager::OnShutdown()
{
	GetHookManager()->OnShutdown();

	fclose(stdin);
	fclose(stdout);
	fclose(stderr);
	FreeConsole();
}

void CheatManager::OnCreateMove(CUserCmd* Cmd)
{
	auto pLocal = CEntity::GetLocalPlayer();

	if (pLocal->GetHealth() >= 1)
	{
		GetMovement()->OnCreateMove(Cmd);
	}
}