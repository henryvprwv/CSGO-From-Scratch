#pragma once
#include <cstdint>

#include <Core/NetVars/NetVars.h>
#include <Utility/Memory/Memory.h>
#include <Volvo/Classes/Vector.h>

class CEntity
{
public:
	NETVAR(GetMoveType, "C_BaseEntity->m_MoveType", int);
	NETVAR(GetFlags, "CBasePlayer->m_fFlags", int);
	NETVAR(Immune, "CCSPlayer->m_bGunGameImmunity", bool);

	bool IsAlive()
	{
		return GetHealth() > 0;
	}

	constexpr std::int32_t GetIndex() noexcept
	{
		return GetMemory()->Call<std::int32_t>(this + 0x8, 10);
	}

	const Vector& GetAbsOrigin() noexcept
	{
		return GetMemory()->Call<const Vector&>(this, 10);
	}

	std::int32_t GetHealth() noexcept
	{
		return GetMemory()->Call<std::int32_t>(this, 122);
	}

	Vector GetEyePosition() noexcept
	{
		Vector EyePosition;
		GetMemory()->Call<void>(this, 285, &EyePosition);
		return EyePosition;
	}

	static CEntity* GetLocalPlayer() noexcept;
};

// https://github.com/ValveSoftware/source-sdk-2013/blob/e1f1fd42271805072f052051c26c21caa2c87b04/src/public/const.h#L192-L211
enum MoveType_t
{
	MOVETYPE_NONE = 0,			// never moves
	MOVETYPE_ISOMETRIC,			// For players -- in TF2 commander view, etc.
	MOVETYPE_WALK,				// Player only - moving on the ground
	MOVETYPE_STEP,				// gravity, special edge handling -- monsters use this
	MOVETYPE_FLY,				// No gravity, but still collides with stuff
	MOVETYPE_FLYGRAVITY,		// flies through the air + is affected by gravity
	MOVETYPE_VPHYSICS,			// uses VPHYSICS for simulation
	MOVETYPE_PUSH,				// no clip to world, push and crush
	MOVETYPE_NOCLIP,			// No gravity, no collisions, still do velocity/avelocity
	MOVETYPE_LADDER,			// Used by players only when going onto a ladder
	MOVETYPE_OBSERVER,			// Observer movement, depends on player's observer mode
	MOVETYPE_CUSTOM,			// Allows the entity to describe its own physics

	// should always be defined as the last item in the list
	MOVETYPE_LAST = MOVETYPE_CUSTOM,

	MOVETYPE_MAX_BITS = 4
};

//https://github.com/ValveSoftware/source-sdk-2013/blob/e1f1fd42271805072f052051c26c21caa2c87b04/src/public/const.h
enum EFlags : std::int32_t
{
	FL_ONGROUND = (1 << 0),
	FL_DUCKING = (1 << 1),
	FL_ANIMDUCKING = (1 << 2),
	FL_WATERJUMP = (1 << 3),
	FL_ONTRAIN = (1 << 4),
	FL_INRAIN = (1 << 5),
	FL_FROZEN = (1 << 6),
	FL_ATCONTROLS = (1 << 7),
	FL_CLIENT = (1 << 8),
	FL_FAKECLIENT = (1 << 9),
	FL_INWATER = (1 << 10),
	FL_FLY = (1 << 11),
	FL_SWIM = (1 << 12),
	FL_CONVEYOR = (1 << 13),
	FL_NPC = (1 << 14),
	FL_GODMODE = (1 << 15),
	FL_NOTARGET = (1 << 16),
	FL_AIMTARGET = (1 << 17),
	FL_PARTIALGROUND = (1 << 18),
	FL_STATICPROP = (1 << 19),
	FL_GRAPHED = (1 << 20),
	FL_GRENADE = (1 << 21),
	FL_STEPMOVEMENT = (1 << 22),
	FL_DONTTOUCH = (1 << 23),
	FL_BASEVELOCITY = (1 << 24),
	FL_WORLDBRUSH = (1 << 25),
	FL_OBJECT = (1 << 26),
	FL_KILLME = (1 << 27),
	FL_ONFIRE = (1 << 28),
	FL_DISSOLVING = (1 << 29),
	FL_TRANSRAGDOLL = (1 << 30),
	FL_UNBLOCKABLE_BY_PLAYER = (1 << 31)
};

//https://github.com/RileyKun/cstrike15_src-2019/blob/a4c7aaea259319aca272839f688a3f4d9fe1cb2c/game/shared/cstrike15/cs_weapon_id.h#L28-L49
enum CSWeaponType
{
	WEAPONTYPE_KNIFE = 0,
	WEAPONTYPE_PISTOL,
	WEAPONTYPE_SUBMACHINEGUN,
	WEAPONTYPE_RIFLE,
	WEAPONTYPE_SHOTGUN,
	WEAPONTYPE_SNIPER_RIFLE,
	WEAPONTYPE_MACHINEGUN,
	WEAPONTYPE_C4,
	WEAPONTYPE_TASER,
	WEAPONTYPE_GRENADE,
	WEAPONTYPE_EQUIPMENT,
	WEAPONTYPE_STACKABLEITEM,

	WEAPONTYPE_FISTS,
	WEAPONTYPE_BREACHCHARGE,
	WEAPONTYPE_TABLET,
	WEAPONTYPE_MELEE,

	WEAPONTYPE_UNKNOWN
};

// https://github.com/RileyKun/cstrike15_src-2019/blob/a4c7aaea259319aca272839f688a3f4d9fe1cb2c/public/cdll_int.h#L134-L159

typedef struct PlayerInfoS
{
	// version for future compatibility
	std::uint64_t	version;
	// network xuid
	std::uint64_t	XUID;
	// scoreboard information
	char			Name[128];
	// local server user ID, unique while server is running
	int				UserID;
	// global unique player identifer
	char			Guid[33];
	// friends identification number
	std::uint32_t	FriendsID;
	// friends name
	char			FriendsName[128];
	// true, if player is a bot controlled by game.dll
	bool			FakePlayer;
	// true if player is the HLTV proxy
	bool			IsHLTV;
	// custom files CRC for this player
	std::uint32_t	CustomFiles[4];
	// this counter increases each time the server downloaded a new file
	unsigned char	FilesDownloaded;
} PlayerInfo;

enum HitGroup
{
	HITGROUP_GENERIC,
	HITGROUP_HEAD,
	HITGROUP_CHEST,
	HITGROUP_STOMACH,
	HITGROUP_LEFTARM,
	HITGROUP_RIGHTARM,
	HITGROUP_LEFTLEG,
	HITGROUP_RIGHTLEG,
	HITGROUP_NECK,
	HITGROUP_GEAR = 10
};