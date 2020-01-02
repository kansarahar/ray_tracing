#include "surface.h"

inline vec3 defaultSphereTexture(double azimuthal, double polar) { 
    double p = sin(polar*M_PI/20);
    double a = sin(azimuthal*M_PI/20);
    if ((p > 0 && a > 0) || (p < 0 && a < 0)) { return vec3(100,100,100); }
    return vec3(200, 200, 200); 
}

Sphere::Sphere(vec3 center, double radius, vec3 color): _center(center), _radius(radius) {
    this->_t = 0;
    this->_normal = vec3();
    this->_color = color;

    this->_up = vec3(0,0,1);
    this->_right = vec3(1,0,0);
    this->_cross = vec3(0,1,0);

    this->_textured = false;
    this->_texture_function = defaultSphereTexture;
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
        if (this->_textured) {
            vec3 r = ray.at(t) - this->_center;
            double polar = acos(dot(this->_up, r)/r.mag());
            vec3 s = r - dot(r, this->_up)*this->_up;
            double azimuthal = 0.5*acos(2*dot(s, this->_right)*dot(s, this->_right)/dot(s,s) - 1);
            if (dot(s, this->_cross) < 0) { azimuthal += M_PI; }
            this->_color = _texture_function(azimuthal*180/M_PI, polar*180/M_PI);
        }
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

void Sphere::rotate(const vec3 &point, const vec3 &axis, double angle) {
    this->_center.rotate(point, axis, angle);
    this->rotateSelf(axis, angle);
}




inline vec3 defaultPlaneTexture(double x, double y) { 
    double sinx = sin(x/20);
    double siny = sin(y/20);
    if ((sinx > 0 && siny > 0) || (sinx < 0 && siny < 0)) { return vec3(100,100,100); }
    return vec3(200, 200, 200); 
}

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

    this->_textured = false;
    this->_texture_function = defaultPlaneTexture;

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
        if (this->_textured) {
            double x = dot(ray.at(t)-this->_point, this->_right);
            double y = dot(ray.at(t)-this->_point, this->_cross);
            this->_color = this->_texture_function(x,y);
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