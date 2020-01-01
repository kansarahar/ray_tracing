#ifndef LIGHT_H
#define LIGHT_H

#include "vec3.h"
#include "surface.h"

class Light {
    public: 
        vec3 intensity;

        virtual ~Light() { };

        virtual vec3 illuminate(Ray &source_ray, const std::vector<Surface *>& surfaces) = 0;
};

#endif