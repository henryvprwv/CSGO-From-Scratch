#pragma once

#include "Vector.h"

//https://github.com/ValveSoftware/source-sdk-2013/blob/e1f1fd42271805072f052051c26c21caa2c87b04/src/game/shared/in_buttons.h

enum ButtonStates
{			      //2^X
	IN_ATTACK    = (1 << 0),
	IN_JUMP      = (1 << 1),
	IN_DUCK      = (1 << 2),
	IN_FORWARD   = (1 << 3),
	IN_BACK      = (1 << 4),
	IN_USE       = (1 << 5),
	IN_CANCEL    = (1 << 6),
	IN_LEFT      = (1 << 7),
	IN_RIGHT     = (1 << 8),
	IN_MOVELEFT  = (1 << 9),
	IN_MOVERIGHT = (1 << 10),
	IN_ATTACK2   = (1 << 11),
	IN_RUN       = (1 << 12),
	IN_RELOAD    = (1 << 13),
	IN_ALT1      = (1 << 14),
	IN_ALT2      = (1 << 15),
	IN_SCORE     = (1 << 16),
	IN_SPEED     = (1 << 17),
	IN_WALK      = (1 << 18),
	IN_ZOOM      = (1 << 19),
	IN_WEAPON1   = (1 << 20),
	IN_WEAPON2   = (1 << 21),
	IN_BULLRUSH  = (1 << 22),
	IN_GRENADE1  = (1 << 23),
	IN_GRENADE2  = (1 << 24),
	IN_ATTACK3   = (1 << 25)
};

//https://github.com/perilouswithadollarsign/cstrike15_src/blob/f82112a2388b841d72cb62ca48ab1846dfcc11c8/game/shared/usercmd.h#L250-L283

class CUserCmd
{
public:
	void* VMT;
	int		CommandNumber;
	int		TickCount;
	Vector	ViewAngles;
	Vector	AimDirection;
	float	ForwardMove;
	float	SideMode; //aka LeftMove
	float	UpMove;
	int		Buttons;
	char    Impulse;
	int		WeaponSelect;
	int		WeaponSubtype;
	int		RandomSeed;
	short	MouseDX;		
	short	MouseDY;		
	bool	HasBeenPredicted; //at least once this tick
};