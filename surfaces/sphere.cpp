#include "sphere.h"

Sphere::Sphere(vec3 center, double radius, vec3 color): _center(center), _radius(radius) {
    this->_t = 0;
    this->_normal = vec3();
    this->_color = color;
}

Sphere::~Sphere() { }


bool Sphere::hit(Ray &ray) {
    double a = dot(ray.direction, ray.direction);
    double b = 2*dot(ray.direction, ray.origin - this->_center);
    double c = dot(ray.origin, ray.origin) + dot(this->_center, this->_center)
                - 2*(dot(ray.origin, this->_center)) - (this->_radius)*(this->_radius);
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
        this->_normal = ray.at(_t)-this->_center;
        return true;
    }
    return false;
}

void Sphere::translateSelf(const vec3 &translation) {
    this->_center.translate(translation);
}

void Sphere::rotateSelf(const vec3 &axis, double angle) {
    this->_up.rotate(axis, angle);
    this->_right.rotate(axis, angle);
    this->_cross.rotate(axis, angle);
}