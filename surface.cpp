#include "surface.h"

inline vec3 defaultSphereTexture(
    const vec3 &hit_point, 
    const vec3 &center, 
    const vec3 &up, 
    const vec3 &right, 
    const vec3 &cross
    ) { 
    vec3 r = hit_point-center;
    double cos_azi = cos(acos(dot((r - dot(r,up)*up).unit(), right))*5);
    double cos_pol = cos(acos(dot(r.unit(), up))*5);
    if ((cos_azi > 0 && cos_pol < 0) || (cos_azi < 0 && cos_pol > 0)) {
        return vec3(100, 100, 100);
    }
    return vec3(200, 200, 200); 
}

inline vec3 defaultCylinderAndConeTexture(
    const vec3 &hit_point, 
    const vec3 &center, 
    const vec3 &up, 
    const vec3 &right, 
    const vec3 &cross
    ) {
    vec3 r = hit_point-center;
    double cos_height = cos(dot(r, up)/5);
    double cos_angle = cos(acos(dot((r - dot(r,up)*up).unit(), right))*5);
    if ((cos_height > 0 && cos_angle < 0) || (cos_height < 0 && cos_angle > 0)) {
        return vec3(100, 100, 100);
    }
    return vec3(200, 200, 200);
}

inline vec3 defaultPlaneTexture(
    const vec3 &hit_point, 
    const vec3 &center, 
    const vec3 &up, 
    const vec3 &right, 
    const vec3 &cross
    ) { 
    vec3 r = hit_point-center;
    double x = sin(dot(r, right)/10);
    double y = sin(dot(r, cross)/10);
    if ((x > 0 && y < 0) || (x < 0 && y > 0)) {
        return vec3(100, 100, 100);
    }
    return vec3(200, 200, 200); 
}

Sphere::Sphere(vec3 center, double radius, vec3 color): 
    _radius(radius) {
    
    this->_t = 0;
    this->_normal = vec3();
    this->_center = center;
    this->_color = color;

    this->_up = vec3(0,0,1);
    this->_right = vec3(1,0,0);
    this->_cross = vec3(0,1,0);

    this->_textured = false;
    this->_texture_function = defaultSphereTexture;
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
    if (this->_textured) {
        this->_color = _texture_function(ray.at(this->_t), this->_center, this->_up, this->_right, this->_cross);
    }
}



Cylinder::Cylinder(vec3 center, double radius, double height, vec3 color): 
    _radius(radius), _height(height) {

    this->_t = 0;
    this->_normal = vec3();
    this->_center = center;
    this->_color = color;

    this->_up = vec3(0,0,1);
    this->_right = vec3(1,0,0);
    this->_cross = vec3(0,1,0);

    this->_textured = false;
    this->_texture_function = defaultCylinderAndConeTexture;
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
    if (dot(ray.direction, this->_normal) > 0) {
        this->_normal = -1*this->_normal;
    }
    if (this->_textured) {
        this->_color = _texture_function(ray.at(this->_t), this->_center, this->_up, this->_right, this->_cross);
    }
}




Cone::Cone(vec3 center, double angle, double height, vec3 color): 
    _angle(angle*M_PI/180), _height(height), _cos_angle(cos(angle*M_PI/180)), _tan_angle(tan(angle*M_PI/180)) {

    this->_t = 0;
    this->_normal = vec3();
    this->_center = center;
    this->_color = color;

    this->_up = vec3(0,0,1);
    this->_right = vec3(1,0,0);
    this->_cross = vec3(0,1,0);

    this->_textured = false;
    this->_texture_function = defaultCylinderAndConeTexture;
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
    if (dot(ray.direction, this->_normal) > 0) {
        this->_normal = -1*this->_normal;
    }
    if (this->_textured) {
        this->_color = _texture_function(ray.at(this->_t), this->_center, this->_up, this->_right, this->_cross);
    }
}



Plane::Plane(vec3 center, vec3 normal, vec3 color) {
    this->_t = 0;
    this->_normal = normal.unit();
    this->_color = color;
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

    this->_textured = false;
    this->_texture_function = defaultPlaneTexture;

}

bool Plane::hit(Ray &ray) {
    double denom = dot(this->_normal, ray.direction);
    if (denom == 0) { return false; }
    double t = dot(this->_normal, this->_center-ray.origin)/denom;
    if (t > 1e-10) {
        this->_t = t;
        return true;
    }
    return false;
}

void Plane::calculateValues(Ray &ray) {
    if (dot(ray.direction, this->_normal) > 0) {
        this->_normal = -1*this->_normal;
    }
    if (this->_textured) {
        this->_color = _texture_function(ray.at(this->_t), this->_center, this->_up, this->_right, this->_cross);
    }
}

void Plane::rotateSelf(const vec3 &axis, double angle) {
    this->_normal.rotate(axis, angle);
    this->_up.rotate(axis, angle);
    this->_right.rotate(axis, angle);
    this->_cross.rotate(axis, angle);
}



Triangle::Triangle(vec3 v0, vec3 v1, vec3 v2, vec3 color):
    _v0(v0), _v1(v1), _v2(v2), _normal_unnormalized(cross(v1-v0, v2-v0)), _area(_normal_unnormalized.mag()/2), _u(0), _v(0), _w(0) {

    this->_t = 0;
    this->_normal = cross(v1-v0, v2-v0).unit();
    this->_color = color;
    this->_center = v0;

    this->_up = _normal;
    this->_right = (v1-v0).unit();
    this->_cross = cross(this->_up, this->_right).unit();

    this->_textured = false;
    this->_texture_function = defaultPlaneTexture;
}

bool Triangle::hit(Ray &ray) {

    double denom = dot(this->_normal, ray.direction);
    if (denom == 0) { return false; }
    double t = dot(this->_normal, this->_center-ray.origin)/denom;
    if (t > 1e-10) {
        this->_t = t;

        vec3 v1v0 = this->_v1 - this->_v0;
        vec3 v2v0 = this->_v2 - this->_v0;

        vec3 point = ray.at(t)-this->_v0;
        double u = dot(cross(v1v0, point), this->_normal)/2/this->_area;
        if (u > 0) { 
            double v = dot(cross(point, v2v0), this->_normal)/2/this->_area;
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
        vec3 temp_v1 = this->_v1;
        this->_v1 = this->_v2;
        this->_v2 = temp_v1;
        this->_normal_unnormalized = -1*this->_normal_unnormalized;
    }
    if (this->_textured) {
        this->_color = _texture_function(ray.at(this->_t), this->_center, this->_up, this->_right, this->_cross);
    }
}

void Triangle::translateSelf(const vec3 &translation) {
    this->_center.translate(translation);
    this->_v0.translate(translation);
    this->_v1.translate(translation);
    this->_v2.translate(translation);
}

void Triangle::rotateSelf(const vec3 &axis, double angle) {
    this->_normal.rotate(axis, angle);
    this->_up.rotate(axis, angle);
    this->_right.rotate(axis, angle);
    this->_cross.rotate(axis, angle);

    this->_normal_unnormalized.rotate(axis, angle);
    this->_v1.rotate(this->_v0, axis, angle);
    this->_v2.rotate(this->_v0, axis, angle);
}

void Triangle::rotate(const vec3 &point, const vec3 &axis, double angle) {
    this->_normal.rotate(axis, angle);
    this->_up.rotate(axis, angle);
    this->_right.rotate(axis, angle);
    this->_cross.rotate(axis, angle);

    this->_normal_unnormalized.rotate(axis, angle);
    this->_center.rotate(point, axis, angle);
    this->_v0.rotate(point, axis, angle);
    this->_v1.rotate(point, axis, angle);
    this->_v2.rotate(point, axis, angle);
}