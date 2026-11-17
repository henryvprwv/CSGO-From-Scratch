#pragma once

class CUserCmd;

class CheatManager
{
public:
	bool OnInit();
	void OnShutdown();
	void OnCreateMove(CUserCmd* Cmd);
	void OnPaintTraverse(int VGUIPannel);
};

CheatManager* GetCheatManager();