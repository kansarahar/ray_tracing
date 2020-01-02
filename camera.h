#ifndef CAMERA_H
#define CAMERA_H

#include "vec3.h"
#include "bmp.h"


class Screen {
    public:
        double width;
        double height;
        
        unsigned width_px;
        unsigned height_px;

        double resolution;
        double ***image_arr;

        Screen();
        Screen(double width, double height, double resolution);
        ~Screen();
};

class Camera {
    public:
        vec3 center;
        vec3 lookat;
        vec3 up;
        vec3 right;
        
        Screen *screen;

        // resolution = pixels/unit_distance
        Camera(double screen_dist, double resolution=1);
        Camera(vec3 center, vec3 lookat, vec3 up, 
            double screen_width, double screen_height, 
            double screen_dist, double resolution=1
        );
        ~Camera();

        void translateSelf(const vec3 &translation) { this->center += translation; };
        void rotateSelf(const vec3 &axis, double angle);
        void rotate(const vec3 &point, const vec3 &axis, double angle);

        Ray castRay(double screen_x_pixel, double screen_y_pixel);

        void saveBMP(std::string name);
        void savePPM(std::string name);
};


#endif