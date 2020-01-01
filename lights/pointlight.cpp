#include "pointlight.h"
#include <iostream>
PointLight::PointLight(vec3 center, vec3 color, double intensity)  {
    this->center = center;
    this->intensity = intensity*(color.unit());
    this->attenuated = false;
    this->showing = false;
    this->attenuation_function = vec3(1, 0, 0);
    this->lightsphere = new Sphere(center, 1, vec3(255,255,255));
}

PointLight::~PointLight() { }


vec3 PointLight::illuminate(Ray &source_ray, const std::vector<Surface *> &surfaces) {
    if (source_ray.hit_surface == nullptr) { return vec3(); }
    vec3 hit_point = source_ray.at(source_ray.hit_surface->t()*0.999999);
    double dist_to_light = (this->center-hit_point).mag();
    Ray shadow_ray = Ray(hit_point, (this->center-hit_point)/dist_to_light);
    shadow_ray.trace(surfaces);
    if (shadow_ray.hit_surface == nullptr || shadow_ray.hit_surface->t() >= dist_to_light) {
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