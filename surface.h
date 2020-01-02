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

        virtual void texture() { this->_textured = true; };
        virtual void texture(vec3 (*texture_function)(double, double)) { this->_textured = true; this->_texture_function = texture_function; };



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


class Sphere: public Surface {
    public: 

        Sphere(vec3 center, double radius, vec3 color);
        ~Sphere();

        bool hit(Ray &ray);
        void translateSelf(const vec3 &translation);
        void rotateSelf(const vec3 &axis, double angle);
        void rotate(const vec3 &point, const vec3 &axis, double angle);


    private:
        vec3 _center;
        double _radius;

};


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