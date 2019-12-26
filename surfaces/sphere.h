#ifndef SPHERE_H
#define SPHERE_H

#include "../surface.h"

class Sphere: public Surface {
    public: 

        Sphere(vec3 center, double radius, vec3 color);
        ~Sphere();

        bool hit(Ray &ray);

    private:
        vec3 _center;
        double _radius;

};


#endif