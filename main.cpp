#include <iostream>
#include <fstream>
#include <stdlib.h>

#include <time.h>
#include <vector>
#include <string>
#include <ctime>

#include "vec3.h"
#include "camera.h"
#include "surfaces/sphere.h"
#include "lights/point.h"

using namespace std;

int main() {

    clock_t begin = clock();  
    const int width = 200;
    const int height = 100;


    Sphere* sphere = new Sphere(vec3(0, 0, -1000), 100, vec3(255,0,0));
    Sphere* sphere2 = new Sphere(vec3(100, 0, -1000), 100, vec3(0,255,0));
    Sphere* sphere3 = new Sphere(vec3(0, 100, -1000), 100, vec3(0,0,255));

    PointLight* plight = new PointLight(vec3(0, 1000, 0), 1);
    vector<Surface *> spheres;
    vector<Light *> lights;
    spheres.push_back(sphere);
    spheres.push_back(sphere2);
    spheres.push_back(sphere3);
    lights.push_back(plight);
    
    Camera camera(vec3(), vec3(0,0,-1), vec3(0,1,0), width, height, 200, 5);
    for (unsigned k = 0; k < lights.size(); k++) {
        Light* light = lights[k];
        for (unsigned i = 0; i < camera.screen->height_px; i++) {
            for (unsigned j = 0; j < camera.screen->width_px; j++) {
                Ray ray = camera.generate_ray(j, i);
                ray.trace(spheres);
                if (ray.hit_surface != nullptr) {
                    vec3 color = light->illuminate(ray, spheres);
                    camera.screen->image_arr[i][j][0] += color.a;
                    camera.screen->image_arr[i][j][1] += color.b;
                    camera.screen->image_arr[i][j][2] += color.c;
                }
            }
        }

    }

    camera.saveBMP("image.bmp");
    clock_t end = clock();

    cout << "time elapsed: " << (end-begin)/1000.0 << endl;

    // srand(time(NULL));

    // ofstream image;
    // image.open ("image.ppm"); 
    // if (image.is_open()) {
    //     image << "P3\n";
    //     image << "255 100\n";
    //     image << "255\n\n";
    //     for (int i = 0; i < height; i++) {
    //         for (int j = 0; j < width; j++) {
    //             image << int(image_arr[i][j][0]) << " " << int(image_arr[i][j][1]) << " " << int(image_arr[i][j][2]) << "\n";
    //         }
    //     }
    //     image.close();
    // }
    // else {
    //     cout << "unable to open file";
    // }

    



    // Camera camera(vec3(), vec3(0,0,1), vec3(0,1,0),
    //     200, 100, 200, 1.7
    // );
    // int height = camera.screen->height_px;
    // camera.generate_ray(1,0).print();

    return 0;
};

