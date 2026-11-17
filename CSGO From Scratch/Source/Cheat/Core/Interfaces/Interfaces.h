#pragma once

#include <Volvo/Interfaces/IClientEntityList.h>
#include <Volvo/Interfaces/IBaseClientDLL.h>
#include <Volvo/Interfaces/ClientModeShared.h>
#include <Volvo/Interfaces/IVEngineClient.h>
#include <Volvo/Interfaces/IEngineTrace.h>
#include <Volvo/Interfaces/ISurface.h>
#include <Volvo/Interfaces/IVDebugOverlay.h>
#include <Volvo/Interfaces/IPanel.h>
#include <Volvo/Interfaces/IEngineVGui.h>

class Interfaces
{
public:
	bool Setup();

	IClientEntityList* EntityList = nullptr;
	IBaseClientDLL* Client = nullptr;
	ClientModeShared* ClientModeS = nullptr;
	IVEngineClient* Engine = nullptr;
	IEngineTrace* Trace = nullptr;
	ISurface* Surface = nullptr;
	IVDebugOverlay* DebugOverlay = nullptr;
	IPanel* Panel = nullptr;
	IEngineVGui* EngineVGUI = nullptr;
};

Interfaces* GetInterfaces();