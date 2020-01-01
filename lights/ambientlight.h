#ifndef AMBIENTLIGHT_H
#define AMBIENTLIGHT_H

#include "../light.h"
#include "../surfaces/sphere.h"

class AmbientLight: public Light {
    public: 

        AmbientLight(vec3 color, double intensity);
        ~AmbientLight();

        vec3 illuminate(Ray &source_ray, const std::vector<Surface *> &surfaces);
};

#endif