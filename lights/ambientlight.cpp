#include "ambientlight.h"

AmbientLight::AmbientLight(vec3 color, double intensity)  {
    this->intensity = intensity*(color.unit());
}

AmbientLight::~AmbientLight() { }


vec3 AmbientLight::illuminate(Ray &source_ray, const std::vector<Surface *> &surfaces) {
    Surface* surface = source_ray.hit_surface;
    if (surface == nullptr) { return vec3(); }
    return surface->color()*this->intensity*surface->material.k_a;
}