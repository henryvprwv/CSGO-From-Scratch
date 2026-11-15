#include "Interfaces.h"

#include <Windows.h>

Interfaces* GetInterfaces()
{
	static Interfaces GInterfaces{};
	return &GInterfaces;
}

//https://github.com/ValveSoftware/source-sdk-2013/blob/e1f1fd42271805072f052051c26c21caa2c87b04/src/public/tier1/interface.h#L62-L68

template <typename T>
T* GetInterface(const char* InterfaceName, const char* ModuleName)
{
	const auto Handle = GetModuleHandleA(ModuleName);

	if (!Handle) return nullptr;

	const auto FunctionAddress = GetProcAddress(Handle, "CreateInterface");

	if (!FunctionAddress) return nullptr;

	using CreateInterfaceFn = T* (*)(const char*, int*);
	const auto CreateInterface = reinterpret_cast<CreateInterfaceFn>(FunctionAddress);

	return CreateInterface(InterfaceName, nullptr);
}

bool Interfaces::Setup()
{
	EntityList = GetInterface<IClientEntityList>("VClientEntityList003", "client.dll");
	if (!EntityList) return false;

	Client = GetInterface<IBaseClientDLL>("VClient018", "client.dll");
	if (!Client) return false;

	/*
	https://github.com/ValveSoftware/source-sdk-2013/blob/e1f1fd42271805072f052051c26c21caa2c87b04/src/game/client/cdll_client_int.cpp#L627
	https://github.com/ValveSoftware/source-sdk-2013/blob/e1f1fd42271805072f052051c26c21caa2c87b04/src/game/client/cdll_client_int.cpp#L1285-L1288

	.text:10260730                   HudProcessInput proc near               ; DATA XREF: .rdata:10BBF94C↓o
	.text:10260730 55                                push    ebp
	.text:10260731 8B EC                             mov     ebp, esp
	.text:10260733 8B 0D 70 11 2C 15                 mov     ecx, dword_152C1170 // 5 bytes are before the 4 byte ptr
	.text:10260739 8B 01                             mov     eax, [ecx]
	.text:1026073B 5D                                pop     ebp
	.text:1026073C FF 60 30                          jmp     dword ptr [eax+30h]
	.text:1026073C                   HudProcessInput endp
	*/																							
	//																^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	//															    10th index in the CHLClient interface + 5 bytes into that fn is our ClientModeShared ptr
	ClientModeS = **reinterpret_cast<ClientModeShared***>((*reinterpret_cast<unsigned int**>(Client))[10] + 5);

	Engine = GetInterface<IVEngineClient>("VEngineClient014", "engine.dll");
	if (!Engine) return false;

	Trace = GetInterface<IEngineTrace>("EngineTraceClient004", "engine.dll");
	if (!Trace) return false;

	return true;
}
