#if !defined(VEC_H)
#define VEC_H

#include <string>

class Vector2
{
private:
    float x, y;
public:
    Vector2(float x, float y): x(x), y(y) {};
    
    Vector2 operator+(const Vector2 &v) const {
        return Vector2(x+v.x, y+v.y);
    }
    Vector2 operator*(float v) const {
        return Vector2(x*v, y*v);
    }
    Vector2& operator+=(const Vector2 &v) {
        x += v.x;
        y += v.y;
        return *this;
    }
    Vector2& operator*=(float v) {
        x *= v;
        y *= v;
        return *this;
    }
    Vector2 operator-() const {
        return Vector2(-x, -y);
    }
    friend Vector2 operator*(float f, const Vector2 &v) {
        return Vector2(f*v.x, f*v.y);
    }

    std::string toString() const {
        return "[" + std::to_string(x) + ", " +
               std::to_string(y) + "]";
    }
};

#endif // VEC_H
