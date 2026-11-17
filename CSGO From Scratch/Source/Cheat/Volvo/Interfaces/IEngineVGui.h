#pragma once

 // https://github.com/ValveSoftware/source-sdk-2013/blob/e1f1fd42271805072f052051c26c21caa2c87b04/src/public/ienginevgui.h#L26-L56

enum VGuiPanel_t
{
	PANEL_ROOT = 0,
	PANEL_GAMEUIDLL,  // the console, game menu
	PANEL_CLIENTDLL,
	PANEL_TOOLS,
	PANEL_INGAMESCREENS,
	PANEL_GAMEDLL,
	PANEL_CLIENTDLL_TOOLS,
	PANEL_GAMEUIBACKGROUND, // the console background, shows under all other stuff in 3d engine view
	PANEL_TRANSITIONEFFECT,
	PANEL_STEAMOVERLAY,
};

class IEngineVGui
{
public:
	virtual			~IEngineVGui(void) {}

	virtual int		GetPanel(VGuiPanel_t type) = 0;

	virtual bool	sGameUIVisible() = 0;

	virtual void	ActivateGameUI() = 0;
};
