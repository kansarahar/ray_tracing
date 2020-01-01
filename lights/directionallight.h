#ifndef DIRECTIONALLIGHT_H
#define DIRECTIONALLIGHT_H

#include "../light.h"
#include "../surfaces/sphere.h"

class DirectionalLight: public Light {
    public: 

        vec3 direction;

        DirectionalLight(vec3 direction, vec3 color, double intensity);
        ~DirectionalLight();

        vec3 illuminate(Ray &source_ray, const std::vector<Surface *> &surfaces);
};

#endif