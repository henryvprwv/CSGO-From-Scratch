#pragma once

class CUserCmd;

class Aim
{
public:
	void OnCreateMove(CUserCmd* Cmd);
private:
	void TriggerBot(CUserCmd* Cmd);
	void AimBot(CUserCmd* Cmd);
};

Aim* GetAim();