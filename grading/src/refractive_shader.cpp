#include "refractive_shader.h"
#include "ray.h"
#include "render_world.h"

#include<iostream>

vec3 Refractive_Shader::
Shade_Surface(const Ray& ray, const vec3& intersection_point,
        const vec3& same_side_normal, int recursion_depth,bool is_exiting) const
{
    //Hints: Use REFRACTIVE_INDICES::AIR for air refractive_index
    //       Use is_exiting to decide the refractive indices on the ray and transmission sides
    vec3 reflection_color;
    vec3 refraction_color;
    double reflectance_ratio=-1;
    if(!world.disable_fresnel_refraction)
    {
        // TODO (Test 27+): Compute the refraction_color:
        vec3 newNormal;
        double n_r, n_i;
        if(is_exiting){
            // i outside, r inside
            n_r = REFRACTIVE_INDICES::AIR;
            n_i = refractive_index;
            newNormal = -same_side_normal;
        }
        else{
            n_r = refractive_index;
            n_i = REFRACTIVE_INDICES::AIR;
            newNormal = same_side_normal;
        }
        double cosI = dot(ray.direction, newNormal);
        
        double check_val = 1 - ((n_i * n_i) / (n_r * n_r)) * (1 - (cosI * cosI));
        
        double cosR = sqrt(check_val);
        
        // NEED TO COMPARE TO cosR (!!!)
        
        // - Check if it is total internal reflection. 
        
        if(check_val < 0){
            // If so update the reflectance_ratio for total internal refraction
            reflectance_ratio = 1;
        }
        else{
            //      else, follow the instructions below
            //      (Test 28+): Update the reflectance_ratio 
        
            double R_parallel, R_perpendicular;
            
            if(cosI < 0){
                cosI = -cosI;
            }
            if(cosR < 0){
                cosR = -cosR;
            }
            
            R_parallel = pow((n_r * cosI - n_i * cosR)/(n_r * cosI + n_i * cosR), 2);
            // R_parallel = R_parallel * R_parallel;
            
            R_perpendicular = pow((n_i * cosI - n_r * cosR)/(n_i * cosI + n_r * cosR), 2);
            // R_perpendicular = R_perpendicular * R_perpendicular;
            
            reflectance_ratio = (R_parallel + R_perpendicular) / 2;
            
            //      (Test 27+): Cast the refraction ray and compute the refraction_color
            vec3 T = (n_i/n_r) * (ray.direction - dot(newNormal, ray.direction) * newNormal) - cosR * newNormal;
            Ray refractive_ray;
            refractive_ray.endpoint = intersection_point;
            refractive_ray.direction = T;
            refraction_color = shader->world.Cast_Ray(refractive_ray, recursion_depth);
            
        }


    }

    if(!world.disable_fresnel_reflection){
        //TODO:(Test 26+): Compute reflection_color:
        // - Cast Reflection Ray andd get color
        //
        
        Ray reflected_ray;
        reflected_ray.endpoint = intersection_point;
        reflected_ray.direction = ray.direction - same_side_normal * 2 * dot(ray.direction, same_side_normal);
        
        reflection_color = shader->world.Cast_Ray(reflected_ray, recursion_depth);
    }

    Enforce_Refractance_Ratio(reflectance_ratio);
    vec3 color;
    // TODO: (Test 26+) Compute final 'color' by blending reflection_color and refraction_color using 
    //                  reflectance_ratio
    //
    color = reflectance_ratio * reflection_color + (1 - reflectance_ratio) * refraction_color;
    return color;
}

void Refractive_Shader::
Enforce_Refractance_Ratio(double& reflectance_ratio) const
{
    if(world.disable_fresnel_reflection) reflectance_ratio=0;
    else if(world.disable_fresnel_refraction) reflectance_ratio=1;
}
