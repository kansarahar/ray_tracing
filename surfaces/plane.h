#ifndef PLANE_H
#define PLANE_H

#include "../surface.h"

class Plane: public Surface {
    public: 

        Plane(vec3 point, vec3 normal, vec3 color);
        Plane(vec3 point1, vec3 point2, vec3 point3, vec3 color);
        ~Plane();

        bool hit(Ray &ray);

    private:
        vec3 _point;

};


#endif