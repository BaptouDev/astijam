#pragma once

#include <raylib.h>
#include <cmath>

class Vector2f{
    public:
        float x;
        float y;
        Vector2f();
        Vector2f(float x, float y);
        float length_sq();
        float length();
        Vector2f normalized();
        Vector2f operator + (const Vector2f& other) const;
        Vector2f operator - (const Vector2f& other) const;
        Vector2f operator * (float scalar) const;
        friend Vector2f operator * (float scalar, const Vector2f& self);
        Vector2 to_rayvect2();
};