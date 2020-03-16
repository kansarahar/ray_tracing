#include "material.h"

Material::Material(int type): type(type) {
    if (type == __REFLECTIVE__) {
        albedo = 0.97;

        k_a = 0.1;
        k_d = 0.2;
        k_s = 1;
        alpha = 50;

        fraction_reflected = 0.5;
        fraction_refracted = 0;
        ior = 0;
    }
    else if (type == __REFRACTIVE__) {
        albedo = 1;

        k_a = 0;
        k_d = 1;
        k_s = 1;
        alpha = 20;

        fraction_reflected = 0;
        fraction_refracted = 1;
        ior = 1.1;
    }
    else {
        type = __DIFFUSE__;
        albedo = 0.73;

        k_a = 0.10;
        k_d = 0.65;
        k_s = 0.25;
        alpha = 20; 
        
        fraction_reflected = 0;
        fraction_refracted = 0;
        ior = 1;
    }

}