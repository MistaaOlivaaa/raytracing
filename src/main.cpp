#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include "vector3.hpp"
#include "ray.hpp"
#include "sphere.hpp"

class Camera {
public:
    Vector3 position;
    Vector3 direction;
    Vector3 up;
    Vector3 right;
    double fov;
    double aspect;

    Camera(const Vector3& position, const Vector3& direction, const Vector3& up, double fov, double aspect)
        : position(position), direction(direction.normalize()), fov(fov), aspect(aspect) {
        right = this->direction.cross(up).normalize();
        this->up = right.cross(this->direction);
    }

    Ray getRay(double u, double v) const {
        double theta = fov * M_PI / 180.0;
        double h = tan(theta / 2);
        double viewport_height = 2.0 * h;
        double viewport_width = aspect * viewport_height;

        Vector3 horizontal = right * viewport_width;
        Vector3 vertical = up * viewport_height;
        Vector3 lower_left_corner = position + direction - horizontal/2 - vertical/2;

        return Ray(position, lower_left_corner + horizontal*u + vertical*v - position);
    }
};

Vector3 trace(const Ray& ray, const std::vector<Sphere>& spheres, const Vector3& light_dir, int depth = 0) {
    if (depth > 3) return Vector3(0, 0, 0);

    double closest_t = INFINITY;
    const Sphere* closest_sphere = nullptr;

    for (const auto& sphere : spheres) {
        double t;
        if (sphere.intersect(ray, t)) {
            if (t < closest_t) {
                closest_t = t;
                closest_sphere = &sphere;
            }
        }
    }

    if (closest_sphere) {
        Vector3 hit_point = ray.at(closest_t);
        Vector3 normal = closest_sphere->getNormal(hit_point);
        double light = std::max(0.0, normal.dot(light_dir * -1.0));
        return closest_sphere->color * light;
    }

    return Vector3(0.2, 0.3, 0.5); // Sky color
}

int main() {
    const int width = 800;
    const int height = 600;

    std::vector<Sphere> spheres;
    spheres.push_back(Sphere(Vector3(0, 0, -5), 1.0, Vector3(1.0, 0.2, 0.2))); // Red sphere
    spheres.push_back(Sphere(Vector3(2, 0, -6), 1.0, Vector3(0.2, 1.0, 0.2))); // Green sphere
    spheres.push_back(Sphere(Vector3(-2, 0, -4), 1.0, Vector3(0.2, 0.2, 1.0))); // Blue sphere

    Camera camera(Vector3(0, 0, 0), Vector3(0, 0, -1), Vector3(0, 1, 0), 90, double(width)/height);
    Vector3 light_dir = Vector3(1, -1, -1).normalize();

    std::ofstream out("output.ppm");
    out << "P3\n" << width << " " << height << "\n255\n";

    for (int j = height-1; j >= 0; --j) {
        for (int i = 0; i < width; ++i) {
            double u = double(i) / (width-1);
            double v = double(j) / (height-1);

            Ray ray = camera.getRay(u, v);
            Vector3 color = trace(ray, spheres, light_dir);

            int r = static_cast<int>(255.99 * std::min(1.0, color.x));
            int g = static_cast<int>(255.99 * std::min(1.0, color.y));
            int b = static_cast<int>(255.99 * std::min(1.0, color.z));

            out << r << " " << g << " " << b << "\n";
        }
    }

    out.close();
    std::cout << "Rendered image saved to output.ppm\n";
    return 0;
}