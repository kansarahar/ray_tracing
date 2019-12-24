#ifndef POINT_H
#define POINT_H

#include "../light.h"

class PointLight: public Light {
    public: 
        vec3 center;
        bool attenuated;
        double attenuation_function[4];

        PointLight(vec3 center, double intensity);
        ~PointLight();

        vec3 illuminate(Ray &source_ray, std::vector<Surface *>);
};

#endif