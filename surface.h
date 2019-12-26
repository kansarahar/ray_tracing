#ifndef SURFACE_H
#define SURFACE_H

#define __DIFFUSE__  0
#define __REFLECTIVE__ 1
#define __REFRACTIVE__ 2

#include <cmath>

#include "vec3.h"


class Surface {
    public: 
        virtual ~Surface() { };
        virtual bool hit(Ray &ray) = 0;

        inline double t() { return this->_t; };
        inline Ray normal() { return this->_normal; };
        inline virtual vec3 color() { return this->_color; };


    protected: 
        double _t;
        Ray _normal;
        vec3 _color;
};

#endif