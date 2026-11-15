#pragma once

#include <Volvo/Interfaces/IClientEntityList.h>
#include <Volvo/Interfaces/IBaseClientDLL.h>
#include <Volvo/Interfaces/ClientModeShared.h>
#include <Volvo/Interfaces/IVEngineClient.h>
#include <Volvo/Interfaces/IEngineTrace.h>

class Interfaces
{
public:
	bool Setup();

	IClientEntityList* EntityList = nullptr;
	IBaseClientDLL* Client = nullptr;
	ClientModeShared* ClientModeS = nullptr;
	IVEngineClient* Engine = nullptr;
	IEngineTrace* Trace = nullptr;
};

Interfaces* GetInterfaces();