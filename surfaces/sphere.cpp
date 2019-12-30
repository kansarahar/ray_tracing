#include "sphere.h"

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

void Sphere::texture() {
    this->_textured = true;
}

void Sphere::texture(vec3 (*texture_function)(double azimuthal_angle, double polar_angle)) {
    this->_textured = true;
    this->_texture_function = texture_function;
}
