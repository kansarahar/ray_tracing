#ifndef SURFACE_H
#define SURFACE_H

#include "vec3.h"
#include "material.h"


class Surface {
    public: 

        Material material = Material(__DIFFUSE__);
        void setMaterial(unsigned material_type) { this->material = Material(material_type); };

        virtual ~Surface() { };
        virtual bool hit(Ray &ray) = 0;

        inline double t() { return this->_t; };
        inline vec3 normal() { return this->_normal; };
        inline virtual vec3 color() { return this->_color; };

        virtual void translateSelf(const vec3 &translation) = 0;
        virtual void rotateSelf(const vec3 &axis, double angle) = 0;
        virtual void rotate(const vec3 &point, const vec3 &axis, double angle) = 0;

        virtual void texture() = 0;
        virtual void texture(vec3 (*texture_function)(double, double)) = 0;



    protected: 
        double _t;
        vec3 _normal;
        vec3 _color;

        // basis vectors for surface
        vec3 _up;
        vec3 _right;
        vec3 _cross;

        bool _textured;
        vec3 (*_texture_function)(double, double);
};


#endif