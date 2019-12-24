#include <iostream>
#include <cmath>
#include "vec3.h"
#include "surface.h"


vec3::vec3(): a(0), b(0), c(0) {

}

vec3::vec3(double a, double b, double c): a(a), b(b), c(c) {

}

double dot(vec3 v1, vec3 v2) {
    return v1.a*v2.a + v1.b*v2.b + v1.c*v2.c;
}

vec3 cross(vec3 v1, vec3 v2) {
    return vec3(v1.b*v2.c-v1.c*v2.b, v1.c*v2.a-v1.a*v2.c, v1.a*v2.b-v1.b*v2.a);
}

double vec3::mag() {
    return sqrt(dot(*this, *this));
}

vec3 vec3::unit() {
    return *this/this->mag();
}

std::string vec3::to_string() {
    return "< " + std::to_string(this->a) + ", " + std::to_string(this->b) + ", " + std::to_string(this->c) + " >";
}
    
void vec3::operator+=(vec3 other) {
    a += other.a;
    b += other.b;
    c += other.c;
}

void vec3::operator-=(vec3 other) {
    a -= other.a;
    b -= other.b;
    c -= other.c;
}

void vec3::operator*=(vec3 other) {
    a *= other.a;
    b *= other.b;
    c *= other.c;
}

vec3 operator+(vec3 v1, vec3 v2) {
    return vec3(v1.a+v2.a, v1.b+v2.b, v1.c+v2.c);
}
vec3 operator-(vec3 v1, vec3 v2){ 
    return vec3(v1.a-v2.a, v1.b-v2.b, v1.c-v2.c);
}
vec3 operator*(vec3 v1, vec3 v2) {
    return vec3(v1.a*v2.a, v1.b*v2.b, v1.c*v2.c);
}

vec3 operator*(double c, vec3 v) {
    return vec3(c*v.a, c*v.b, c*v.c);
}
vec3 operator*(vec3 v, double c){ 
    return vec3(c*v.a, c*v.b, c*v.c);
}
vec3 operator/(vec3 v, double c) { 
    return vec3(v.a/c, v.b/c, v.c/c);
}



void print_vec(vec3 v) {
    std::cout << "<" << v.a << ", " << v.b << ", " << v.c << ">" << std::endl;
}


Ray::Ray(): origin(vec3()), direction(vec3(0,0,-1)), hit_surface(nullptr) {

}

Ray::Ray(vec3 origin, vec3 direction): origin(origin), direction(direction), hit_surface(nullptr) {

}

vec3 Ray::at(double t) {
    return this->origin + t*this->direction;
}

void Ray::trace(std::vector<Surface *> &surfaces_array) {
    for (unsigned i = 0; i < surfaces_array.size(); i++) {
        Surface *surface = surfaces_array[i];
        if (surface->hit(*this)) {
            if (this->hit_surface == nullptr || this->hit_surface->t > surface->t) {
                this->hit_surface = surface;
            }
        }
    }
}

std::string Ray::to_string() {
    return "origin: " + this->origin.to_string() + ", direction: " + this->direction.to_string();
}