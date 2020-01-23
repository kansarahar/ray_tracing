#ifndef TEXTURE_EXAMPLES_H
#define TEXTURE_EXAMPLES_H

#include "vec3.h"

inline vec3 checkerSphereTexture(
        const vec3 &hit_point, 
        const vec3 &center, 
        const vec3 &up, 
        const vec3 &right, 
        const vec3 &cross
    ) { 
        vec3 r = hit_point-center;
        double cos_azi = cos(acos(dot((r - dot(r,up)*up).unit(), right))*5);
        double cos_pol = cos(acos(dot(r.unit(), up))*5);
        if ((cos_azi > 0 && cos_pol < 0) || (cos_azi < 0 && cos_pol > 0)) {
            return vec3(100, 100, 100);
        }
        return vec3(200, 200, 200); 
    }

inline vec3 checkerCylinderAndConeTexture(
    const vec3 &hit_point, 
    const vec3 &center, 
    const vec3 &up, 
    const vec3 &right, 
    const vec3 &cross
) {
    vec3 r = hit_point-center;
    double cos_height = cos(dot(r, up)/5);
    double cos_angle = cos(acos(dot((r - dot(r,up)*up).unit(), right))*5);
    if ((cos_height > 0 && cos_angle < 0) || (cos_height < 0 && cos_angle > 0)) {
        return vec3(100, 100, 100);
    }
    return vec3(200, 200, 200);
}

inline vec3 checkerPlaneTexture(
    const vec3 &hit_point, 
    const vec3 &center, 
    const vec3 &up, 
    const vec3 &right, 
    const vec3 &cross
) { 
    vec3 r = hit_point-center;
    double x = sin(dot(r, right)/10);
    double y = sin(dot(r, cross)/10);
    if ((x > 0 && y < 0) || (x < 0 && y > 0)) {
        return vec3(100, 100, 100);
    }
    return vec3(200, 200, 200); 
}

#endif