#ifndef SPHERE_H
#define SPHERE_H

#include "../surface.h"

class Sphere: public Surface {
    public: 

        Sphere(vec3 center, double radius, vec3 color);
        ~Sphere();

        bool hit(Ray &ray);
        void translateSelf(const vec3 &translation);
        void rotateSelf(const vec3 &axis, double angle);
        void rotate(const vec3 &point, const vec3 &axis, double angle);

    private:
        vec3 _center;
        double _radius;

};


#endif