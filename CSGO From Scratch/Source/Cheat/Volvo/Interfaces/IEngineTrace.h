#pragma once

#include <cstddef>
#include <cstdint>

#include <Utility/Memory/Memory.h>
#include <Volvo/Classes/CEntity.h>
#include <Volvo/Classes/Vector.h>
#include <Volvo/Classes/Matrix3x4.h>
#include <Volvo/Classes/bspflags.h>

#define  Assert( _exp )	((void)0)

// https://github.com/ValveSoftware/source-sdk-2013/blob/e1f1fd42271805072f052051c26c21caa2c87b04/src/public/engine/IEngineTrace.h#L33-L46

enum TraceType_t : std::int32_t
{
	TRACE_EVERYTHING = 0,
	TRACE_WORLD_ONLY,				// NOTE: This does *not* test static props!!!
	TRACE_ENTITIES_ONLY,			// NOTE: This version will *not* test static props
	TRACE_EVERYTHING_FILTER_PROPS,	// NOTE: This version will pass the IHandleEntity for props through the filter, unlike all other filters
};

class ITraceFilter
{
public:
	virtual bool ShouldHitEntity(CEntity* pEntity, int contentsMask) = 0;
	virtual TraceType_t	GetTraceType() const = 0;
};


//https://github.com/ValveSoftware/source-sdk-2013/blob/e1f1fd42271805072f052051c26c21caa2c87b04/src/public/engine/IEngineTrace.h#L89-L100

class CTraceFilter : public ITraceFilter
{
public:
	CTraceFilter(CEntity* Entity) noexcept : SkipEntity(Entity) {}

	bool ShouldHitEntity(CEntity* Entity, std::int32_t ContentsMask) override
	{
		return Entity != this->SkipEntity;
	}

	TraceType_t GetTraceType() const override
	{
		return TRACE_EVERYTHING;
	}

private:
	const CEntity* SkipEntity;
};

// https://github.com/ValveSoftware/source-sdk-2013/blob/e1f1fd42271805072f052051c26c21caa2c87b04/src/public/mathlib/mathlib.h#L147-L162

struct cplane_t
{
	Vector Normal;
	float Dist;
	unsigned char Type;			// for fast side tests
	unsigned char Signbits;		// signx + (signy<<1) + (signz<<1)
	unsigned char pad[2];
};

// https://github.com/ValveSoftware/source-sdk-2013/blob/e1f1fd42271805072f052051c26c21caa2c87b04/src/public/cmodel.h#L50-L55
struct csurface_t
{
	const char* Name;
	short		SurfaceProps;
	unsigned short	Flags;		// BUGBUG: These are declared per surface, not per material, but this database is per-material now
};

struct Ray
{
	VectorAligned Start;		// starting point, centered within the extents
	VectorAligned Delta;		// direction + length of the ray
	VectorAligned StartOffset;	// Add this to Start to get the actual ray start
	VectorAligned Extents;		// Describes an axis aligned box extruded along a ray
	const matrix3x4_t* WorldAxisTransform;
	bool IsRay;		// are the extents zero?
	bool IsSwept;	// is delta != 0?

	Ray() : WorldAxisTransform(NULL) {}

	void Init(Vector const& start, Vector const& end)
	{
		Assert(&end);
		Vector::Subtract(end, start, Delta);

		IsSwept = (Delta.LengthSqr() != 0);

		Vector::Clear(Extents);
		WorldAxisTransform = NULL;
		IsRay = true;

		// Offset Start to be in the center of the box...
		Vector::Clear(StartOffset);
		Vector::Copy(start, Start);
	}
};

// https://github.com/ValveSoftware/source-sdk-2013/blob/e1f1fd42271805072f052051c26c21caa2c87b04/src/public/trace.h#L47-L67

class CBaseTrace
{
public:
	// these members are aligned!!
	Vector			StartPos;				// start position
	Vector			EndPos;					// final position
	cplane_t		Plane;					// surface normal at impact

	float			Fraction;				// time completed, 1.0 = didn't hit anything

	int				Contents;				// contents on other side of surface hit
	unsigned short	DispFlags;				// displacement flags for marking surfaces with data

	bool			AllSolid;				// if true, plane is not valid
	bool			StartSolid;				// if true, the initial point was in a solid area

	CBaseTrace() {}

private:
	// No copy constructors allowed
	CBaseTrace(const CBaseTrace& vOther);
};

// https://github.com/ValveSoftware/source-sdk-2013/blob/e1f1fd42271805072f052051c26c21caa2c87b04/src/public/gametrace.h#L30-L80

class CGameTrace : public CBaseTrace
{
public:
	// Returns true if m_pEnt points at the world entity.
	bool DidHitWorld() const;

	// Returns true if we hit something and it wasn't the world.
	bool DidHitNonWorldEntity() const;

	// Gets the entity's network index if the trace has hit an entity. If not, returns -1.
	int GetEntityIndex() const;

	// Returns true if there was any kind of impact at all
	bool DidHit() const
	{
		return Fraction < 1.0f || AllSolid || StartSolid;
	}

public:
	float			FractionLeftSolid;	// time we left a solid, only valid if we started in solid
	csurface_t		Surface;			// surface hit (impact surface)

	int				HitGroup;			// 0 == generic, non-zero is specific body part

	short			PhysicsBone;		// physics bone hit by trace in studio
	unsigned short	WorldSurfaceIndex;	// Index of the msurface2_t, if applicable

	CEntity* Ent;

	int				Hitbox;				// box hit by trace in studio

	CGameTrace() : Ent(NULL) {}

private:
	// No copy constructors allowed
	CGameTrace(const CGameTrace& vOther);
};

// https://github.com/ValveSoftware/source-sdk-2013/blob/e1f1fd42271805072f052051c26c21caa2c87b04/src/public/engine/IEngineTrace.h#L148

class IEngineTrace
{
public:
	void TraceRay(const Ray& InRay, unsigned int Mask, ITraceFilter* Filter, CGameTrace* OutTrace) noexcept
	{
		GetMemory()->Call<void>(this, 5, &InRay, Mask, Filter, OutTrace);
	}
};
