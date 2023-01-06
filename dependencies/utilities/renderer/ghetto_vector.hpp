#pragma once

#include <sstream>

#define DEG(a)	   a * 57.295779513082

#define CHECK_VALID( _v ) 0

#define ZERO Vector(0.0f, 0.0f, 0.0f)

class Vector {
public:
    Vector(void)     {
        Invalidate();
    }
    Vector(float X, float Y, float Z)     {
        x = X;
        y = Y;
        z = Z;
    }
    Vector(const float* clr)     {
        x = clr[0];
        y = clr[1];
        z = clr[2];
    }

    void Init(float ix = 0.0f, float iy = 0.0f, float iz = 0.0f)     {
        x = ix; y = iy; z = iz;
    }
    bool IsValid() const     {
        return std::isfinite(x) && std::isfinite(y) && std::isfinite(z);
    }
    void Invalidate()     {
        x = y = z = std::numeric_limits<float>::infinity();
    }

    float& operator[](int i)     {
        return ((float*)this)[i];
    }
    float operator[](int i) const     {
        return ((float*)this)[i];
    }

    void Zero()     {
        x = y = z = 0.0f;
    }

    bool operator==(const Vector& src) const     {
        return (src.x == x) && (src.y == y) && (src.z == z);
    }
    bool operator!=(const Vector& src) const     {
        return (src.x != x) || (src.y != y) || (src.z != z);
    }

    inline void VectorSubtract(const Vector& a, Vector& b, Vector& c)     {
        CHECK_VALID(a);
        CHECK_VALID(b);
        c.x = a.x - b.x;
        c.y = a.y - b.y;
        c.z = a.z - b.z;
    }

    Vector& operator+=(const Vector& v)     {
        x += v.x; y += v.y; z += v.z;
        return *this;
    }
    Vector& operator-=(const Vector& v)     {
        x -= v.x; y -= v.y; z -= v.z;
        return *this;
    }
    Vector& operator*=(float fl)     {
        x *= fl;
        y *= fl;
        z *= fl;
        return *this;
    }
    Vector& operator*=(const Vector& v)     {
        x *= v.x;
        y *= v.y;
        z *= v.z;
        return *this;
    }
    Vector& operator/=(const Vector& v)     {
        x /= v.x;
        y /= v.y;
        z /= v.z;
        return *this;
    }
    Vector& operator+=(float fl)     {
        x += fl;
        y += fl;
        z += fl;
        return *this;
    }
    Vector& operator/=(float fl)     {
        x /= fl;
        y /= fl;
        z /= fl;
        return *this;
    }
    Vector& operator-=(float fl)     {
        x -= fl;
        y -= fl;
        z -= fl;
        return *this;
    }

    void NormalizeInPlace()     {
        *this = Normalized();
    }
    Vector Normalized() const     {
        Vector res = *this;
        float l = res.Length();
        if (l != 0.0f) {
            res /= l;
        }
        else {
            res.x = res.y = res.z = 0.0f;
        }
        return res;
    }

    Vector Normalize()     {
        Vector vector;
        float length = this->Length();

        if (length != 0)         {
            vector.x = x / length;
            vector.y = y / length;
            vector.z = z / length;
        }
        else         {
            vector.x = vector.y = 0.0f; vector.z = 1.0f;
        }

        return vector;

    }

    float DistTo(const Vector& vOther) const     {
        Vector delta;

        delta.x = x - vOther.x;
        delta.y = y - vOther.y;
        delta.z = z - vOther.z;

        return delta.Length();
    }
    float DistToSqr(const Vector& vOther) const     {
        Vector delta;

        delta.x = x - vOther.x;
        delta.y = y - vOther.y;
        delta.z = z - vOther.z;

        return delta.LengthSqr();
    }
    float Dot(const Vector& vOther) const     {
        return (x * vOther.x + y * vOther.y + z * vOther.z);
    }
    float Length() const     {
        return sqrt(x * x + y * y + z * z);
    }
    float LengthSqr(void) const     {
        return (x * x + y * y + z * z);
    }
    float Length2D() const     {
        return sqrt(x * x + y * y);
    }
    Vector Cross(const Vector& vOther) const     {
        return Vector(y * z - z * vOther.y, z * vOther.x - x * vOther.z, x * vOther.y - y * vOther.x);
    }
    Vector& operator=(const Vector& vOther)     {
        x = vOther.x; y = vOther.y; z = vOther.z;
        return *this;
    }

    bool IsZero(float tolerance = 0.01f) {
        return (x > -tolerance && x < tolerance&&
            y > -tolerance && y < tolerance&&
            z > -tolerance && z < tolerance);
    }
    inline Vector Angle(Vector* up = 0) {
        if (!x && !y)
            return Vector(0, 0, 0);

        double roll = 0;

        if (up) {
            Vector left = (*up).Cross(*this);
            roll = DEG(atan2f(left.z, (left.y * x) - (left.x * y)));
        }
        return Vector((float)(DEG(atan2f(-z, sqrtf(x * x + y * y)))), (float)(DEG(atan2f(y, x))), (float)roll);
    }

    float x, y, z;
};


