#include "ambientlight.h"

AmbientLight::AmbientLight(vec3 color, double intensity)  {
    this->intensity = intensity*(color.unit());
}

AmbientLight::~AmbientLight() { }


vec3 AmbientLight::illuminate(Ray &source_ray, const std::vector<Surface *> &surfaces) {
    if (source_ray.hit_surface == nullptr) { return vec3(); }
    return source_ray.hit_surface->color()*this->intensity;
}