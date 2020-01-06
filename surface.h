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
        virtual void calculateValues(Ray &ray) = 0;

        virtual void translateSelf(const vec3 &translation) { this->_center.translate(translation); };
        virtual void rotateSelf(const vec3 &axis, double angle) { 
            this->_up.rotate(axis, angle);
            this->_right.rotate(axis, angle);
            this->_cross.rotate(axis, angle);
        };
        virtual void rotate(const vec3 &point, const vec3 &axis, double angle) {
            this->_center.rotate(axis, angle);
            this->rotateSelf(axis, angle);
        };

        virtual void texture() { this->_textured = true; };
        virtual void texture(vec3 (*texture_function)(
            const vec3 &hit_point, 
            const vec3 &center, 
            const vec3 &up, 
            const vec3 &right, 
            const vec3 &cross
        )) {
            this->_textured = true; this->_texture_function = texture_function; 
        };



    protected: 
        double _t;
        vec3 _normal;
        vec3 _center;
        vec3 _color;

        // basis vectors for surface
        vec3 _up;
        vec3 _right;
        vec3 _cross;

        bool _textured;
        vec3 (*_texture_function)(
            const vec3 &hit_point, 
            const vec3 &center, 
            const vec3 &up, 
            const vec3 &right, 
            const vec3 &cross
        );
};


class Sphere: public Surface {
    public: 

        Sphere(vec3 center, double radius, vec3 color);

        bool hit(Ray &ray);
        void calculateValues(Ray &ray);

    private:
        double _radius;

};


class Cylinder: public Surface {
    public:
        Cylinder(vec3 center, double radius, double height, vec3 color);

        bool hit(Ray &ray);
        void calculateValues(Ray &ray);

    private:
        double _radius;
        double _height;
};

class Cone: public Surface {
    public:
        Cone(vec3 center, double angle, double height, vec3 color);

        bool hit(Ray &ray);
        void calculateValues(Ray &ray);
    
    private:
        double _angle;
        double _height;
        double _cos_angle;
        double _tan_angle;
};

class Plane: public Surface {
    public: 

        Plane(vec3 center, vec3 normal, vec3 color);

        bool hit(Ray &ray);
        void calculateValues(Ray &ray);

        void rotateSelf(const vec3 &axis, double angle);
};

class Triangle: public Surface {
    public: 
        Triangle(vec3 v0, vec3 v1, vec3 v2, vec3 color);

        bool hit(Ray &ray);
        void calculateValues(Ray &ray);
        
        void translateSelf(const vec3 &translation);
        void rotateSelf(const vec3 &axis, double angle);
        void rotate(const vec3 &point, const vec3 &axis, double angle);

    
    private:
        vec3 _v0;
        vec3 _v1;
        vec3 _v2;
        vec3 _normal_unnormalized;
        double _area;
        double _u;
        double _v;
        double _w;
};

#endif