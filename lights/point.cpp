#include "point.h"
#include <iostream>
PointLight::PointLight(vec3 center, double intensity)  {
    this->center = center;
    this->intensity = intensity;
    this->attenuated = false;
    this->attenuation_function[0] = 1;
    this->attenuation_function[1] = 0;
    this->attenuation_function[2] = 0;
    this->attenuation_function[3] = 1;
}

PointLight::~PointLight() {

}


vec3 PointLight::illuminate(Ray &source_ray, std::vector<Surface *> surfaces) {
    if (source_ray.hit_surface == nullptr) { 
        return vec3(); 
    }
    vec3 hit_point = source_ray.at(source_ray.hit_surface->t()*0.999999);
    Ray shadow_ray = Ray(hit_point, this->center-hit_point);
    shadow_ray.trace(surfaces);
    if (shadow_ray.hit_surface == nullptr) {
        vec3 pixel_color = source_ray.hit_surface->color()*this->intensity*dot(shadow_ray.direction.unit(), source_ray.hit_surface->normal().unit());
        // std::cout << pixel_color.to_string() << std::endl;
        if (pixel_color.a < 0 || pixel_color.b < 0 || pixel_color.c < 0) {
            return vec3();
        }
        return pixel_color;
    }
    return vec3();
}