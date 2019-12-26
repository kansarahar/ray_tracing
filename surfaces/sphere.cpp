#include "sphere.h"

Sphere::Sphere(vec3 center, double radius, vec3 color): _center(center), _radius(radius) {
    this->_t = 0;
    this->_normal = Ray();
    this->_color = color;
}

Sphere::~Sphere() {
    
}


bool Sphere::hit(Ray &ray) {
    double a = dot(ray.direction, ray.direction);
    double b = 2*dot(ray.direction, ray.origin - this->_center);
    double c = dot(ray.origin, ray.origin) + dot(this->_center, this->_center)
                -2*(dot(ray.origin, this->_center)) - (this->_radius)*(this->_radius);
    double k = b*b - 4*a*c;
    if (k > 0) {
        k = sqrt(k);
        double t = (-b-k)/(2*a);
        if (t < 0) {
            t = (-b+k)/(2*a);
            if (t < 0) {
                return false;
            }
        }
        this->_t = t;
        this->_normal = Ray(ray.at(_t), ray.at(_t)-this->_center);
        return true;
    }
    return false;
};


