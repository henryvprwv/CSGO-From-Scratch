#include "HookManager.h"

#include <Core/Interfaces/Interfaces.h>
#include <Utility/Memory/Memory.h>

#include "Hooks/CreateMove.h"
#include "Hooks/PaintTraverse.h"
#include <iostream>

HookManager* GetHookManager()
{
	static HookManager GHookManager{};
	return &GHookManager;
}

bool HookManager::OnInit()
{
    Hooks = {
        {"CreateMove", GetMemory()->Get(GetInterfaces()->ClientModeS, 24), reinterpret_cast<void*>(&CreateMoveHook), reinterpret_cast<void**>(&CreateMoveOriginal)},
        {"PaintTraverse", GetMemory()->Get(GetInterfaces()->Panel, 41), reinterpret_cast<void*>(&PaintTraverseHook), reinterpret_cast<void**>(&PaintTraverseOriginal)}
    };

    for (auto& Hook : Hooks)
    {
        if (!Hook.Target) return false;

        MH_STATUS Result = MH_CreateHook(Hook.Target, Hook.Detour, Hook.Original);
        if (Result != MH_OK) return false;

        Result = MH_EnableHook(Hook.Target);
        if (Result != MH_OK) return false;

        std::cout << "[Hooks] " << Hook.Name << " Success!\n";
    }
    return true;
}

void HookManager::OnShutdown()
{
	MH_DisableHook(MH_ALL_HOOKS);
	MH_RemoveHook(MH_ALL_HOOKS);
	MH_Uninitialize();
}