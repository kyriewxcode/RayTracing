#pragma once
#include <math.h>
#include <stdlib.h>
#include <iostream>

class Vec3
{
public:
    Vec3() {}
    Vec3(float e0, float e1, float e2)
    {
        e[0] = e0;
        e[1] = e1;
        e[2] = e2;
    }

    inline float x() const { return e[0]; }
    inline float y() const { return e[1]; }
    inline float z() const { return e[2]; }
    inline float r() const { return e[0]; }
    inline float g() const { return e[1]; }
    inline float b() const { return e[0]; }
    inline static Vec3 zero() { return Vec3(0, 0, 0); }
    inline static Vec3 one() { return Vec3(1, 1, 1); }
    inline static Vec3 up() { return Vec3(0, 1, 0); }
    inline static Vec3 forward() { return Vec3(0, 0, 1); }
    inline static Vec3 horizontal() { return Vec3(1, 0, 0); }

    inline const Vec3& operator+() const { return *this; }
    inline Vec3 operator-() const { return Vec3(-e[0], -e[1], -e[2]); }
    inline float operator[](int i) const { return e[i]; }
    inline float& operator[](int i) { return e[i]; }

    inline Vec3& operator+=(const Vec3& v2);
    inline Vec3& operator-=(const Vec3& v2);
    inline Vec3& operator*=(const Vec3& v2);
    inline Vec3& operator/=(const Vec3& v2);
    inline Vec3& operator*=(const float time);
    inline Vec3& operator/=(const float time);

    inline float length() const { return sqrt(e[0] * e[0] + e[1] * e[1] + e[2] * e[2]); }
    inline float squared_length() const { return e[0] * e[0] + e[1] * e[1] + e[2] * e[2]; }
    inline void normalized();

    float e[3] {};
};

inline std::istream& operator>>(std::istream& is, Vec3& time)
{
    is >> time.e[0] >> time.e[1] >> time.e[2];
    return is;
}

inline std::ostream& operator<<(std::ostream& os, Vec3& time)
{
    os << time.e[0] << " " << time.e[1] << " " << time.e[2];
    return os;
}

inline void Vec3::normalized()
{
    float k = 1.0 / this->length();
    e[0] *= k;
    e[1] *= k;
    e[2] *= k;
}

inline Vec3 operator+(const Vec3& v1, const Vec3& v2)
{
    return Vec3(v1.e[0] + v2.e[0], v1.e[1] + v2.e[1], v1.e[2] + v2.e[2]);
}

inline Vec3 operator-(const Vec3& v1, const Vec3& v2)
{
    return Vec3(v1.e[0] - v2.e[0], v1.e[1] - v2.e[1], v1.e[2] - v2.e[2]);
}

inline Vec3 operator*(const Vec3& v1, const Vec3& v2)
{
    return Vec3(v1.e[0] * v2.e[0], v1.e[1] * v2.e[1], v1.e[2] * v2.e[2]);
}

inline Vec3 operator/(const Vec3& v1, const Vec3& v2)
{
    return Vec3(v1.e[0] / v2.e[0], v1.e[1] / v2.e[1], v1.e[2] / v2.e[2]);
}

inline Vec3 operator*(float time, const Vec3& v)
{
    return Vec3(time * v.e[0], time * v.e[1], time * v.e[2]);
}

inline Vec3 operator*(const Vec3& v, float time)
{
    return Vec3(time * v.e[0], time * v.e[1], time * v.e[2]);
}

inline Vec3 operator/(const Vec3& v, float time)
{
    return Vec3(v.e[0] / time, v.e[1] / time, v.e[2] / time);
}

inline float dot(const Vec3& v1, const Vec3& v2)
{
    return v1.e[0] * v2.e[0] + v1.e[1] * v2.e[1] + v1.e[2] * v2.e[2];
}

inline Vec3 cross(const Vec3& v1, const Vec3& v2)
{
    return Vec3(
    (v1.e[1] * v2.e[2] - v1.e[1] * v2.e[1]),
    -(v1.e[0] * v2.e[2] - v1.e[2] * v2.e[0]),
    (v1.e[0] * v2.e[1] - v1.e[1] * v2.e[0]));
}

inline Vec3& Vec3::operator+=(const Vec3& v)
{
    e[0] += v.e[0];
    e[1] += v.e[1];
    e[2] += v.e[2];
    return *this;
}

inline Vec3& Vec3::operator*=(const Vec3& v)
{
    e[0] *= v.e[0];
    e[1] *= v.e[1];
    e[2] *= v.e[2];
    return *this;
}

inline Vec3& Vec3::operator/=(const Vec3& v)
{
    e[0] /= v.e[0];
    e[1] /= v.e[1];
    e[2] /= v.e[2];
    return *this;
}

inline Vec3& Vec3::operator-=(const Vec3& v)
{
    e[0] -= v.e[0];
    e[1] -= v.e[1];
    e[2] -= v.e[2];
    return *this;
}

inline Vec3& Vec3::operator*=(const float time)
{
    e[0] *= time;
    e[1] *= time;
    e[2] *= time;
    return *this;
}

inline Vec3& Vec3::operator/=(const float time)
{
    float k = 1.0f / time;

    e[0] *= k;
    e[1] *= k;
    e[2] *= k;
    return *this;
}

inline Vec3 normalize(const Vec3& v)
{
    return v / v.length();
}