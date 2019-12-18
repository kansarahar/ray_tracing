#include <iostream>
#include <cmath>
#include "vec3.h"



vec3::vec3(double a, double b, double c) {
    this->a = a;
    this->b = b;
    this->c = c;
}

vec3::vec3() {
    this->a = 0;
    this->b = 0;
    this->c = 0;
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
    double mag = this->mag();
    return *this/mag;
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


Ray::Ray() {
    this->origin = vec3();
    this->direction = vec3(0,0,-1);
    this->hit_surface = nullptr;
}

Ray::Ray(vec3 origin, vec3 direction) {
    this->origin = origin;
    this->direction = direction;
    this->hit_surface = nullptr;
}

vec3 Ray::at(double t) {
    return this->origin + t*this->direction;
}

vec3 Ray::trace(Surface** surfaces) {
    return vec3();
}

void Ray::print() {
    print_vec(this->origin);
    print_vec(this->direction);
}