#include "scene.h"

Scene::Scene(Camera *camera): camera(camera) {
    this->surfaces = new std::vector<Surface *>;    
    this->lights = new std::vector<Light *>;
}

Scene::~Scene() {
    delete this->surfaces;
    delete this->lights;
}

void Scene::render(int ray_depth=1, std::string image_name="image.bmp") {
    for (unsigned k = 0; k < lights->size(); k++) {
        Light* light = (*lights)[k];
        for (unsigned i = 0; i < camera->screen->height_px; i++) {
            for (unsigned j = 0; j < camera->screen->width_px; j++) {
                Ray ray = camera->castRay(j, i);
                ray.trace(*surfaces);
                if (ray.hit_surface != nullptr) {
                    vec3 color = light->illuminate(ray, *surfaces);
                    camera->screen->image_arr[i][j][0] += color.a;
                    camera->screen->image_arr[i][j][1] += color.b;
                    camera->screen->image_arr[i][j][2] += color.c;
                }
            }
        }
    }
    std::string extension = image_name.substr(image_name.size()-3);
    if (extension == "bmp" || extension == "BMP") {
        camera->saveBMP(image_name);
    }
    else if (extension == "ppm" || extension == "PPM") {
        camera->savePPM(image_name);
    }
}