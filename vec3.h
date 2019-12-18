#ifndef VEC3_H
#define VEC3_H


class vec3 {
    public: 

        double a;
        double b;
        double c;

        vec3(double a, double b, double c);
        vec3();

        void operator+=(vec3 other);
        void operator-=(vec3 other);
        void operator*=(vec3 other);

        double mag();
        vec3 unit();
};

vec3 operator+(vec3 v1, vec3 v2);
vec3 operator-(vec3 v1, vec3 v2);
vec3 operator*(vec3 v1, vec3 v2);

vec3 operator*(double c, vec3 v);
vec3 operator*(vec3 v, double c);
vec3 operator/(vec3 v, double c);

double dot(vec3 v1, vec3 v2);
vec3 cross(vec3 v1, vec3 v2);
void print_vec(vec3 v);



class Surface;


class Ray {
    public:
        vec3 origin;
        vec3 direction;
        Surface* hit_surface;

        Ray();
        Ray(vec3 origin, vec3 direction);

        vec3 at(double t);
        vec3 trace(Surface** surfaces);

        void print();
};



#endif