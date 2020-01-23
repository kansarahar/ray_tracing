#include "texture.h"

Texture::Texture() {
    _type = __SOLID_COLOR__;
    _color = vec3(250,250,250);
}

Texture::Texture(vec3 solid_color) {
    _type = __SOLID_COLOR__;
    _color = solid_color;
}

Texture::Texture(vec3 (*function)(
    const vec3 &hit_point, 
    const vec3 &center, 
    const vec3 &up, 
    const vec3 &right, 
    const vec3 &cross
)){
    _type = __CUSTOM__;
    _texture_function = function;
}

void Texture::set(vec3 solid_color) {
    _type = __SOLID_COLOR__;
    _color = solid_color;
}

void Texture::set(vec3 (*function)(
    const vec3 &hit_point, 
    const vec3 &center, 
    const vec3 &up, 
    const vec3 &right, 
    const vec3 &cross
)) {
    _type = __CUSTOM__;
    _texture_function = function;
}

vec3 Texture::getColor() { 
    return _color; 
}

vec3 Texture::getColor(
    const vec3 &hit_point, 
    const vec3 &center, 
    const vec3 &up, 
    const vec3 &right, 
    const vec3 &cross
) {
    if (_type == __SOLID_COLOR__) {
        return _color;
    }
    return _texture_function(hit_point, center, up, right, cross);
}



