#include "surface.h"



Sphere::Sphere(vec3 center, double radius): 
    _radius(radius) {

    this->_center = center;

    this->_up = vec3(0,0,1);
    this->_right = vec3(1,0,0);
    this->_cross = vec3(0,1,0);
}

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
        return true;
    }
    return false;
}

void Sphere::calculateValues(Ray &ray) {
    this->_normal = (ray.at(this->_t)-this->_center).unit();
    this->_outer_surface_normal = this->_normal;
    if (dot(ray.direction, this->_normal) > 0) { this->_normal = -1*this->_normal; }
    this->_color = this->texture.getColor(ray.at(this->_t), this->_center, this->_up, this->_right, this->_cross);
}



Cylinder::Cylinder(vec3 center, double radius, double height): 
    _radius(radius), _height(height) {

    this->_center = center;

    this->_up = vec3(0,0,1);
    this->_right = vec3(1,0,0);
    this->_cross = vec3(0,1,0);
}

bool Cylinder::hit(Ray &ray) {

    double da = dot(ray.direction, this->_up);
    double qa = dot(ray.origin, this->_up);
    double ca = dot(this->_center, this->_up);
    double a = dot(ray.direction, ray.direction) - da*da;
    double b = 2*dot(ray.direction, ray.origin-this->_center) - 2*da*(qa-ca);
    double c = dot(ray.origin, ray.origin)-qa*qa+dot(this->_center, this->_center)
        -ca*ca-2*dot(ray.origin, this->_center)+2*(qa*ca)-(this->_radius*this->_radius);

    double k = b*b - 4*a*c;
    if (k > 0) {
        k = sqrt(k);
        double t = (-b-k)/(2*a);
        double height = dot(ray.at(t)-this->_center, this->_up);
        if (t < 0 || height > this->_height || height < 0) {
            t = (-b+k)/(2*a);
            if (t < 0) { return false; }
        }
        height = dot(ray.at(t)-this->_center, this->_up);
        if (height > this->_height || height < 0) { return false; }
        this->_t = t;
        return true;
    }
    return false;
}

void Cylinder::calculateValues(Ray &ray) {
    vec3 r = ray.at(this->_t) - this->_center;
    this->_normal = (r - dot(r, this->_up)*this->_up).unit();
    this->_outer_surface_normal = this->_normal;
    if (dot(ray.direction, this->_normal) > 0) { this->_normal = -1*this->_normal; }
    this->_color = this->texture.getColor(ray.at(this->_t), this->_center, this->_up, this->_right, this->_cross);
}




Cone::Cone(vec3 center, double angle, double height): 
    _angle(angle*M_PI/180), _height(height), _cos_angle(cos(angle*M_PI/180)), _tan_angle(tan(angle*M_PI/180)) {

    this->_t = 0;
    this->_normal = vec3();
    this->_center = center;

    this->_up = vec3(0,0,1);
    this->_right = vec3(1,0,0);
    this->_cross = vec3(0,1,0);
}

bool Cone::hit(Ray &ray) {

    double da = dot(ray.direction, this->_up);
    double qa = dot(ray.origin, this->_up);
    double ca = dot(this->_center, this->_up);
    double cost = this->_cos_angle;
    double a = dot(ray.direction, ray.direction)*cost*cost - da*da;
    double b = 2*dot(ray.direction, ray.origin-this->_center)*cost*cost - 2*da*(qa-ca);
    double c = (dot(ray.origin, ray.origin)+dot(this->_center, this->_center)
        -2*dot(ray.origin, this->_center))*cost*cost - qa*qa - ca*ca + 2*qa*ca;

    double k = b*b-4*a*c;
    if (k > 0) {
        k = sqrt(k);
        double t = (-b-k)/(2*a);
        double height = dot(ray.at(t)-this->_center, this->_up);
        if (t < 0 || height > this->_height || height < 0) {
            t = (-b+k)/(2*a);
            if (t < 0) { return false; }
        }
        height = dot(ray.at(t)-this->_center, this->_up);
        if (height > this->_height || height < 0) { return false; }
        this->_t = t;
        return true;
    }
    return false;
}

void Cone::calculateValues(Ray &ray) {
    vec3 r = ray.at(this->_t) - this->_center;
    vec3 s = (r - dot(r, this->_up)*this->_up).unit();
    this->_normal = (s - (this->_tan_angle*this->_up)).unit();
    this->_outer_surface_normal = this->_normal;
    if (dot(ray.direction, this->_normal) > 0) { this->_normal = -1*this->_normal; }
    this->_color = this->texture.getColor(ray.at(this->_t), this->_center, this->_up, this->_right, this->_cross);
}



Plane::Plane(vec3 center, vec3 normal) {
    this->_normal = normal.unit();
    this->_center = center;

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

    this->_outer_surface_normal = this->_normal;
}

bool Plane::hit(Ray &ray) {
    double denom = dot(this->_up, ray.direction);
    if (denom == 0) { return false; }
    double t = dot(this->_up, this->_center-ray.origin)/denom;
    if (t > 1e-10) {
        this->_t = t;
        return true;
    }
    return false;
}

void Plane::calculateValues(Ray &ray) {
    if (dot(ray.direction, this->_normal) > 0) { this->_normal = -1*this->_normal; }
    this->_color = this->texture.getColor(ray.at(this->_t), this->_center, this->_up, this->_right, this->_cross);
}

void Plane::rotateSelf(const vec3 &axis, double angle) {
    this->_normal.rotate(axis, angle);
    this->_outer_surface_normal.rotate(axis, angle);
    this->_up.rotate(axis, angle);
    this->_right.rotate(axis, angle);
    this->_cross.rotate(axis, angle);
}



Triangle::Triangle(vec3 v0, vec3 v1, vec3 v2):
    _v0(v0), _v1(v1), _v2(v2), _normal_unnormalized(cross(v1-v0, v2-v0)), _area(_normal_unnormalized.mag()/2), _u(0), _v(0), _w(0) {

    this->_t = 0;
    this->_normal = cross(v1-v0, v2-v0).unit();
    this->_center = v0;

    this->_up = _normal;
    this->_right = (v1-v0).unit();
    this->_cross = cross(this->_up, this->_right).unit();

    this->_outer_surface_normal = this->_up;
}

bool Triangle::hit(Ray &ray) {

    double denom = dot(this->_up, ray.direction);
    if (denom == 0) { return false; }
    double t = dot(this->_up, this->_center-ray.origin)/denom;
    if (t > 1e-10) {
        this->_t = t;
        vec3 point = ray.at(t) - this->_v0;
        double u = dot(cross(this->_v1 - this->_v0, point), this->_up)/2/this->_area;
        if (u > 0) { 
            double v = dot(cross(point, this->_v2 - this->_v0), this->_up)/2/this->_area;
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
    if (dot(ray.direction, this->_normal) > 0) {
        this->_normal = -1*this->_normal;
        this->_normal_unnormalized = -1*this->_normal_unnormalized;
    }
    this->_color = this->texture.getColor(ray.at(this->_t), this->_center, this->_up, this->_right, this->_cross);
}

void Triangle::translateSelf(const vec3 &translation) {
    this->_center.translate(translation);
    this->_v0.translate(translation);
    this->_v1.translate(translation);
    this->_v2.translate(translation);
}

void Triangle::rotateSelf(const vec3 &axis, double angle) {
    this->_normal.rotate(axis, angle);
    this->_outer_surface_normal.rotate(axis, angle);
    this->_up.rotate(axis, angle);
    this->_right.rotate(axis, angle);
    this->_cross.rotate(axis, angle);

    this->_normal_unnormalized.rotate(axis, angle);
    this->_v1.rotate(this->_v0, axis, angle);
    this->_v2.rotate(this->_v0, axis, angle);
}

void Triangle::rotate(const vec3 &point, const vec3 &axis, double angle) {
    this->_normal.rotate(axis, angle);
    this->_outer_surface_normal.rotate(axis, angle);
    this->_up.rotate(axis, angle);
    this->_right.rotate(axis, angle);
    this->_cross.rotate(axis, angle);

    this->_normal_unnormalized.rotate(axis, angle);
    this->_center.rotate(point, axis, angle);
    this->_v0.rotate(point, axis, angle);
    this->_v1.rotate(point, axis, angle);
    this->_v2.rotate(point, axis, angle);
}