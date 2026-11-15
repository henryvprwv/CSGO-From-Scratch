#pragma once

#include <cmath>

struct Vector
{
	float X, Y, Z;

    Vector operator + (const Vector& Other) const
    {
        return { X + Other.X, Y + Other.Y, Z + Other.Z };
    }

    Vector operator - (const Vector& Other) const
    {
        return { X - Other.X, Y - Other.Y, Z - Other.Z };
    }

    Vector operator * (const Vector& Other) const
    {
        return { X * Other.X, Y * Other.Y, Z * Other.Z };
    }

    Vector operator * (float Scale) const
    {
        return { X * Scale, Y * Scale, Z * Scale };
    }

    Vector operator / (const Vector& Other) const
    {
        return { X / Other.X, Y / Other.Y, Z / Other.Z };
    }

    void Clamp()
    {
        while (X > 180.0f)  X -= 360.0f;
        while (X < -180.0f) X += 360.0f;

        while (Y > 180.0f)  Y -= 360.0f;
        while (Y < -180.0f) Y += 360.0f;
    }

    static void Subtract(const Vector& a, const Vector& b, Vector& c)
    {
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
        dst.X = src.X;
        dst.Y = src.Y;
        dst.Z = src.Z;
    }

    float LengthSqr() const
    {
        return (X * X + Y * Y + Z * Z);
    }

    static void AngleVectors(const Vector& Angles, Vector* Forward, Vector* Right = nullptr, Vector* Up = nullptr)
    {
        static constexpr float kDeg2Rad = 3.14159265358979323846f / 180.f;

        float sp = std::sin(Angles.X * kDeg2Rad), cp = std::cos(Angles.X * kDeg2Rad);
        float sy = std::sin(Angles.Y * kDeg2Rad), cy = std::cos(Angles.Y * kDeg2Rad);
        float sr = std::sin(Angles.Z * kDeg2Rad), cr = std::cos(Angles.Z * kDeg2Rad);

        if (Forward) *Forward = { cp * cy, cp * sy, -sp };
        if (Right) *Right = { -sr * sp * cy + cr * sy, -sr * sp * sy - cr * cy, -sr * cp };
        if (Up) *Up = { cr * sp * cy + sr * sy, cr * sp * sy - sr * cy, cr * cp };
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