#ifndef VEC3_H
#define VEC3_H

#define _USE_MATH_DEFINES

#include "math.h"

#include <string>
#include <vector>


class vec3 {
    public: 
        double a;
        double b;
        double c;

        vec3();
        vec3(double a, double b, double c);

        inline void operator+=(const vec3 &other) { this->a += other.a; this->b += other.b; this->c += other.c; };
        inline void operator-=(const vec3 &other) { this->a -= other.a; this->b -= other.b; this->c -= other.c; };
        inline void operator*=(const vec3 &other) { this->a *= other.a; this->b *= other.b; this->c *= other.c; };
        inline bool operator==(const vec3 &other) { return this->a == other.a && this->b == other.b && this->c == other.c; };

        double mag() const;
        vec3 unit() const;

        inline void translate(const vec3 &translation) { *this += translation; };
        void rotate(const vec3 &point, const vec3 &axis, double theta);  // rotate about axis through arbitrary point
        void rotate(const vec3 &axis, double theta);  // rotate about axis through origin

        std::string to_string();
};

inline vec3 operator+(const vec3 &v1, const vec3 &v2) { return vec3(v1.a+v2.a, v1.b+v2.b, v1.c+v2.c); };
inline vec3 operator-(const vec3 &v1, const vec3 &v2) { return vec3(v1.a-v2.a, v1.b-v2.b, v1.c-v2.c); };
inline vec3 operator*(const vec3 &v1, const vec3 &v2) { return vec3(v1.a*v2.a, v1.b*v2.b, v1.c*v2.c); };

inline vec3 operator*(double c, const vec3 &v) { return vec3(v.a*c, v.b*c, v.c*c); };
inline vec3 operator*(const vec3 &v, double c) { return vec3(v.a*c, v.b*c, v.c*c); };
inline vec3 operator/(const vec3 &v, double c) { return vec3(v.a/c, v.b/c, v.c/c); };

inline double dot(const vec3 &v1, const vec3 &v2) { return v1.a*v2.a + v1.b*v2.b + v1.c*v2.c; };
inline vec3 cross(const vec3 &v1, const vec3 &v2) { return vec3(v1.b*v2.c-v1.c*v2.b, v1.c*v2.a-v1.a*v2.c, v1.a*v2.b-v1.b*v2.a); };



class quaternion {
    public:
        double r;
        vec3 v;

        quaternion(double r, vec3 v);

        inline quaternion conj() const { return quaternion(this->r, -1*this->v); };
        std::string to_string();
};

inline quaternion operator*(const quaternion &q1, const quaternion &q2) { return quaternion(q1.r*q2.r - dot(q1.v, q2.v), q1.r*q2.v + q2.r*q1.v + cross(q1.v, q2.v)); };
inline quaternion operator+(const quaternion &q1, const quaternion &q2) { return quaternion(q1.r+q2.r, q1.v+q2.v); };


class Surface; // forward declaration

class Ray {
    public:
        vec3 origin;
        vec3 direction;
        Surface* hit_surface;

        Ray();
        Ray(vec3 origin, vec3 direction);

        inline vec3 at(double t) const { return this->origin + t*this->direction; };
        void trace(const std::vector<Surface *> &surfaces_array);

        std::string to_string();
};



#endif