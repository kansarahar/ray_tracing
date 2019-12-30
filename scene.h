#ifndef SCENE_H
#define SCENE_H

#include "camera.h"
#include "surface.h"
#include "light.h"
// #include "material.h"

#include "surfaces/sphere.h"
#include "surfaces/plane.h"
#include "lights/ambientlight.h"
#include "lights/directionallight.h"
#include "lights/pointlight.h"

#include <string>

class Scene {
    public: 
        Camera *camera;
        std::vector<Surface *> *surfaces;
        std::vector<Light *> *lights;

        Scene(Camera *);
        ~Scene();

        void addSurface(Surface *surface) { surfaces->push_back(surface); };
        void addLight(Light *light) { lights->push_back(light); };

        void render(int ray_depth, std::string image_name);
};

#endif