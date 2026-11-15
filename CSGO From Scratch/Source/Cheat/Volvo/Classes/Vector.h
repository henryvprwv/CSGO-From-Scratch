#pragma once

#define CHECK_VALID( _v)	0

struct Vector
{
	float X, Y, Z;

    void Clamp()
    {
        while (X > 180.0f)  X -= 360.0f;
        while (X < -180.0f) X += 360.0f;

        while (Y > 180.0f)  Y -= 360.0f;
        while (Y < -180.0f) Y += 360.0f;
    }

    static void Subtract(const Vector& a, const Vector& b, Vector& c)
    {
        CHECK_VALID(a);
        CHECK_VALID(b);
        c.X = a.X - b.X;
        c.Y = a.Y - b.Y;
        c.Z = a.Z - b.Z;
    }

    static void Clear(Vector& a)
    {
        a.X = a.Y = a.Z = 0.0f;
    }

    static void Copy(const Vector& src, Vector& dst)
    {
        CHECK_VALID(src);
        dst.X = src.X;
        dst.Y = src.Y;
        dst.Z = src.Z;
    }

    float LengthSqr() const
    {
        CHECK_VALID(*this);
        return (X * X + Y * Y + Z * Z);
    }
};

// https://github.com/ValveSoftware/source-sdk-2013/blob/e1f1fd42271805072f052051c26c21caa2c87b04/src/public/mathlib/vector.h#L377-L408

struct alignas(16) VectorAligned : Vector
{
    VectorAligned() = default;
    VectorAligned(const Vector& Other) : Vector(Other) {}

    VectorAligned& operator=(const Vector& Other)
    {
        X = Other.X;
        Y = Other.Y;
        Z = Other.Z;
        return *this;
    }
};

static_assert(sizeof(VectorAligned) == 16, "VectorAligned must match the engine layout");
static_assert(alignof(VectorAligned) == 16, "VectorAligned must be 16-byte aligned");