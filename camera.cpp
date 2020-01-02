#include "camera.h"
#include <iostream>

Screen::Screen(): width(200), height(100), resolution(1) {
    this->width_px = unsigned(width*resolution);
    this->height_px = unsigned(height*resolution);

    this->image_arr = new double**[height_px];
    for (unsigned i = 0; i < height_px; i++) {
        image_arr[i] = new double*[width_px];
        for (unsigned j = 0; j < width_px; j++) {
            image_arr[i][j] = new double[3] {0,0,0};
        }
    }
}

Screen::Screen(double width, double height, double resolution): width(width), height(height), resolution(resolution) {
    this->width_px = int(width*resolution);
    this->height_px = int(height*resolution);
    
    this->image_arr = new double**[height_px];
    for (unsigned i = 0; i < height_px; i++) {
        image_arr[i] = new double*[width_px];
        for (unsigned j = 0; j < width_px; j++) {
            image_arr[i][j] = new double[3] {0,0,0};
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
    this->lookat = screen_dist*vec3(0,1,0);
    this->up = vec3(0,0,1);
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

Camera::~Camera() { }

void Camera::rotateSelf(const vec3 &axis, double angle) {
    this->lookat.rotate(axis, angle);
    this->up.rotate(axis, angle);
    this->right.rotate(axis, angle);
}

void Camera::rotate(const vec3 &point, const vec3 &axis, double angle) {
    this->center.rotate(point, axis, angle);
    this->rotateSelf(axis, angle);
}

Ray Camera::castRay(double screen_x_pixel, double screen_y_pixel) {
    // resolution = pixels / unit length
    double x_dist = (screen_x_pixel-this->screen->width_px/2.0)/this->screen->resolution;
    double y_dist = (this->screen->height_px/2.0-screen_y_pixel)/this->screen->resolution;

    return Ray(this->center, this->lookat+this->right*x_dist+this->up*y_dist);
}

void Camera::saveBMP(std::string name) {
    const char *img_name = name.c_str();

    uint32_t width_px = this->screen->width_px;
    uint32_t height_px = this->screen->height_px;
    double ***image_arr = this->screen->image_arr;

    BitmapFileHeader bfh;
    BitmapInfoHeader bih;

    bih.bi_width = width_px;
    bih.bi_height = height_px;

    FILE *file = fopen(img_name, "wb");
    if (!file) {
        printf("Could not write file\n");
        return;
    }

    /*Write headers*/
    fwrite(&bfh, 1, sizeof(bfh), file);
    fwrite(&bih, 1, sizeof(bih), file);

    /*Write bitmap*/
    for (int y = bih.bi_height-1; y >= 0; y--) { 
        for (int x = 0; x < int(bih.bi_width); x++) { 

            if (image_arr[y][x][0] < 0) { image_arr[y][x][0] = 0.0; }
            if (image_arr[y][x][1] < 0) { image_arr[y][x][1] = 0.0; }
            if (image_arr[y][x][2] < 0) { image_arr[y][x][2] = 0.0; }
            if (image_arr[y][x][0] > 255) { image_arr[y][x][0] = 255; }
            if (image_arr[y][x][1] > 255) { image_arr[y][x][1] = 255; }
            if (image_arr[y][x][2] > 255) { image_arr[y][x][2] = 255; }

            /*compute some pixel values*/
            unsigned char r = image_arr[y][x][0];
            unsigned char g = image_arr[y][x][1];
            unsigned char b = image_arr[y][x][2];

            fwrite(&b, 1, 1, file);
            fwrite(&g, 1, 1, file);
            fwrite(&r, 1, 1, file);
        }
        int bytes_in_row = bih.bi_width*bih.bi_bit_count/8;
        if (bytes_in_row%4 > 0) {
            for (int i = 0; i < 4-bytes_in_row%4; i++) {
                unsigned char zero = 0;
                fwrite(&zero, 1, 1, file);
            }
        }
    }
    fclose(file);
}

void Camera::savePPM(std::string name) {
    ofstream image;
    image.open (name); 
    double*** image_arr = this->screen->image_arr;
    if (image.is_open()) {
        image << "P3\n";
        image << "255 100\n";
        image << "255\n\n";
        for (unsigned y = 0; y < this->screen->height_px; y++) {
            for (unsigned x = 0; x < this->screen->width_px; x++) {
                if (image_arr[y][x][0] > 255) { image_arr[y][x][0] = 255; }
                if (image_arr[y][x][1] > 255) { image_arr[y][x][1] = 255; }
                if (image_arr[y][x][2] > 255) { image_arr[y][x][2] = 255; }
                image << int(image_arr[y][x][0]) << " " << int(image_arr[y][x][1]) << " " << int(image_arr[y][x][2]) << "\n";
            }
        }
        image.close();
    }
    else {
        cout << "unable to open file";
    }
}