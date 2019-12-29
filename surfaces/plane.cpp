#include "plane.h"

Plane::Plane(vec3 point, vec3 color): _point(point) {
    this->_t = 0;
    this->_color = color;
    this->_normal = vec3(0,0,1);

    this->_up = vec3(0,0,1);
    this->_right = vec3(1,0,0);
    this->_cross = vec3(0,1,0);

}

Plane::~Plane() { }

bool Plane::hit(Ray &ray) {
    double denom = dot(this->_normal, ray.direction);
    if (denom == 0) { return false; }
    double t = dot(this->_normal, this->_point-ray.origin)/denom;
    if (t > 1e-10) {
        this->_t = t;
        if (dot(ray.direction, this->_normal) > 0) {
            this->_normal = -1*this->_normal;
        }
        return true;
    }
    return false;
}

void Plane::translateSelf(const vec3 &translation) {
    this->_point.translate(translation);
}

void Plane::rotateSelf(const vec3 &axis, double angle) {
    this->_normal.rotate(axis, angle);
    this->_up.rotate(axis, angle);
    this->_right.rotate(axis, angle);
    this->_cross.rotate(axis, angle);
}