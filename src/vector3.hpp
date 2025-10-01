#ifndef VECTOR3_HPP
#define VECTOR3_HPP

#include <cmath>

class Vector3 {
public:
    double x, y, z;

    Vector3() : x(0), y(0), z(0) {}
    Vector3(double x, double y, double z) : x(x), y(y), z(z) {}

    Vector3 operator+(const Vector3& v) const {
        return Vector3(x + v.x, y + v.y, z + v.z);
    }

    Vector3 operator-(const Vector3& v) const {
        return Vector3(x - v.x, y - v.y, z - v.z);
    }

    Vector3 operator*(double t) const {
        return Vector3(x * t, y * t, z * t);
    }

    Vector3 operator/(double t) const {
        return Vector3(x / t, y / t, z / t);
    }

    double dot(const Vector3& v) const {
        return x * v.x + y * v.y + z * v.z;
    }

    Vector3 cross(const Vector3& v) const {
        return Vector3(y * v.z - z * v.y,
                      z * v.x - x * v.z,
                      x * v.y - y * v.x);
    }

    double length() const {
        return std::sqrt(dot(*this));
    }

    Vector3 normalize() const {
        return *this / length();
    }
};

#endif