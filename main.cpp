#include <iostream>
#include <fstream>
#include "stdlib.h"

#include "time.h"

#include "scene.h"

using namespace std;

int main() {


    clock_t begin = clock();  
    const int width = 200;
    const int height = 100;

    Camera *camera = new Camera(vec3(0,-200,0), vec3(0,1,0), vec3(0,0,1), width, height, 200, 5);
    // Camera camera(vec3(0, 100, 0), vec3(0,-100,-1440), vec3(0,1440,-100), width, height, 200, 5);
    


    Sphere* sphere = new Sphere(vec3(0, 440, 0), 30, vec3(255,80,80));
    Sphere* sphere2 = new Sphere(vec3(50, 440, 0), 30, vec3(80,255,80));
    Sphere* sphere3 = new Sphere(vec3(0, 440, 50), 30, vec3(80,80,255));
    Sphere* sphere4 = new Sphere(vec3(-500, 1000, 250), 30, vec3(255,255,0));
    Plane* plane1 = new Plane(vec3(0,0,-100), vec3(0,0,1));

    PointLight* plight = new PointLight(vec3(-20, 100, 0), vec3(1,1,1), 1.3);
    DirectionalLight *dlight = new DirectionalLight(vec3(1,0,-1), vec3(1,1,1), 1);
    AmbientLight *alight = new AmbientLight(vec3(1,1,1), 1);

    Scene scene(camera);
    scene.addSurface(sphere);
    scene.addSurface(sphere2);
    scene.addSurface(sphere3);
    scene.addSurface(sphere4);
    scene.addSurface(plane1);
    scene.addLight(plight);
    scene.addLight(dlight);
    scene.addLight(alight);

    // plane1->rotate(vec3(0,0,0), vec3(0,1,0), 20);
    // plane1->rotateSelf(vec3(0,1,0), 180);
    sphere->rotateSelf(vec3(1,0,0), 90);
    sphere2->rotateSelf(vec3(1,1,1),45);
    plane1->texture();

    scene.render(1, 1, "image.bmp");
    clock_t end = clock();

    cout << "time elapsed: " << (end-begin)/1000.0 << endl;

    
    return 0;
};

