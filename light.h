#ifndef LIGHT_H
#define LIGHT_H

#include "vec3.h"
#include "surface.h"

class Light {
    public: 
        vec3 intensity;

        virtual ~Light() { };

        virtual vec3 illuminate(const Ray &source_ray, const std::vector<Surface *>& surfaces) = 0;
};

class AmbientLight: public Light {
    public: 

        AmbientLight(vec3 color, double intensity);
        ~AmbientLight();

        vec3 illuminate(const Ray &source_ray, const std::vector<Surface *> &surfaces);
};

class DirectionalLight: public Light {
    public: 

        vec3 direction;

        DirectionalLight(vec3 direction, vec3 color, double intensity);
        ~DirectionalLight();

        vec3 illuminate(const Ray &source_ray, const std::vector<Surface *> &surfaces);
};

class PointLight: public Light {
    public: 
        vec3 center;
        vec3 attenuation_function;
        bool attenuated;
        bool showing;
        Sphere* lightsphere;

        PointLight(vec3 center, vec3 color, double intensity);
        ~PointLight();

        inline void show() { this->showing = true; };
        vec3 illuminate(const Ray &source_ray, const std::vector<Surface *> &surfaces);
};




#endif