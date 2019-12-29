#include "directionallight.h"

DirectionalLight::DirectionalLight(vec3 direction, double intensity)  {
    this->direction = direction.unit();
    this->intensity = intensity;
}

DirectionalLight::~DirectionalLight() { }


vec3 DirectionalLight::illuminate(Ray &source_ray, const std::vector<Surface *> &surfaces) {
    if (source_ray.hit_surface == nullptr) { return vec3(); }
    vec3 hit_point = source_ray.at(source_ray.hit_surface->t()*0.999999);
    Ray shadow_ray = Ray(hit_point, -1*this->direction);
    shadow_ray.trace(surfaces);
    if (shadow_ray.hit_surface == nullptr) {
        vec3 pixel_color = source_ray.hit_surface->color()*this->intensity*dot(shadow_ray.direction.unit(), source_ray.hit_surface->normal().unit());
        if (pixel_color.a < 0 || pixel_color.b < 0 || pixel_color.c < 0) {
            return vec3();
        }
        return pixel_color;
    }
    return vec3();
}