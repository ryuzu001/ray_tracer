#include <vector>
#include "render_world.h"
#include "flat_shader.h"
#include "object.h"
#include "light.h"
#include "ray.h"


Render_World::Render_World()
    :background_shader(0),ambient_intensity(0),enable_shadows(true),
    recursion_depth_limit(3),disable_fresnel_reflection(false),disable_fresnel_refraction(false)
{}

Render_World::~Render_World()
{
    delete background_shader;
    for(size_t i=0;i<objects.size();i++) delete objects[i];
    for(size_t i=0;i<lights.size();i++) delete lights[i];
}

// Find the closest object of intersection and return the object that was
// intersected.  Record the Hit structure in hit.  If no intersection occurred,
// return NULL.  Note that in the case of a Boolean, the object returned will be
// the Boolean, but the object stored in hit will be the underlying primitive.
// Any intersection with t<=small_t should be ignored.
Object* Render_World::Closest_Intersection(const Ray& ray,Hit& hit)
{
    Object* closest_object = NULL;
    
    // int min_t = std::numeric_limits<int>::max();
    float min_t = 9999;
    
    
    for(unsigned i = 0; i < this->objects.size(); ++i){
        std::vector<Hit> hits;
        this->objects.at(i)->Intersection(ray, hits);
        for(unsigned j = 0; j < hits.size(); ++j){
    	    if(hits.at(j).t < min_t && hits.at(j).t > small_t){
    	        closest_object = const_cast<Object*>(hits.at(j).object);
    	        hit = hits.at(j);
    	        min_t = hits.at(j).t;
    	    }
        }
    }
    return closest_object;
}

// set up the initial view ray and call
void Render_World::Render_Pixel(const ivec2& pixel_index)
{
    Ray ray; // TODO: set up the initial view ray here
    
    vec3 end_point = camera.position;       //ray endpoint is the camera
    vec3 direction = this->camera.World_Position(pixel_index).normalized();  //direction = pixel
    ray.endpoint = end_point;
    ray.direction = direction;
    
    
    
    vec3 color=Cast_Ray(ray,1);
    camera.Set_Pixel(pixel_index,Pixel_Color(color));
}

void Render_World::Render()
{
    for(int j=0;j<camera.number_pixels[1];j++)
        for(int i=0;i<camera.number_pixels[0];i++)
            Render_Pixel(ivec2(i,j));
}

// cast ray and return the color of the closest intersected surface point,
// or the background color if there is no object intersection
vec3 Render_World::Cast_Ray(const Ray& ray,int recursion_depth)
{
    Hit hit;
    vec3 color;
    Object* obj = this->Closest_Intersection(ray,hit);
    if(obj != 0){
        // intersection
        // vec3 intersection_point = ray.endpoint + ray.direction * hit.t;
        vec3 intersection_point = ray.Point(hit.t);
		vec3 normal = hit.object->Normal(intersection_point);
		if(hit.ray_exiting){
		    normal = -normal;
		}
		color = obj->material_shader->Shade_Surface(ray, intersection_point, normal, recursion_depth, false);
    }
    else{
        // no intersection
        color = this->background_shader->Shade_Surface(ray,ray.endpoint,ray.endpoint,this->recursion_depth_limit, false);
    }
    
    return color;
}
