#ifndef MATERIAL_H
#define MATERIAL_H

#define __DIFFUSE__  0
#define __REFLECTIVE__ 1
#define __REFRACTIVE__ 2

#include <string>

class Material {
    public:
        int type;

        double albedo;

        double k_a;
        double k_d;
        double k_s;
        double alpha;

        double fraction_reflected;

        double fraction_refracted;
        double ior;

        Material(int type);
};

#endif