#include <iostream>
#include <fstream>
#include "stdlib.h"

#include "time.h"

#include "scene.h"
#include "texture_examples.h"

using namespace std;

int main() {


    clock_t begin = clock();  
    const int width = 150;
    const int height = 100;

    Camera *camera = new Camera(vec3(0,-200,0), vec3(0,1,0), vec3(0,0,1), width, height, 200, 10);    


    Sphere* sphere1 = new Sphere(vec3(0, 440, -70), 30);
    Sphere* sphere2 = new Sphere(vec3(150, 440, -70), 30);;
    Sphere* sphere3 = new Sphere(vec3(0, 440, -20), 30);
    
    Plane* plane1 = new Plane(vec3(0,0,-100), vec3(0,0,1));//, vec3(150,150,150));

    Cylinder* cylinder1 = new Cylinder(vec3(-120,420,-100), 20, 100);//, vec3(150,150,150));
    
    Cone* cone1 = new Cone(vec3(-100,370,-100), 30, 60);//, vec3(150,150,150));

    Triangle* tri1 = new Triangle(vec3(0,0,0), vec3(-100,0,100), vec3(100,0,100));//, vec3(250,0,0));

    PointLight* plight1 = new PointLight(vec3(-50,350, 100), vec3(1,1,1), 1.3);
    DirectionalLight *dlight1 = new DirectionalLight(vec3(-1,0,-1), vec3(1,1,1), 1.7);
    DirectionalLight *dlight2 = new DirectionalLight(vec3(0,0,-1), vec3(1,1,1), 0.5);
    DirectionalLight *dlight3 = new DirectionalLight(vec3(0,1,-1), vec3(1,1,1), 0.7);
    AmbientLight *alight = new AmbientLight(vec3(1,1,1), 1);

    Scene scene(camera);
    scene.addSurface(sphere1);
    scene.addSurface(sphere2);
    scene.addSurface(sphere3);
    scene.addSurface(plane1);
    scene.addSurface(cylinder1);
    scene.addSurface(cone1);
    scene.addSurface(tri1);

    scene.addLight(plight1);
    scene.addLight(dlight1);
    // scene.addLight(dlight2);
    // scene.addLight(dlight3);
    scene.addLight(alight);

    sphere1->setTexture(vec3(255,80,80));
    sphere2->setTexture(vec3(80,255,80));
    sphere3->setTexture(vec3(80,80,255));
    plane1->setTexture(vec3(150,150,150));
    cylinder1->setTexture(vec3(150,150,150));
    cone1->setTexture(vec3(150,150,150));
    tri1->setTexture(vec3(250,0,0));

    sphere1->rotateSelf(vec3(1,0,0), 90);
    sphere2->rotateSelf(vec3(1,1,1),45);
    plane1->rotateSelf(vec3(1,0,0), 180);
    cone1->rotateSelf(vec3(0,1,0), -30);
    // cylinder1->rotateSelf(vec3(0,1,0), -30);
    tri1->rotateSelf(vec3(0,0,1), 180);
    // tri1->rotateSelf(vec3(0,1,0), -30);
    tri1->translateSelf(vec3(0,500,-50));


    plane1->setMaterial(__REFLECTIVE__);
    tri1->setMaterial(__REFLECTIVE__);
    // sphere2->setMaterial(__REFLECTIVE__);
    // sphere->setMaterial(__REFLECTIVE__);
    cone1->setMaterial(__REFLECTIVE__);
    cylinder1->setMaterial(__REFLECTIVE__);

    

    plane1->setTexture(checkerPlaneTexture);
    // sphere1->texture()
    // sphere2->texture();
    // cone1->texture();
    // cylinder1->texture();

    camera->translateSelf(vec3(0,0,-50));
    camera->rotate(vec3(0,440,0), camera->right, -45);
    camera->rotate(vec3(0,440,0), vec3(0,0,1), 45);

    scene.render(10, 1, "image.bmp");
    clock_t end = clock();

    cout << "time elapsed: " << (end-begin)/1000.0 << endl;

    
    return 0;
};

