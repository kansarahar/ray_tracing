#ifndef SURFACE_H
#define SURFACE_H

#include <cmath>

#include "vec3.h"


class Surface {
    public: 
        Ray normal;
        double t;
        vec3 color;

        virtual ~Surface() {

        };

        virtual bool hit(Ray &ray) = 0;
};

#endif