#ifndef SPHERE_H
#define SPHERE_H

#include "../surface.h"

class Sphere: public Surface {
    public: 
        vec3 center;
        double radius;

        Sphere(vec3 center, double radius);
        
        ~Sphere();

        bool hit(Ray* ray);
};


#endif