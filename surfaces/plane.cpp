#include "plane.h"

Plane::Plane(vec3 point, vec3 normal, vec3 color): _point(point) {
    this->_t = 0;
    this->_color = color;
    this->_normal = normal.unit();

    // ensure that basis vectors are orthogonal
    this->_up = this->_normal;
    this->_right = vec3(1,0,0);
    if (cross(this->_up, this->_right).mag() < 1e-10) {
        this->_normal = vec3(1,0,0);
        this->_up = vec3(1,0,0);
        this->_right = vec3(0,0,-1);
        this->_cross = vec3(0,1,0);
    }
    else {
        this->_cross = cross(this->_up, this->_right).unit();
        this->_right = cross(this->_cross, this->_up);
    }

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

void Plane::rotate(const vec3 &point, const vec3 &axis, double angle) {
    this->_point.rotate(point, axis, angle);
    this->rotateSelf(axis, angle);
}