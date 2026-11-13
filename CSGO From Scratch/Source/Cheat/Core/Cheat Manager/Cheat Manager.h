#pragma once

class CUserCmd;

class CheatManager
{
public:
	bool OnInit();
	void OnShutdown();
	void OnCreateMove(CUserCmd* Cmd);
};

CheatManager* GetCheatManager();