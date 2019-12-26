#include "plane.h"

Plane::Plane(vec3 point, vec3 normal, vec3 color): _point(point) {
    this->_t = 0;
    this->_color = color;
    this->_normal = normal;
}

Plane::Plane(vec3 point1, vec3 point2, vec3 point3, vec3 color): _point(point1) {
    this->_t = 0;
    this->_color = color;
    this->_normal = cross(point2-point1, point3-point1);
}

Plane::~Plane() { }

bool Plane::hit(Ray &ray) {
    double denom = dot(this->_normal, ray.direction);
    if (denom == 0) { return false; }
    double t = dot(this->_normal, this->_point-ray.origin)/denom;
    if (t > 0) {
        this->_t = t;
        if (dot(ray.direction, this->_normal) > 0) {
            this->_normal = -1*this->_normal;
        }
        return true;
    }
    return false;
}