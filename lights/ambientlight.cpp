#include "ambientlight.h"

AmbientLight::AmbientLight(double intensity)  {
    this->intensity = intensity;
}

AmbientLight::~AmbientLight() { }


vec3 AmbientLight::illuminate(Ray &source_ray, const std::vector<Surface *> &surfaces) {
    if (source_ray.hit_surface == nullptr) { return vec3(); }
    return source_ray.hit_surface->color()*this->intensity;
}