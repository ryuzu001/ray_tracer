#include "light.h"
#include "phong_shader.h"
#include "ray.h"
#include "render_world.h"

#include<iostream>

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
		
		float dotrc;
		if(dot(R,C) < 0){
			dotrc = 0;
		}
		else{ dotrc = dot(C,R); }
		
		float specular_intensity = pow(dotrc, specular_power);
		
		// colorS = colorS + Rs * L * specular_intensity;
		
		
		/* ------------------ END SPECULAR ------------------ */
		
		
		if(world.enable_shadows){
			Ray temp;
			temp.endpoint = intersection_point;
			temp.direction = (this->world.lights[i]->position - intersection_point).normalized();
			
			Hit hit;
			hit.t = 0;
			
			Object* obj = world.Closest_Intersection(temp, hit);
			
			vec3 NewPt = temp.direction * hit.t;
			
			if(obj != 0 && temp.direction.magnitude() < NewPt.magnitude()){

			}
			else{
				colorD = colorD + Rd * L * dotln;
				colorS = colorS + Rs * L * specular_intensity;
			}
		
	    }
	    else
	    {
			colorD = colorD + Rd * L * dotln;
			colorS = colorS + Rs * L * specular_intensity;
		}

		
		
		
		color = colorD + colorS + colorA;
    }

    return color;
}