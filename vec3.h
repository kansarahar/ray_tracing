#ifndef VEC3_H
#define VEC3_H

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

        double mag();
        vec3 unit();
        std::string to_string();
};

inline vec3 operator+(const vec3 &v1, const vec3 &v2) { return vec3(v1.a+v2.a, v1.b+v2.b, v1.c+v2.c); };
inline vec3 operator-(const vec3 &v1, const vec3 &v2) { return vec3(v1.a-v2.a, v1.b-v2.b, v1.c-v2.c); };
inline vec3 operator*(const vec3 &v1, const vec3 &v2) { return vec3(v1.a*v2.a, v1.b*v2.b, v1.c*v2.c); };

inline vec3 operator*(double c, const vec3 &v) { return vec3(v.a*c, v.b*c, v.c*c); };
inline vec3 operator*(const vec3 &v, double c) { return vec3(v.a*c, v.b*c, v.c*c); };
inline vec3 operator/(const vec3 &v, double c) { return vec3(v.a/c, v.b/c, v.c/c); };

inline double dot(const vec3 &v1, const vec3 &v2) {
    return v1.a*v2.a + v1.b*v2.b + v1.c*v2.c;
};
inline vec3 cross(const vec3 &v1, const vec3 &v2) { 
    return vec3(v1.b*v2.c-v1.c*v2.b, v1.c*v2.a-v1.a*v2.c, v1.a*v2.b-v1.b*v2.a);
};



class Surface;


class Ray {
    public:
        vec3 origin;
        vec3 direction;
        Surface* hit_surface;

        Ray();
        Ray(vec3 origin, vec3 direction);

        inline vec3 at(double t) { return this->origin + t*this->direction; };
        void trace(std::vector<Surface *> &surfaces_array);

        std::string to_string();
};



#endif