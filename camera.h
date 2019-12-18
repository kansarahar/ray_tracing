#ifndef CAMERA_H
#define CAMERA_H

#include "vec3.h"


class Screen {
    public:
        double width;
        double height;
        
        int width_px;
        int height_px;

        double resolution;
        double ***image_arr;

        Screen(double width, double height, double resolution);
        ~Screen();
};

class Camera {
    public:
        vec3 center;
        vec3 lookat;
        vec3 up;
        vec3 right;
        
        Screen* screen;

        // resolution = pixels/unit_distance
        Camera(double screen_dist, double resolution=1);
        Camera(vec3 center, vec3 lookat, vec3 up, 
            double screen_width, double screen_height, 
            double screen_dist, double resolution=1
        );
        ~Camera();

        Ray generate_ray(int x_pixel, int y_pixel);
};


#endif