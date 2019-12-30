#ifndef PLANE_H
#define PLANE_H

#include "../surface.h"

class Plane: public Surface {
    public: 

        Plane(vec3 point=vec3(0,0,-100), vec3 normal=vec3(0,0,1), vec3 color=vec3(150,150,150));

        ~Plane();

        bool hit(Ray &ray);
        void translateSelf(const vec3 &translation);
        void rotateSelf(const vec3 &axis, double angle);
        void rotate(const vec3 &point, const vec3 &axis, double angle);

    private:
        vec3 _point;

};


#endif