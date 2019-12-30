#include "material.h"

Material::Material(int type, std::string name): type(type), name(name) {
    if (type == __REFLECTIVE__) {
        albedo = 0.92;

        k_a = 0.15;
        k_d = 0.80;
        k_s = 0.05;

        fraction_reflected = 0.92;
        fraction_refracted = 0;
        ior = 0;
    }
    else if (type == __REFRACTIVE__) {
        albedo = 0.84;

        k_a = 0.22;
        k_d = 0.54;
        k_s = 0.24;

        fraction_reflected = 0;
        fraction_refracted = 0.9;
        ior = 1.3;
    }
    else {
        type = __DIFFUSE__;
        albedo = 0.78;

        k_a = 0.10;
        k_d = 0.75;
        k_s = 0.15;
        alpha = 10; 
        
        fraction_reflected = 0;
        fraction_refracted = 0;
        ior = 1;
    }

}