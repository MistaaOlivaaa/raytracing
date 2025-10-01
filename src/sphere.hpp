#ifndef SPHERE_HPP
#define SPHERE_HPP

#include "vector3.hpp"
#include "ray.hpp"

class Sphere {
public:
    Vector3 center;
    double radius;
    Vector3 color;

    Sphere(const Vector3& center, double radius, const Vector3& color)
        : center(center), radius(radius), color(color) {}

    bool intersect(const Ray& ray, double& t) const {
        Vector3 oc = ray.origin - center;
        double a = ray.direction.dot(ray.direction);
        double b = 2.0 * oc.dot(ray.direction);
        double c = oc.dot(oc) - radius * radius;
        double discriminant = b * b - 4 * a * c;

        if (discriminant < 0) {
            return false;
        }

        t = (-b - std::sqrt(discriminant)) / (2.0 * a);
        if (t < 0) {
            t = (-b + std::sqrt(discriminant)) / (2.0 * a);
        }
        return t >= 0;
    }

    Vector3 getNormal(const Vector3& point) const {
        return (point - center).normalize();
    }
};

#endif