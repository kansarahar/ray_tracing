#ifndef PLANE_H
#define PLANE_H

#include "../surface.h"

class Plane: public Surface {
    public: 

        Plane(vec3 point, vec3 color);

        ~Plane();

        bool hit(Ray &ray);
        void translateSelf(const vec3 &translation);
        void rotateSelf(const vec3 &axis, double angle);

    private:
        vec3 _point;

};


#endif