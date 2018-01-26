#include "light.h"
#include "phong_shader.h"
#include "ray.h"
#include "render_world.h"

#include<iostream>

vec3 Phong_Shader::
Shade_Surface(const Ray& ray,const vec3& intersection_point,
    const vec3& same_side_normal,int recursion_depth, bool is_exiting) const
{
	vec3 color;
    vec3 colorA;
	colorA = colorA + color_ambient * this->world.ambient_color * this->world.ambient_intensity;
    vec3 colorD;
    vec3 colorS;
    
	vec3 Rd = color_diffuse;
	vec3 Ld = this->world.lights[0]->Emitted_Light(ray);    // light color
	
	// "the intensity of the light should decay proportional to the square distance between the intersection point and the light source."
    vec3 light_source = this->world.lights[0]->position;
	vec3 light_to_intersection = intersection_point - light_source;
	
	float light_decay = light_to_intersection.magnitude_squared();
	
	Ld  = Ld / light_decay;         // Ld is now correct
	
	vec3 n = same_side_normal;
	n = n.normalized();
	vec3 l = - light_to_intersection;       // INTERSECTION POINT TO LIGHT SOURCE
	l = l.normalized();
		
	float dotln;        
	if(dot(l,n) < 0){       // max(0, dot(l,n))
	    dotln = 0;
	}
	else{ dotln = dot(l,n); }
	
	colorD = colorD + Rd * Ld * dotln;
	
	color = colorD;

    return color;
}