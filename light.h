#ifndef LIGHT_H
#define LIGHT_H

#include <vector>

#include "vec3.h"
#include "surface.h"

class Light {
    public: 
        double intensity;

        virtual ~Light() { };

        virtual vec3 illuminate(Ray &source_ray, std::vector<Surface *>) = 0;
};

#endif