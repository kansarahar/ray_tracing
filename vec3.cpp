#include "vec3.h"
#include "surface.h"


vec3::vec3(): a(0), b(0), c(0) { };
vec3::vec3(double a, double b, double c): a(a), b(b), c(c) { };

double vec3::mag() const { return sqrt(dot(*this, *this)); };
vec3 vec3::unit() const { return *this/this->mag(); };

void vec3::rotate(const vec3 &axis, double theta) {
    quaternion q(cos(theta*M_PI/360), sin(theta*M_PI/360)*axis.unit());
    *this = (q*quaternion(0, *this)*q.conj()).v;
};
void vec3::rotate(const vec3 &point, const vec3 &axis, double theta) {
    this->translate(-1*point);
    this->rotate(axis, theta);
    this->translate(point);
}

vec3 vec3::reflect(const vec3 &normal) {
    vec3 n = normal.unit();
    vec3 l = -1*(*this).unit();
    return 2*(dot(l,n)*n)-l;
}

std::string vec3::to_string() { return "< " + std::to_string(this->a) + ", " + std::to_string(this->b) + ", " + std::to_string(this->c) + " >"; };



quaternion::quaternion(double r, vec3 v): r(r), v(v) { }

std::string quaternion::to_string() { return "(" + std::to_string(this->r) + ", " + v.to_string() + ")"; };



Ray::Ray(): origin(vec3()), direction(vec3(0,0,-1)), hit_surface(nullptr) { }
Ray::Ray(vec3 origin, vec3 direction): origin(origin), direction(direction), hit_surface(nullptr) { }

void Ray::trace(const std::vector<Surface *> &surfaces_array) {
    for (unsigned i = 0; i < surfaces_array.size(); i++) {
        Surface *surface = surfaces_array[i];
        if (surface->hit(*this)) {
            if (this->hit_surface == nullptr || this->hit_surface->t() > surface->t()) {
                this->hit_surface = surface;
            }
        }
    }
};

std::string Ray::to_string() { return "origin: " + this->origin.to_string() + ", direction: " + this->direction.to_string(); };