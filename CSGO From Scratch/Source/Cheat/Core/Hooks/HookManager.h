#pragma once

#include <MinHook/Include/MinHook.h>
#include <initializer_list>
#include <vector>

struct HookData
{
	const char* Name;
	LPVOID Target, Detour;
	LPVOID* Original;
};

class HookManager
{
public:
	bool OnInit();
	void OnShutdown();

private:
	std::vector<HookData> Hooks;
};

HookManager* GetHookManager();