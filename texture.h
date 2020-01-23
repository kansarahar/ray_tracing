#ifndef TEXTURE_H
#define TEXTURE_H

#include "vec3.h"

#define __SOLID_COLOR__  0
#define __CUSTOM__ 1

class Texture {
    public: 
        Texture();
        Texture(vec3 solid_color);
        Texture(vec3 (*function)(
            const vec3 &hit_point, 
            const vec3 &center, 
            const vec3 &up, 
            const vec3 &right, 
            const vec3 &cross
        ));

        void set(vec3 solid_color);
        void set(vec3 (*function)(
            const vec3 &hit_point, 
            const vec3 &center, 
            const vec3 &up, 
            const vec3 &right, 
            const vec3 &cross
        ));

        vec3 getColor();
        vec3 getColor(
            const vec3 &hit_point, 
            const vec3 &center, 
            const vec3 &up, 
            const vec3 &right, 
            const vec3 &cross
        );
    
    private:
        unsigned _type;
        vec3 _color;
        vec3 (*_texture_function)(
            const vec3 &hit_point, 
            const vec3 &center, 
            const vec3 &up, 
            const vec3 &right, 
            const vec3 &cross
        );
};

#endif