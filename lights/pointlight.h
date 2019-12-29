#ifndef POINTLIGHT_H
#define POINTLIGHT_H

#include "../light.h"
#include "../surfaces/sphere.h"

class PointLight: public Light {
    public: 
        vec3 center;
        vec3 attenuation_function;
        bool attenuated;
        bool showing;
        Sphere* lightsphere;

        PointLight(vec3 center, double intensity);
        ~PointLight();

        inline void show() { this->showing = true; };
        vec3 illuminate(Ray &source_ray, const std::vector<Surface *> &surfaces);
};

#endif