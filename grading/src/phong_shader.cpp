#include "light.h"
#include "phong_shader.h"
#include "ray.h"
#include "render_world.h"

// #include<iostream>

vec3 Phong_Shader::
Shade_Surface(const Ray& ray,const vec3& intersection_point,
    const vec3& same_side_normal,int recursion_depth, bool is_exiting) const
{
	vec3 color, colorA, colorD, colorS;
	
    
    
    /* ------------------ CALCULATE AMBIENT ------------------ */
		
	colorA = colorA + this->world.ambient_color * this->world.ambient_intensity * color_ambient;
	
	/* ------------------ END AMBIENT ------------------ */
	
	
	
	for(unsigned i = 0; i < this->world.lights.size(); i++){
    	
    	
    	
    	
    	/* ------------------ CALCULATE DIFFUSE ------------------ */
    	
		vec3 Rd = color_diffuse;
		vec3 L = this->world.lights[i]->Emitted_Light(ray);    // light color
		
		// "the intensity of the light should decay proportional to the square distance between the intersection point and the light source."
		
	    vec3 light_source = this->world.lights[i]->position;
		vec3 light_to_intersection = intersection_point - light_source;
		
		float light_decay = light_to_intersection.magnitude_squared();
		
		L = L / light_decay;         // Ld is now correct
		
		vec3 n = same_side_normal;
		n = n.normalized();
		vec3 l = - light_to_intersection;       // INTERSECTION POINT TO LIGHT SOURCE
		l = l.normalized();
			
		float dotln;        
		if(dot(l,n) < 0){       // max(0, dot(l,n))
		    dotln = 0;
		}
		else{ dotln = dot(l,n); }
	
		// colorD = colorD + Rd * L * dotln;
	
		/* ------------------ END DIFFUSE ------------------ */
		
		
		
		
		/* ------------------ CALCULATE SPECULAR ------------------ */
		
		/* proportional to the cosine of the angle between the reflected direction and 
		the vector from the intersection point to the camera position (C). */
		
		vec3 Rs = color_specular;
		
		vec3 R = l - n * (2 * dot(l,n));
		R = R.normalized();
			
		vec3 C = intersection_point - ray.endpoint;
		C = C.normalized();
		
		/* The specular intensity is max(dot(R,C),0)^α, where α is 
		given to you as the specular_power variable. */
		
		float dotrc;
		if(dot(R,C) < 0){		// max(0, rdotc)
			dotrc = 0;
		}
		else{ dotrc = dot(C,R); }
		
		float specular_intensity = pow(dotrc, specular_power);
		
		// colorS = colorS + Rs * L * specular_intensity;
		
		
		/* ------------------ END SPECULAR ------------------ */
		
		
		if(world.enable_shadows){
			
			// define shadow ray
			
			Ray shadow_ray;
			shadow_ray.endpoint = intersection_point;
			shadow_ray.direction = this->world.lights[i]->position - intersection_point;
			float shadow_mag = shadow_ray.direction.magnitude();
			
			// NORMALIZE THE DIRECTION  (!!!)
			
			shadow_ray.direction = shadow_ray.direction.normalized();
			
			// Cast shadow ray
			
			Hit hit;
			Object* obj = world.Closest_Intersection(shadow_ray,hit);
			
			// find if collision (shadow ray)
			
			vec3 collision;
			collision = shadow_ray.direction * hit.t;
			// collision = shadow_ray.endpoint + shadow_ray.direction * hit.t;
			// collision = collision - shadow_ray.endpoint;


			// IF OBJECT EXISTS AND OBJECT INTERSECTED IN FRONT OF LIGHT
			// NOT BEHIND (!!!)
			
			if(obj != 0 && shadow_mag > collision.magnitude()) {
				// return only ambient
			}
			else{
				// return all
				colorD = colorD + Rd * L * dotln;
				colorS = colorS + Rs * L * specular_intensity;
			}
		
	    }
	    else{
			colorD = colorD + Rd * L * dotln;
			colorS = colorS + Rs * L * specular_intensity;
		}

		
		
		
		color = colorD + colorS + colorA;
    }

    return color;
}

