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
        
    // vec3 d = -ray.direction;
    // vec3 n = same_side_normal;
    // vec3 endpoint = d - n * (2 * dot(d,n));
    // Ray reflected_ray(endpoint, d);
    
    Ray reflected_ray;
    reflected_ray.endpoint = intersection_point;
    reflected_ray.direction = ray.direction - same_side_normal * 2 * dot(ray.direction, same_side_normal);
    
    
    vec3 reflected_color = shader->world.Cast_Ray(reflected_ray, recursion_depth);
    
    vec3 shader_color = shader->Shade_Surface(ray, intersection_point, same_side_normal, recursion_depth, is_exiting);
    
    /* The final color should be    (reflectivity * reflected_color + (1 - reflectivity) * shader_color).    */
    
    color = reflectivity * reflected_color + (1 - reflectivity) * shader_color;

    return color;
}