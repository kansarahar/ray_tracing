#include "pointlight.h"
#include <iostream>
PointLight::PointLight(vec3 center, double intensity)  {
    this->center = center;
    this->intensity = intensity;
    this->attenuated = false;
    this->showing = false;
    this->attenuation_function = vec3(1, 0, 0);
    this->lightsphere = new Sphere(center, 1, vec3(255,255,255));
}

PointLight::~PointLight() { }


vec3 PointLight::illuminate(Ray &source_ray, const std::vector<Surface *> &surfaces) {
    if (source_ray.hit_surface == nullptr) { return vec3(); }
    vec3 hit_point = source_ray.at(source_ray.hit_surface->t()*0.999999);
    Ray shadow_ray = Ray(hit_point, (this->center-hit_point).unit());
    shadow_ray.trace(surfaces);
    if (shadow_ray.hit_surface == nullptr || shadow_ray.hit_surface->t() >= 1) {
        vec3 pixel_color = source_ray.hit_surface->color()*this->intensity*dot(shadow_ray.direction.unit(), source_ray.hit_surface->normal().unit());
        if (pixel_color.a < 0 || pixel_color.b < 0 || pixel_color.c < 0) {
            return vec3();
        }
        if (this->attenuated) {
            double r = shadow_ray.direction.mag();
            double att = 1/(attenuation_function.a + r*attenuation_function.b + r*r*attenuation_function.c);
            pixel_color = pixel_color*att;
        }
        return pixel_color;
    }
    return vec3();
}