#include "reflective_shader.h"
#include "ray.h"
#include "render_world.h"

// #include <iostream>

vec3 Reflective_Shader::
Shade_Surface(const Ray& ray,const vec3& intersection_point,
    const vec3& same_side_normal,int recursion_depth,bool is_exiting) const
{
    vec3 color;
    
    /* Compute the reflected ray in the same way you calculate the reflection in the Phong shader. */
    
    /* From phong_shader.cpp: 
    
    vec3 R = l - n * (2 * dot(l,n)); 
    
    */
    
    // std::cout << recursion_depth;
        
    vec3 l = ray.direction;
    vec3 n = same_side_normal;
    
    vec3 endpoint = l - n * (2 * dot(l,n));
    
    Ray reflected_ray(endpoint, ray.direction);
    
    vec3 reflected_color = world.Cast_Ray(reflected_ray, recursion_depth);
    
    /* The final color should be    (reflectivity * reflected_color + (1 - reflectivity) * shader_color).    */
    
    vec3 shader_color = Shade_Surface(ray, intersection_point, same_side_normal, recursion_depth, is_exiting);
    
    color = reflectivity * reflected_color + (1 - reflectivity) * shader_color;

    return color;
}
