#include "scene.h"

Scene::Scene(Camera *camera): camera(camera) {
    this->surfaces = new std::vector<Surface *>;    
    this->lights = new std::vector<Light *>;
}

Scene::~Scene() {
    delete this->surfaces;
    delete this->lights;
}

vec3 Scene::_castRay(unsigned depth, Ray &ray, Light *&light) {
    if (depth == 0) { return vec3(); }
    ray.trace(*(this->surfaces));
    if (ray.hit_surface != nullptr) {
        Material material = ray.hit_surface->material;
        if (material.type == __DIFFUSE__) {
            return material.albedo * light->illuminate(ray, *(this->surfaces));
        }
        if (material.type == __REFLECTIVE__) {
            Ray reflected_ray = Ray(ray.at(ray.hit_surface->t()), ray.direction.reflect(ray.hit_surface->normal()));
            vec3 reflected_color = _castRay(depth-1, reflected_ray, light);
        }        
    }
    return vec3();
}

void Scene::render(unsigned ray_depth=1, unsigned jitters=1, std::string image_name="image.bmp") {
    std::srand(std::time(nullptr));
    if (jitters < 1) { jitters = 1; }
    for (unsigned jitter = 0; jitter < jitters; jitter++) {
        for (unsigned k = 0; k < lights->size(); k++) {
            Light* light = (*lights)[k];
            for (unsigned i = 0; i < camera->screen->height_px; i++) {
                for (unsigned j = 0; j < camera->screen->width_px; j++) {
                    Ray ray = camera->castRay(j, i);
                    if (jitters > 1) {
                        double jitter_i = (rand()%100)/100.0;
                        double jitter_j = (rand()%100)/100.0;
                        ray = camera->castRay(j+jitter_j, i+jitter_i);
                    }
                    // ray.trace(*(this->surfaces));
                    // if (ray.hit_surface != nullptr) {
                    //     vec3 color = light->illuminate(ray, *(this->surfaces));
                    vec3 color = _castRay(1, ray, light);
                    camera->screen->image_arr[i][j][0] += color.a/jitters;
                    camera->screen->image_arr[i][j][1] += color.b/jitters;
                    camera->screen->image_arr[i][j][2] += color.c/jitters;
                    // }
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