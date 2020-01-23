#include "light.h"

AmbientLight::AmbientLight(vec3 color, double intensity)  {
    this->intensity = intensity*(color.unit());
}

AmbientLight::~AmbientLight() { }


vec3 AmbientLight::illuminate(Ray &source_ray, const std::vector<Surface *> &surfaces) {
    Surface* surface = source_ray.hit_surface;
    if (surface == nullptr) { return vec3(); }
    return surface->color()*this->intensity*surface->material.k_a;
}



DirectionalLight::DirectionalLight(vec3 direction, vec3 color, double intensity)  {
    this->direction = direction.unit();
    this->intensity = intensity*(color.unit());
}

DirectionalLight::~DirectionalLight() { }


vec3 DirectionalLight::illuminate(Ray &source_ray, const std::vector<Surface *> &surfaces) {
    Surface *surface = source_ray.hit_surface;
    if (surface == nullptr) { return vec3(); }
    vec3 hit_point = source_ray.at(surface->t()*0.999999);
    Ray shadow_ray = Ray(hit_point, -1*this->direction);
    shadow_ray.trace(surfaces);
    if (shadow_ray.hit_surface == nullptr) {
        vec3 diffuse_color = surface->color()*this->intensity*dot(shadow_ray.direction.unit(), surface->normal().unit());
        if (diffuse_color < 0) { diffuse_color = vec3(); }

        vec3 spec_color = vec3();
        vec3 reflected_vector = (this->direction).reflect(surface->normal()).unit();
        double spec_comp = dot(reflected_vector, -1*source_ray.direction.unit());
        if (spec_comp > 0) {
            spec_color = pow(spec_comp, surface->material.alpha)*this->intensity*255;
        }

        vec3 pixel_color = diffuse_color*surface->material.k_d + spec_color*surface->material.k_s;
        if (pixel_color < 0) {
            return vec3();
        }
        return pixel_color;
    }
    return vec3();
}




PointLight::PointLight(vec3 center, vec3 color, double intensity)  {
    this->center = center;
    this->intensity = intensity*(color.unit());
    this->attenuated = false;
    this->showing = false;
    this->attenuation_function = vec3(1, 0, 0);
}

PointLight::~PointLight() { }


vec3 PointLight::illuminate(Ray &source_ray, const std::vector<Surface *> &surfaces) {
    Surface *surface = source_ray.hit_surface;
    if (surface == nullptr) { return vec3(); }
    vec3 hit_point = source_ray.at(surface->t()*0.999999);
    double dist_to_light = (this->center-hit_point).mag();
    Ray shadow_ray = Ray(hit_point, (this->center-hit_point)/dist_to_light);
    shadow_ray.trace(surfaces);
    if (shadow_ray.hit_surface == nullptr || shadow_ray.hit_surface->t() >= dist_to_light) {

        vec3 diffuse_color = surface->color()*this->intensity*dot(shadow_ray.direction.unit(), surface->normal().unit());
        if (diffuse_color < 0) { diffuse_color = vec3(); }

        vec3 spec_color = vec3();
        vec3 reflected_vector = (hit_point-this->center).reflect(surface->normal()).unit();
        double spec_comp = dot(reflected_vector, -1*source_ray.direction.unit());
        if (spec_comp > 0) {
            spec_color = pow(spec_comp, surface->material.alpha)*this->intensity*255;
        }

        vec3 pixel_color = diffuse_color*surface->material.k_d + spec_color*surface->material.k_s;
        if (pixel_color < 0) {
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