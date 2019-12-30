#include <iostream>
#include <fstream>
#include "stdlib.h"

#include "time.h"

#include "camera.h"
#include "surfaces/sphere.h"
#include "surfaces/plane.h"
#include "lights/pointlight.h"
#include "lights/directionallight.h"
#include "lights/ambientlight.h"

using namespace std;

int main() {

    clock_t begin = clock();  
    const int width = 200;
    const int height = 100;


    Sphere* sphere = new Sphere(vec3(0, 440, 0), 30, vec3(255,0,0));
    Sphere* sphere2 = new Sphere(vec3(50, 440, 0), 30, vec3(0,255,0));
    Sphere* sphere3 = new Sphere(vec3(0, 440, 50), 30, vec3(0,0,255));
    Sphere* sphere4 = new Sphere(vec3(-500, 1000, 250), 30, vec3(255,255,0));
    Plane* plane1 = new Plane(vec3(0,0,-100), vec3(0,0,1));

    PointLight* plight = new PointLight(vec3(-20, 100, 0), 0.7);
    DirectionalLight *dlight = new DirectionalLight(vec3(1,0,-1), 0.1);
    AmbientLight *alight = new AmbientLight(0.2);
    vector<Surface *> spheres;
    vector<Light *> lights;
    spheres.push_back(sphere);
    spheres.push_back(sphere2);
    spheres.push_back(sphere3);
    spheres.push_back(sphere4);
    spheres.push_back(plane1);
    lights.push_back(plight);
    lights.push_back(dlight);
    lights.push_back(alight);

    // plane1->rotate(vec3(0,0,0), vec3(0,1,0), 180);
    plane1->rotateSelf(vec3(0,1,0), 180);
    Camera camera(vec3(0,-200,0), vec3(0,1,0), vec3(0,0,1), width, height, 200, 2);
    // Camera camera(vec3(0, 100, 0), vec3(0,-100,-1440), vec3(0,1440,-100), width, height, 200, 5);
    for (unsigned k = 0; k < lights.size(); k++) {
        Light* light = lights[k];
        for (unsigned i = 0; i < camera.screen->height_px; i++) {
            for (unsigned j = 0; j < camera.screen->width_px; j++) {
                Ray ray = camera.castRay(j, i);
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

    
    return 0;
};

