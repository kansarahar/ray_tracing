#include "camera.h"

Screen::Screen(double width, double height, double resolution): width(width), height(height), resolution(resolution) {
    this->width_px = int(width*resolution);
    this->height_px = int(height*resolution);
    
    this->image_arr = new double**[height_px];
    for (int i = 0; i < height_px; i++) {
        image_arr[i] = new double*[width_px];
        for (int j = 0; j < width_px; j++) {
            image_arr[i][j] = new double[3];
        }
    }
}

Screen::~Screen() {
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            delete[] image_arr[i][j];
        }
        delete[] image_arr[i];
    }
    delete[] image_arr;
}

Camera::Camera(double screen_dist, double resolution) {
    this->center = vec3();
    this->lookat = screen_dist*vec3(0,0,-1);
    this->up = vec3(0,1,0);
    this->right = vec3(1,0,0);

    this->screen = new Screen(200, 100, resolution);
}

Camera::Camera(vec3 center, vec3 lookat, vec3 up, double screen_width, double screen_height, double screen_dist, double resolution) {
    this->center = center;
    this->lookat = screen_dist*lookat.unit();
    this->up = up;
    // ensure that basis is orthonormal
    this->right = cross(lookat, up).unit();
    this->up = cross(right, lookat).unit();

    this->screen = new Screen(screen_width, screen_height, resolution);
}

Camera::~Camera() {
    delete this->screen;
}

Ray Camera::generate_ray(int x_pixel, int y_pixel) {
    double x_dist = (double(x_pixel)/this->screen->resolution)-(this->screen->width/2);
    double y_dist = (double(y_pixel)/this->screen->resolution)-(this->screen->height/2);
    return Ray(this->center, this->lookat+this->right*x_dist+this->up*y_dist);
}