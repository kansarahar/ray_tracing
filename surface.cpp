#include "surface.h"



Sphere::Sphere(vec3 center, double radius): 
    _radius(radius) {

    _center = center;

    _up = vec3(0,0,1);
    _right = vec3(1,0,0);
    _cross = vec3(0,1,0);
}

bool Sphere::hit(Ray &ray) {

    double a = dot(ray.direction, ray.direction);
    double b = 2*dot(ray.direction, ray.origin - _center);
    double c = dot(ray.origin, ray.origin) + dot(_center, _center)
                - 2*(dot(ray.origin, _center)) - _radius*_radius;
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
        return true;
    }
    return false;
}

void Sphere::calculateValues(Ray &ray) {
    _normal = (ray.at(_t)-_center).unit();
    _outer_surface_normal = _normal;
    if (dot(ray.direction, _normal) > 0) { _normal = -1*_normal; }
    _color = this->texture.getColor(ray.at(_t), _center, _up, _right, _cross);
}



Cylinder::Cylinder(vec3 center, double radius, double height): 
    _radius(radius), _height(height) {

    _center = center;

    _up = vec3(0,0,1);
    _right = vec3(1,0,0);
    _cross = vec3(0,1,0);
}

bool Cylinder::hit(Ray &ray) {

    double da = dot(ray.direction, _up);
    double qa = dot(ray.origin, _up);
    double ca = dot(_center, _up);
    double a = dot(ray.direction, ray.direction) - da*da;
    double b = 2*dot(ray.direction, ray.origin-_center) - 2*da*(qa-ca);
    double c = dot(ray.origin, ray.origin)-qa*qa+dot(_center, _center)
        -ca*ca-2*dot(ray.origin, _center)+2*(qa*ca)-_radius*_radius;

    double k = b*b - 4*a*c;
    if (k > 0) {
        k = sqrt(k);
        double t = (-b-k)/(2*a);
        double height = dot(ray.at(t)-_center, _up);
        if (t < 0 || height > this->_height || height < 0) {
            t = (-b+k)/(2*a);
            if (t < 0) { return false; }
        }
        height = dot(ray.at(t)-_center, _up);
        if (height > this->_height || height < 0) { return false; }
        this->_t = t;
        return true;
    }
    return false;
}

void Cylinder::calculateValues(Ray &ray) {
    vec3 r = ray.at(_t) - _center;
    _normal = (r - dot(r, _up)*_up).unit();
    _outer_surface_normal = _normal;
    if (dot(ray.direction, _normal) > 0) { _normal = -1*_normal; }
    _color = this->texture.getColor(ray.at(_t), _center, _up, _right, _cross);
}




Cone::Cone(vec3 center, double angle, double height): 
    _angle(angle*M_PI/180), _height(height), _cos_angle(cos(angle*M_PI/180)), _tan_angle(tan(angle*M_PI/180)) {

    _center = center;

    _up = vec3(0,0,1);
    _right = vec3(1,0,0);
    _cross = vec3(0,1,0);
}

bool Cone::hit(Ray &ray) {

    double da = dot(ray.direction, _up);
    double qa = dot(ray.origin, _up);
    double ca = dot(_center, _up);
    double cost = _cos_angle;
    double a = dot(ray.direction, ray.direction)*cost*cost - da*da;
    double b = 2*dot(ray.direction, ray.origin-_center)*cost*cost - 2*da*(qa-ca);
    double c = (dot(ray.origin, ray.origin)+dot(_center, _center)
        -2*dot(ray.origin, _center))*cost*cost - qa*qa - ca*ca + 2*qa*ca;

    double k = b*b-4*a*c;
    if (k > 0) {
        k = sqrt(k);
        double t = (-b-k)/(2*a);
        double height = dot(ray.at(t)-_center, _up);
        if (t < 0 || height > this->_height || height < 0) {
            t = (-b+k)/(2*a);
            if (t < 0) { return false; }
        }
        height = dot(ray.at(t)-_center, _up);
        if (height > this->_height || height < 0) { return false; }
        this->_t = t;
        return true;
    }
    return false;
}

void Cone::calculateValues(Ray &ray) {
    vec3 r = ray.at(_t) - _center;
    vec3 s = (r - dot(r, _up)*_up).unit();
    _normal = (s - (_tan_angle*_up)).unit();
    _outer_surface_normal = _normal;
    if (dot(ray.direction, _normal) > 0) { _normal = -1*_normal; }
    _color = this->texture.getColor(ray.at(_t), _center, _up, _right, _cross);
}



Plane::Plane(vec3 center, vec3 normal) {
    _normal = normal.unit();
    _center = center;

    // ensure that basis vectors are orthogonal
    _up = _normal;
    _right = vec3(1,0,0);
    if (cross(_up, _right).mag() < 1e-10) {
        _normal = vec3(1,0,0);
        _up = vec3(1,0,0);
        _right = vec3(0,0,-1);
        _cross = vec3(0,1,0);
    }
    else {
        _cross = cross(_up, _right).unit();
        _right = cross(_cross, _up);
    }

    _outer_surface_normal = _normal;
}

bool Plane::hit(Ray &ray) {
    double denom = dot(_up, ray.direction);
    if (denom == 0) { return false; }
    double t = dot(_up, _center-ray.origin)/denom;
    if (t > 1e-10) {
        this->_t = t;
        return true;
    }
    return false;
}

void Plane::calculateValues(Ray &ray) {
    if (dot(ray.direction, _normal) > 0) { _normal = -1*_normal; }
    _color = this->texture.getColor(ray.at(_t), _center, _up, _right, _cross);
}

void Plane::rotateSelf(const vec3 &axis, double angle) {
    _normal.rotate(axis, angle);
    _outer_surface_normal.rotate(axis, angle);
    _up.rotate(axis, angle);
    _right.rotate(axis, angle);
    _cross.rotate(axis, angle);
}



Triangle::Triangle(vec3 v0, vec3 v1, vec3 v2):
    _v0(v0), _v1(v1), _v2(v2), _normal_unnormalized(cross(v1-v0, v2-v0)), _area(_normal_unnormalized.mag()/2), _u(0), _v(0), _w(0) {

    _normal = cross(v1-v0, v2-v0).unit();
    _center = v0;

    _up = _normal;
    _right = (v1-v0).unit();
    _cross = cross(_up, _right).unit();

    _outer_surface_normal = _up;
}

bool Triangle::hit(Ray &ray) {

    double denom = dot(_up, ray.direction);
    if (denom == 0) { return false; }
    double t = dot(_up, _center-ray.origin)/denom;
    if (t > 1e-10) {
        _t = t;
        vec3 point = ray.at(t) - _v0;
        double u = dot(cross(_v1 - _v0, point), _up)/2/_area;
        if (u > 0) { 
            double v = dot(cross(point, _v2 - _v0), _up)/2/_area;
            if (v > 0 && 1-u-v > 0) {
                this->_u = u;
                this->_v = v;
                this->_w = 1-u-v;
                return true;
            }
        }
    }
    return false;
}

void Triangle::calculateValues(Ray &ray) {
    if (dot(ray.direction, _normal) > 0) {
        _normal = -1*_normal;
        _normal_unnormalized = -1*_normal_unnormalized;
    }
    _color = this->texture.getColor(ray.at(_t), _center, _up, _right, _cross);
}

void Triangle::translateSelf(const vec3 &translation) {
    _center.translate(translation);
    _v0.translate(translation);
    _v1.translate(translation);
    _v2.translate(translation);
}

void Triangle::rotateSelf(const vec3 &axis, double angle) {
    _normal.rotate(axis, angle);
    _outer_surface_normal.rotate(axis, angle);
    _up.rotate(axis, angle);
    _right.rotate(axis, angle);
    _cross.rotate(axis, angle);

    _normal_unnormalized.rotate(axis, angle);
    _v1.rotate(_v0, axis, angle);
    _v2.rotate(_v0, axis, angle);
}

void Triangle::rotate(const vec3 &point, const vec3 &axis, double angle) {
    _normal.rotate(axis, angle);
    _outer_surface_normal.rotate(axis, angle);
    _up.rotate(axis, angle);
    _right.rotate(axis, angle);
    _cross.rotate(axis, angle);

    _normal_unnormalized.rotate(axis, angle);
    _center.rotate(point, axis, angle);
    _v0.rotate(point, axis, angle);
    _v1.rotate(point, axis, angle);
    _v2.rotate(point, axis, angle);
}