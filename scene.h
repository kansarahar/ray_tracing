#ifndef SCENE_H
#define SCENE_H

#include "camera.h"
#include "surface.h"
#include "light.h"

#include <string>
#include <stdlib.h>
#include <ctime>

class Scene {
    public: 
        Camera *camera;
        std::vector<Surface *> *surfaces;
        std::vector<Light *> *lights;

        Scene(Camera *);
        ~Scene();

        void addSurface(Surface *surface) { surfaces->push_back(surface); };
        void addLight(Light *light) { lights->push_back(light); };

        void render(unsigned ray_depth, unsigned jitters, std::string image_name);
    
    private:
        vec3 _castRay(unsigned depth, Ray &ray, Light *&light);
};

#endif