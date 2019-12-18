#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <time.h>

#include "vec3.h"
#include "camera.h"
#include "surfaces/sphere.h"

using namespace std;

int main() {


    // const int width = 400;
    // const int height = 200;

    // double ***image_arr = new double**[height];
    // for (int i = 0; i < height; i++) {
    //     image_arr[i] = new double*[width];
    //     for (int j = 0; j < width; j++) {
    //         image_arr[i][j] = new double[3];
    //     }
    // }

    // // srand(time(NULL));

    // ofstream image;
    // image.open ("test.ppm"); 
    // if (image.is_open()) {
    //     image << "P3\n";
    //     image << "255 100\n";
    //     image << "255\n\n";
    //     for (int i = 0; i < height; i++) {
    //         for (int j = 0; j < width; j++) {
    //             image << image_arr[i][j][0] << " " << image_arr[i][j][1] << " " << image_arr[i][j][2] << "\n";
    //         }
    //     }
    //     image.close();
    // }
    // else {
    //     cout << "unable to open file";
    // }

    Sphere* sphere = new Sphere(vec3(0,15,-100), 15.0);

    Ray* ray = new Ray();
    std::cout << sphere->hit(ray) << std::endl;
    delete ray;
    delete sphere;

    // Camera camera(vec3(), vec3(0,0,1), vec3(0,1,0),
    //     200, 100, 200, 1.7
    // );
    // int height = camera.screen->height_px;
    // camera.generate_ray(1,0).print();


};

