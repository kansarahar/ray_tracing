#include <cmath>
#include "sphere.h"

Sphere::Sphere(vec3 center, double radius, vec3 color): center(center), radius(radius) {
    this->normal = Ray();
    this->t = 0;
    this->color = color;
}

Sphere::~Sphere() {
    
}


bool Sphere::hit(Ray &ray) {
    double a = dot(ray.direction, ray.direction);
    double b = 2*dot(ray.direction, ray.origin - this->center);
    double c = dot(ray.origin, ray.origin) + dot(this->center, this->center)
                -2*(dot(ray.origin, this->center)) - (this->radius)*(this->radius);
    double k = b*b - 4*a*c;
    if (k > 0) {
        k = sqrt(k);
        t = (-b-k)/(2*a);
        if (t < 0) {
            t = (-b+k)/(2*a);
            if (t < 0) {
                return false;
            }
        }
        this->t = t;
        this->normal = Ray(ray.at(t), ray.at(t)-this->center);
        return true;
    }
    return false;
};


