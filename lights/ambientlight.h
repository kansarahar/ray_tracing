#ifndef AMBIENTLIGHT_H
#define AMBIENTLIGHT_H

#include "../light.h"
#include "../surfaces/sphere.h"

class AmbientLight: public Light {
    public: 

        AmbientLight(double intensity);
        ~AmbientLight();

        vec3 illuminate(Ray &source_ray, const std::vector<Surface *> &surfaces);
};

#endif